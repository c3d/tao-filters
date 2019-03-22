// *****************************************************************************
// convolution_filter.cpp                                          Tao3D project
// *****************************************************************************
//
// File description:
//
//   Convolution Filter implementation.
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

#include "convolution_filter.h"

// ============================================================================
//
//   Convolution filters 3x3
//   For further informations, see
//   http://www.opengl.org/resources/code/samples/advanced/advanced97/notes/node152.html
//   or http://stfsworld.com/article20.html
//
// ============================================================================

bool                  ConvolutionFilter::failed = false;
QGLShaderProgram*     ConvolutionFilter::pgm = NULL;
uint                  ConvolutionFilter::widthID = 0;
uint                  ConvolutionFilter::heightID = 0;
uint                  ConvolutionFilter::colorMapID = 0;
uint                  ConvolutionFilter::levelID = 0;
uint                  ConvolutionFilter::amountID = 0;
uint                  ConvolutionFilter::kernelID = 0;
const QGLContext*     ConvolutionFilter::context = NULL;

DLL_PUBLIC Tao::GraphicState * graphic_state = NULL;


ConvolutionFilter::ConvolutionFilter(int w, int h)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Filter(&context), w(w), h(h), level(0.0)
{
    IFTRACE(filters)
        debug() << "Create convolution filter" << "\n";

    checkGLContext();
}


ConvolutionFilter::~ConvolutionFilter()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void ConvolutionFilter::setLevel(float l)
// ----------------------------------------------------------------------------
//  Set the gray level
// ----------------------------------------------------------------------------
{
    level = l;
}


void ConvolutionFilter::setKernel(float* k)
// ----------------------------------------------------------------------------
//  Set the convolution kernel 3x3
// ----------------------------------------------------------------------------
{
    memcpy(kernel, k, sizeof(kernel));
}


void ConvolutionFilter::Draw()
// ----------------------------------------------------------------------------
//   Apply convolution filter
// ----------------------------------------------------------------------------
{
    checkGLContext();

    uint prg_id = 0;
    if(pgm)
        prg_id = pgm->programId();

    if(prg_id)
    {
        IFTRACE(filters)
            debug() << "Apply convolution filter" << "\n";

        // Set shader
        tao->SetShader(prg_id);

        // Set texture parameters
        GL.Uniform(widthID, 1.0f/w);
        GL.Uniform(heightID, 1.0f/h);
        GL.Uniform(colorMapID, 0);

        // Set convolution parameters
        GL.Uniform(levelID, level);
        GL.Uniform(amountID, amount);
        GL.Uniform1fv(kernelID, sizeof(kernel), kernel);
    }
}


void ConvolutionFilter::createShaders()
// ----------------------------------------------------------------------------
//   Create shader programs
// ----------------------------------------------------------------------------
{
    if(!failed)
    {
        IFTRACE(filters)
            debug() << "Create shader for convolution filter" << "\n";

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
            "uniform float pixel_width;"
            "uniform float pixel_height;"
            "varying vec2 texCoord[9];"
            "void main()"
            "{"
            "   gl_Position = ftransform();"

            "   /* Compute texture coordinates */"
            "   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"

            "   vec2 tc = gl_TexCoord[0].st;"
            "   texCoord[0] = tc + vec2(-pixel_width, -pixel_height);"
            "   texCoord[1] = tc + vec2(         0.0, -pixel_height);"
            "   texCoord[2] = tc + vec2( pixel_width, -pixel_height);"
            "   texCoord[3] = tc + vec2(-pixel_width,           0.0);"
            "   texCoord[4] = tc + vec2(         0.0,           0.0);"
            "   texCoord[5] = tc + vec2( pixel_width,           0.0);"
            "   texCoord[6] = tc + vec2(-pixel_width,  pixel_height);"
            "   texCoord[7] = tc + vec2(         0.0,  pixel_height);"
            "   texCoord[8] = tc + vec2( pixel_width,  pixel_height);"
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
            "uniform float pixel_width; "    // Texture width
            "uniform float pixel_height; "   // Texture height
            "uniform float level;"           // Gray level
            "uniform float amount;"
            "uniform float kernel[9];"       // Convolution kernel
            "uniform sampler2D colorMap;"
            "varying vec2 texCoord[9];"

            "void main()"
            "{"
            "   /* Get the correct texture coordinates */"
            "   vec4 source = texture2D(colorMap, texCoord[4]);"
            "   vec4 color = vec4(level) "
            "          + kernel[0] * texture2D(colorMap, texCoord[0])"
            "          + kernel[1] * texture2D(colorMap, texCoord[1])"
            "          + kernel[2] * texture2D(colorMap, texCoord[2])"
            "          + kernel[3] * texture2D(colorMap, texCoord[3])"
            "          + kernel[4] * source"
            "          + kernel[5] * texture2D(colorMap, texCoord[5])"
            "          + kernel[6] * texture2D(colorMap, texCoord[6])"
            "          + kernel[7] * texture2D(colorMap, texCoord[7])"
            "          + kernel[8] * texture2D(colorMap, texCoord[8]);"
            "    gl_FragColor = mix(source, color, amount);"
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
            widthID    = GL.GetUniformLocation(id, "pixel_width");
            heightID   = GL.GetUniformLocation(id, "pixel_height");
            colorMapID = GL.GetUniformLocation(id, "colorMap");
            levelID    = GL.GetUniformLocation(id, "level");
            amountID   = GL.GetUniformLocation(id, "amount");
            kernelID   = GL.GetUniformLocation(id, "kernel");
        }
    }
}
