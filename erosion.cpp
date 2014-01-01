// ****************************************************************************
//  erosion.cpp                                                     Tao project
// ****************************************************************************
//
//   File Description:
//
//   Erosion filter implementation.
//
//
//
//
//
//
//
// ****************************************************************************
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriété de Taodyne SAS - Confidentiel
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************
#include "erosion.h"

// ============================================================================
//
//   Erosion filter
//
// ============================================================================

bool                  Erosion::failed = false;
QGLShaderProgram*     Erosion::pgm = NULL;
uint                  Erosion::colorMapID = 0;
uint                  Erosion::radiusID = 0;
uint                  Erosion::thresholdID = 0;
uint                  Erosion::colorID = 0;
uint                  Erosion::centerID = 0;
const QGLContext*     Erosion::context = NULL;

#define GL (*graphic_state)

Erosion::Erosion(float x, float y, float threshold)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Filter(&context), x(x), y(y), threshold(threshold), radius(1.0)
{
    IFTRACE(filters)
        debug() << "Create black and white filter" << "\n";

    checkGLContext();
}


Erosion::~Erosion()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void Erosion::setColor(GLfloat erode_color[3])
// ----------------------------------------------------------------------------
//   Set erosion color
// ----------------------------------------------------------------------------
{
    color[0] = erode_color[0];
    color[1] = erode_color[1];
    color[2] = erode_color[2];
}


void Erosion::setRadius(float r)
// ----------------------------------------------------------------------------
//   Set erosion radius
// ----------------------------------------------------------------------------
{
    radius = r;
}


void Erosion::Draw()
// ----------------------------------------------------------------------------
//   Apply erosion filter
// ----------------------------------------------------------------------------
{
    checkGLContext();

    uint prg_id = 0;
    if(pgm)
        prg_id = pgm->programId();

    if(prg_id)
    {
        IFTRACE(filters)
                debug() << "Apply erosion filter" << "\n";

        // Set shader
        tao->SetShader(prg_id);

        // Set texture parameters
        GL.Uniform(colorMapID, 0);

        // Set erosion parameters
        GL.Uniform(radiusID, radius);
        GL.Uniform(thresholdID, threshold);
        GL.Uniform3fv(colorID, 1, color);

        GLfloat center[2] = {x, y};
        GL.Uniform2fv(centerID, 1, center);
    }
}


void Erosion::createShaders()
// ----------------------------------------------------------------------------
//   Create shader programs
// ----------------------------------------------------------------------------
{
    if(!failed)
    {
        IFTRACE(filters)
                debug() << "Create shader for erosion filter" << "\n";

        delete pgm;

        pgm = new QGLShaderProgram(*pcontext);
        bool ok = false;

        // Basic vertex shader
        static string vSrc =
                "/********************************************************************************\n"
                "**                                                                               \n"
                "** Copyright (C) 2011 Taodyne.                                                   \n"
                "** All rights reserved.                                                          \n"
                "** Contact: Taodyne (contact@taodyne.com)                                        \n"
                "**                                                                               \n"
                "** This file is part of the Tao Presentations application, developped by Taodyne.\n"
                "** It can be only used in the software and these modules.                        \n"
                "**                                                                               \n"
                "** If you have questions regarding the use of this file, please contact          \n"
                "** Taodyne at contact@taodyne.com.                                               \n"
                "**                                                                               \n"
                "********************************************************************************/\n"
                "void main()"
                "{"
                "   gl_Position = ftransform();"

                "   /* Compute texture coordinates */"
                "   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
                "   gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;"
                "   gl_TexCoord[2] = gl_TextureMatrix[2] * gl_MultiTexCoord2;"
                "   gl_TexCoord[3] = gl_TextureMatrix[3] * gl_MultiTexCoord3;"
                "}";

        static string fSrc =
                "/********************************************************************************\n"
                "**                                                                               \n"
                "** Copyright (C) 2011 Taodyne.                                                   \n"
                "** All rights reserved.                                                          \n"
                "** Contact: Taodyne (contact@taodyne.com)                                        \n"
                "**                                                                               \n"
                "** This file is part of the Tao Presentations application, developped by Taodyne.\n"
                "** It can be only used in the software and these modules.                        \n"
                "**                                                                               \n"
                "** If you have questions regarding the use of this file, please contact          \n"
                "** Taodyne at contact@taodyne.com.                                               \n"
                "**                                                                               \n"
                "********************************************************************************/\n"
                "/* Filter parameters */"
                "uniform float radius;"
                "uniform float threshold;"
                "uniform vec2 center;"
                "uniform vec3 color;"

                "uniform sampler2D colorMap;"

                "/* Erode main color according to the erode color and threshold */"
                "void erode(vec3 mainColor, vec3 erodeColor)"
                "{"
                "    if(erodeColor.r + threshold >= mainColor.r"
                "    && erodeColor.g + threshold >= mainColor.g"
                "    && erodeColor.b + threshold >= mainColor.b)"
                "    {"
                "        if(erodeColor.r - threshold <= mainColor.r"
                "        && erodeColor.g - threshold <= mainColor.g"
                "        && erodeColor.b - threshold <= mainColor.b)"
                "        {"
                "            discard;"
                "        }"
                "    }"
                "}"

                "void main()"
                "{"
                "    /* Get the correct texture coordinates */"
                "    vec2 texCoords = gl_TexCoord[0].st;"
                "    vec4 mainColor = texture2D(colorMap, texCoords);"

                "    vec3 erodeColor;"
                "    /* If color is not set, get center color to erode */"
                "    if(color.r > 1.0 || color.g > 1.0 || color.b > 1.0)"
                "        erodeColor = texture2D(colorMap, center).rgb;"

                "    /* Filtering inside a circle */"
                "    if(length(gl_TexCoord[0].st - center.xy) <= radius)"
                "        erode(mainColor.rgb, erodeColor);"
                "    gl_FragColor  = mainColor;"
                "}";

        if (pgm->addShaderFromSourceCode(QGLShader::Vertex, vSrc.c_str()))
        {
            if (pgm->addShaderFromSourceCode(QGLShader::Fragment, fSrc.c_str()))
            {
                ok = true;
            }
            else
            {
                std::cerr << "Error loading fragment shader code: " << "\n";
                std::cerr << pgm->log().toStdString();
            }
        }
        else
        {
            std::cerr << "Error loading vertex shader code: " << "\n";
            std::cerr << pgm->log().toStdString();
        }
        if (!ok)
        {
            delete pgm;
            pgm = NULL;
            failed = true;
        }
        else
        {
            pgm->link();

            // Save uniform locations
            uint id = pgm->programId();
            colorMapID  = glGetUniformLocation(id, "colorMap");

            radiusID    = glGetUniformLocation(id, "radius");
            thresholdID = glGetUniformLocation(id, "threshold");
            centerID    = glGetUniformLocation(id, "center");
            colorID     = glGetUniformLocation(id, "color");
        }
    }
}
