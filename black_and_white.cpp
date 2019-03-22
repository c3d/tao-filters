// *****************************************************************************
// black_and_white.cpp                                             Tao3D project
// *****************************************************************************
//
// File description:
//
//   Black and white filter implementation.
//
//
//
//
//
//
//
// *****************************************************************************
// This software is licensed under the GNU General Public License v3
// (C) 2011-2014, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// (C) 2011-2013, Catherine Burvelle <catherine@taodyne.com>
// (C) 2011-2014,2019, Christophe de Dinechin <christophe@dinechin.org>
// (C) 2011-2014, Jérôme Forissier <jerome@taodyne.com>
// (C) 2011-2014, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// *****************************************************************************
// This file is part of Tao3D
//
// Tao3D is free software: you can r redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tao3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Tao3D, in a file named COPYING.
// If not, see <https://www.gnu.org/licenses/>.
// *****************************************************************************
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
                "** This file is part of the Tao3D application, developped by Taodyne.\n"
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
                "** This file is part of the Tao3D application, developped by Taodyne.\n"
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
            colorMapID = GL.GetUniformLocation(id, "colorMap");
            levelsID   = GL.GetUniformLocation(id, "levels");
            amountID   = GL.GetUniformLocation(id, "amount");
        }
    }
}
