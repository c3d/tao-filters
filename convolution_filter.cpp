// ****************************************************************************
//  convolution_filter.cpp                                          Tao project
// ****************************************************************************
//
//   File Description:
//
//   Convolution Filter implementation.
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
std::map<text, GLuint> ConvolutionFilter::uniforms;
const QGLContext*     ConvolutionFilter::context = NULL;


#define GL (*graphic_state)
DLL_PUBLIC Tao::GraphicState * graphic_state = NULL;


ConvolutionFilter::ConvolutionFilter(int unit, int w, int h)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : Filter(&context), unit(unit), w(w), h(h), level(0.0)
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
    if (!tested)
    {
        licensed = tao->checkImpressOrLicense("Filters 1.005");
        tested = true;
    }

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
        GL.Uniform(uniforms["width"], w);
        GL.Uniform(uniforms["height"], h);
        GL.Uniform(uniforms["texUnit"], unit);
        GL.Uniform(uniforms["colorMap"], unit);

        // Set convolution parameters
        GL.Uniform(uniforms["level"], level);
        GL.Uniform1fv(uniforms["kernel"], sizeof(kernel), kernel);
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
                "uniform int   width; "    //Texture width
                "uniform int   height; "   //Texture height
                "uniform float level;"     //Gray level
                "uniform float kernel[9];" //Convolution kernel

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

                "   /* Size of a pixel */"
                "   float pixel_w = 1.0 / float(width);"
                "   float pixel_h = 1.0 / float(height);"

                "   int i = 0;"
                "   vec4 sum = vec4(0.0);"

                "   /* Compute offset */ "
                "   vec2 offset[9];"
                "   offset[0] = vec2(-pixel_w, -pixel_h);"
                "   offset[1] = vec2(0.0, -pixel_h);"
                "   offset[2] = vec2(pixel_w, -pixel_h);"

                "   offset[3] = vec2(-pixel_w, 0.0);"
                "   offset[4] = vec2(0.0, 0.0);"
                "   offset[5] = vec2(pixel_w, 0.0);"

                "   offset[6] = vec2(-pixel_w, pixel_h);"
                "   offset[7] = vec2(0.0, pixel_h);"
                "   offset[8] = vec2(pixel_w, pixel_h);"

                "   /* Apply filter to the current map */ "
                "   for( i=0; i < 9; i++ )"
                "       sum += texture2D(colorMap, texCoords + offset[i]) * kernel[i];"

                "   /* Add gray level */"
                "   sum += level;"

                "   gl_FragColor = vec4(sum.rgb, 1.0);"
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
            uniforms["width"]    = glGetUniformLocation(id, "width");
            uniforms["height"]   = glGetUniformLocation(id, "height");
            uniforms["texUnit"]  = glGetUniformLocation(id, "texUnit");
            uniforms["colorMap"] = glGetUniformLocation(id, "colorMap");

            uniforms["level"]    = glGetUniformLocation(id, "level");
            uniforms["kernel"]   = glGetUniformLocation(id, "kernel");
        }
    }
}
