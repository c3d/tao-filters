// ****************************************************************************
//  black_and_white.cpp                                             Tao project
// ****************************************************************************
//
//   File Description:
//
//   Black and white filter implementation.
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
#include "black_and_white.h"

// ============================================================================
//
//   Black and White filter
//
// ============================================================================

bool                  BlackAndWhite::failed = false;
QGLShaderProgram*     BlackAndWhite::pgm = NULL;
std::map<text, GLint> BlackAndWhite::uniforms;
const QGLContext*     BlackAndWhite::context = NULL;


#define GL (*graphic_state)

BlackAndWhite::BlackAndWhite(int unit)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Filter(&context), unit(unit)
{
    IFTRACE(filters)
            debug() << "Create black and white filter" << "\n";

    checkGLContext();
}


BlackAndWhite::~BlackAndWhite()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void BlackAndWhite::setLevels(GLfloat color_levels[3])
// ----------------------------------------------------------------------------
//   Set color levels
// ----------------------------------------------------------------------------
{
    levels[0] = color_levels[0];
    levels[1] = color_levels[1];
    levels[2] = color_levels[2];
}


void BlackAndWhite::Draw()
// ----------------------------------------------------------------------------
//   Apply black and white filter
// ----------------------------------------------------------------------------
{
    checkGLContext();

    uint prg_id = 0;
    if(pgm)
        prg_id = pgm->programId();

    if(prg_id)
    {
        IFTRACE(filters)
                debug() << "Apply black and white filter" << "\n";

        // Set shader
        tao->SetShader(prg_id);

        // Set texture parameters
        GL.Uniform(uniforms["texUnit"], unit);
        GL.Uniform(uniforms["colorMap"], unit);

        // Set erosion parameters
        GL.Uniform3fv(uniforms["levels"], 1, levels);
    }
}


void BlackAndWhite::createShaders()
// ----------------------------------------------------------------------------
//   Create shader programs
// ----------------------------------------------------------------------------
{
    if(!failed)
    {
        IFTRACE(filters)
                debug() << "Create shader for black and white filter" << "\n";

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
                "uniform vec3 levels;"

                "uniform int       texUnit;"
                "uniform sampler2D colorMap;"

                "void main()"
                "{"
                "   /* Get the correct texture coordinates */"
                "   vec2 texCoords = vec2(0.0);"
                "   if(texUnit == 0)"
                "       texCoords = gl_TexCoord[0].st;"
                "   if(texUnit == 1)"
                "       texCoords = gl_TexCoord[1].st;"
                "   if(texUnit == 2)"
                "       texCoords = gl_TexCoord[2].st;"
                "   if(texUnit == 3)"
                "       texCoords = gl_TexCoord[3].st;"

                "   vec4 color = texture2D( colorMap, texCoords );"

                "   /* Define color levels */"
                "   vec3 red   = vec3(color.r, color.r, color.r);"
                "   vec3 green = vec3(color.g, color.g, color.g);"
                "   vec3 blue  = vec3(color.b, color.b, color.b);"

                "   gl_FragColor = vec4(levels.r * red + levels.g * green +  levels.b * blue, 1.0);"
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
            uniforms["texUnit"]  = glGetUniformLocation(id, "texUnit");
            uniforms["colorMap"] = glGetUniformLocation(id, "colorMap");
            uniforms["levels"]   = glGetUniformLocation(id, "levels");
        }
    }
}
