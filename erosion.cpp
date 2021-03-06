// *****************************************************************************
// erosion.cpp                                                     Tao3D project
// *****************************************************************************
//
// File description:
//
//   Erosion filter implementation.
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
uint                  Erosion::amountID = 0;
uint                  Erosion::thresholdID = 0;
uint                  Erosion::colorID = 0;
uint                  Erosion::centerID = 0;
const QGLContext*     Erosion::context = NULL;


Erosion::Erosion(float x, float y, float threshold)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Filter(&context), x(x), y(y), threshold(threshold), radius(1.0e6)
{
    IFTRACE(filters)
        debug() << "Create black and white filter" << "\n";

    checkGLContext();
}


Erosion::~Erosion()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{}


void Erosion::setColor(GLfloat erode_color[4])
// ----------------------------------------------------------------------------
//   Set erosion color
// ----------------------------------------------------------------------------
{
    color[0] = erode_color[0];
    color[1] = erode_color[1];
    color[2] = erode_color[2];
    color[3] = erode_color[3];
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
        GL.Uniform(amountID, amount);
        GL.Uniform(thresholdID, threshold);
        GL.Uniform4fv(colorID, 1, color);

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
            "uniform float radius;"
            "uniform float threshold;"
            "uniform float amount;"
            "uniform vec2 center;"
            "uniform vec4 color;"

            "uniform sampler2D colorMap;"

            "void main()"
            "{"
            "    /* Get the correct texture coordinates */"
            "    vec2 texCoords = gl_TexCoord[0].st;"
            "    vec4 mainColor = texture2D(colorMap, texCoords);"
            "    vec4 centerColor = texture2D(colorMap, center);"
            "    vec4 erodeSet = vec4(greaterThan(color, vec4(0)));"
            "    vec4 erodeColor = mix(centerColor, color, erodeSet);"

            "    /* Erode within a circle */"
            "    if (length(texCoords - center) <= radius)"
            "    {"
            "        vec4 cmp = vec4(threshold);"
            "        vec4 dist = abs(erodeColor - mainColor);"
            "        bool keep = !all(lessThanEqual(dist, cmp));"
            "        vec4 transparent = vec4(mainColor.rgb, float(keep));"
            "        mainColor = mix(mainColor, transparent, amount);"
            "    }"
            "    gl_FragColor = mainColor;"
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
            colorMapID  = GL.GetUniformLocation(id, "colorMap");

            radiusID    = GL.GetUniformLocation(id, "radius");
            amountID    = GL.GetUniformLocation(id, "amount");
            thresholdID = GL.GetUniformLocation(id, "threshold");
            centerID    = GL.GetUniformLocation(id, "center");
            colorID     = GL.GetUniformLocation(id, "color");
        }
    }
}
