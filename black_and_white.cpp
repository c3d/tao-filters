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
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
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
uint                  BlackAndWhite::colorMapID = 0;
uint                  BlackAndWhite::levelsID = 0;
uint                  BlackAndWhite::amountID = 0;
const QGLContext*     BlackAndWhite::context = NULL;


#define GL (*graphic_state)

BlackAndWhite::BlackAndWhite(GLfloat color_levels[4])
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Filter(&context)
{
    IFTRACE(filters)
        debug() << "Create black and white filter" << "\n";
    setLevels(color_levels);
    checkGLContext();
}


BlackAndWhite::~BlackAndWhite()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{}


void BlackAndWhite::setLevels(GLfloat color_levels[4])
// ----------------------------------------------------------------------------
//   Set color levels
// ----------------------------------------------------------------------------
{
    levels[0] = color_levels[0];
    levels[1] = color_levels[1];
    levels[2] = color_levels[2];
    levels[3] = color_levels[3];
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
        GL.Uniform(colorMapID, 0);

        // Set colorization parameters
        GL.Uniform4fv(levelsID, 1, levels);
        GL.Uniform(amountID, amount);
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
                "   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
                "   gl_FrontColor = gl_BackColor = gl_Color;"
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
                "uniform vec4 levels;"
                "uniform float amount;"
                "uniform sampler2D colorMap;"
                "void main()"
                "{"
                "   /* Get the correct texture coordinates */"
                "   vec2 texCoords = gl_TexCoord[0].st;"
                "   vec4 color = texture2D(colorMap, texCoords);"
                "   float bw = dot(levels, color);"
                "   vec4 tinted = vec4(bw * gl_Color.rgb, gl_Color.a);"
                "   gl_FragColor = mix(color, tinted, amount);"
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
            colorMapID = glGetUniformLocation(id, "colorMap");
            levelsID   = glGetUniformLocation(id, "levels");
            amountID   = glGetUniformLocation(id, "amount");
        }
    }
}
