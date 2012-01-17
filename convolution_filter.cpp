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
std::map<text, GLint> ConvolutionFilter::uniforms;

ConvolutionFilter::ConvolutionFilter(uint unit, uint w, uint h)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : unit(unit), w(w), h(h), level(0.0)
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
                "varying vec4 color;"
                "void main()"
                "{"
                "   gl_Position = ftransform();"

                "   /* Compute texture coordinates */"
                "   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
                "   gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;"
                "   gl_TexCoord[2] = gl_TextureMatrix[2] * gl_MultiTexCoord2;"
                "   gl_TexCoord[3] = gl_TextureMatrix[3] * gl_MultiTexCoord3;"

                "   color = gl_Color;"
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

                "varying vec4 color;"
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

                "   gl_FragColor = vec4(sum.rgb, 1.0) * color;"
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
            uniforms["height"] = glGetUniformLocation(id, "height");
            uniforms["texUnit"]  = glGetUniformLocation(id, "texUnit");
            uniforms["colorMap"] = glGetUniformLocation(id, "colorMap");

            uniforms["level"]    = glGetUniformLocation(id, "level");
            uniforms["kernel"]     = glGetUniformLocation(id, "kernel");
        }
    }
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


void ConvolutionFilter::render_callback(void *arg)
// ----------------------------------------------------------------------------
//   Rendering callback: call the render function for the object
// ----------------------------------------------------------------------------
{
    ((ConvolutionFilter *)arg)->Draw();
}


void ConvolutionFilter::identify_callback(void *)
// ----------------------------------------------------------------------------
//   Identify callback: don't do anything
// ----------------------------------------------------------------------------
{
}


void ConvolutionFilter::delete_callback(void *arg)
// ----------------------------------------------------------------------------
//   Delete callback: destroy object
// ----------------------------------------------------------------------------
{
    delete (ConvolutionFilter *)arg;
}


void ConvolutionFilter::Draw()
// ----------------------------------------------------------------------------
//   Apply Convolution Filter
// ----------------------------------------------------------------------------
{
    if (!tested)
    {
        licensed = tao->checkLicense("Filters 1.0", false);
        tested = true;
    }
    if (!licensed && !tao->blink(1.0, 0.2))
        return;

    uint prg_id = 0;
    if(pgm)
        prg_id = pgm->programId();

    if(prg_id)
    {
        tao->SetShader(prg_id);

        // Set texture parameters
        glUniform1i(uniforms["width"], w);
        glUniform1i(uniforms["height"], h);
        glUniform1i(uniforms["texUnit"], unit);
        glUniform1i(uniforms["colorMap"], unit);

        // Set convolution parameters
        glUniform1f(uniforms["level"], level);
        glUniform1fv(uniforms["kernel"], sizeof(kernel), kernel);
    }
}

