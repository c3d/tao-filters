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
std::map<text, GLint> Erosion::uniforms;
const QGLContext*     Erosion::context = NULL;

Erosion::Erosion(uint unit, float x, float y, float threshold)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Filter(&context), unit(unit), x(x), y(y), threshold(threshold), radius(1.0)
{
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


void Erosion::render_callback(void *arg)
// ----------------------------------------------------------------------------
//   Rendering callback: call the render function for the object
// ----------------------------------------------------------------------------
{
    ((Erosion *)arg)->Draw();
}


void Erosion::identify_callback(void *)
// ----------------------------------------------------------------------------
//   Identify callback: don't do anything
// ----------------------------------------------------------------------------
{
}


void Erosion::delete_callback(void *arg)
// ----------------------------------------------------------------------------
//   Delete callback: destroy object
// ----------------------------------------------------------------------------
{
    delete (Erosion *)arg;
}


void Erosion::Draw()
// ----------------------------------------------------------------------------
//   Apply Convolution Filter
// ----------------------------------------------------------------------------
{
    if (!tested)
    {
        licensed = tao->checkImpressOrLicense("Filters 1.0");
        tested = true;
    }
    if (!licensed && !tao->blink(1.0, 0.2, 300.0))
        return;

    checkGLContext();

    uint prg_id = 0;
    if(pgm)
        prg_id = pgm->programId();

    if(prg_id)
    {
        tao->SetShader(prg_id);

        // Set texture parameters
        glUniform1i(uniforms["texUnit"], unit);
        glUniform1i(uniforms["colorMap"], unit);

        // Set erosion parameters
        glUniform1f(uniforms["radius"], radius);
        glUniform1f(uniforms["threshold"], threshold);
        glUniform3fv(uniforms["color"], 1, color);

        GLfloat center[2] = {x, y};
        glUniform2fv(uniforms["center"], 1, center);
    }
}


void Erosion::createShaders()
{
    if(!pgm && !failed)
    {
        pgm = new QGLShaderProgram();
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
                "varying vec4 baseColor;"
                "void main()"
                "{"
                "   gl_Position = ftransform();"

                "   /* Compute texture coordinates */"
                "   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
                "   gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;"
                "   gl_TexCoord[2] = gl_TextureMatrix[2] * gl_MultiTexCoord2;"
                "   gl_TexCoord[3] = gl_TextureMatrix[3] * gl_MultiTexCoord3;"

                "   baseColor = gl_Color;"
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

                "uniform int       texUnit;"
                "uniform sampler2D colorMap;"

                "varying vec4 baseColor;"

                "/* Erode main color according to the erode color and threshold */"
                "void erode(vec3 mainColor, vec3 erodeColor)"
                "{"
                    "if(erodeColor.r + threshold >= mainColor.r"
                    "&& erodeColor.g + threshold >= mainColor.g"
                    "&& erodeColor.b + threshold >= mainColor.b)"
                    "{"
                        "if(erodeColor.r - threshold <= mainColor.r"
                        "&& erodeColor.g - threshold <= mainColor.g"
                        "&& erodeColor.b - threshold <= mainColor.b)"
                        "{"
                            "discard;"
                        "}"
                    "}"
                "}"

                "void main()"
                "{"
                    "/* Get the correct texture coordinates */"
                    "vec2 texCoords = vec2(0.0);"
                    "if(texUnit == 0)"
                        "texCoords = gl_TexCoord[0].st;"
                    "if(texUnit == 1)"
                        "texCoords = gl_TexCoord[1].st;"
                    "if(texUnit == 2)"
                        "texCoords = gl_TexCoord[2].st;"
                    "if(texUnit == 3)"
                        "texCoords = gl_TexCoord[3].st;"

                    "vec4 mainColor = texture2D(colorMap, texCoords);"

                    "vec3 erodeColor;"
                    "/* If color is not set, get center color to erode */"
                    "if(color.r > 1.0 || color.g > 1.0 || color.b > 1.0)"
                        "erodeColor = texture2D(colorMap, center).rgb;"

                    "/* Filtering inside a circle */"
                    "if((gl_TexCoord[0].s - center.x) *"
                       "(gl_TexCoord[0].s - center.x) +"
                       "(gl_TexCoord[0].t - center.y) *"
                       "(gl_TexCoord[0].t - center.y) <= radius * radius)"

                        "erode(mainColor.rgb, erodeColor);"

                    "gl_FragColor  = mainColor * baseColor;"
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
            uniforms["texUnit"]   = glGetUniformLocation(id, "texUnit");
            uniforms["colorMap"]  = glGetUniformLocation(id, "colorMap");

            uniforms["radius"]    = glGetUniformLocation(id, "radius");
            uniforms["threshold"] = glGetUniformLocation(id, "threshold");
            uniforms["center"]    = glGetUniformLocation(id, "center");
            uniforms["color"]     = glGetUniformLocation(id, "color");
        }
    }
}

