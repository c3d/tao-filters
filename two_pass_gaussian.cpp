// ****************************************************************************
//  two_pass_gaussian.cpp                                          Tao project 
// ****************************************************************************
// 
//   File Description:
// 
//     Two-pass gaussian filter
// 
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
//  (C) 2011 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

#include "two_pass_gaussian.h"
#include "tao/tao_gl.h"
#include <cmath>
#include <sstream>
#include <iomanip>


const QGLContext*       TwoPassGaussian::context = NULL;
QGLShaderProgram*       TwoPassGaussian::pgm[MAX_SAMPLES] = { NULL };
uint                    TwoPassGaussian::textureID[MAX_SAMPLES] = { 0 };
uint                    TwoPassGaussian::deltaID[MAX_SAMPLES] = { 0 };


TwoPassGaussian::TwoPassGaussian(uint w, uint h, uint n, bool vert)
// ----------------------------------------------------------------------------
//   Two pass gaussian filter
// ----------------------------------------------------------------------------
    : Filter(&context), width(w), height(h), samples(n), vertical(vert)
{}


TwoPassGaussian::~TwoPassGaussian()
// ----------------------------------------------------------------------------
//   Destructor does nothing
// ----------------------------------------------------------------------------
{}


void TwoPassGaussian::createShaders()
// ----------------------------------------------------------------------------
//   When changing GL context, erase older GLSL programs
// ----------------------------------------------------------------------------
{
    IFTRACE(filters)
        debug() << "Create shader for two-pass gaussian filter\n";
    for (uint i = 0; i < MAX_SAMPLES; i++)
    {
        delete pgm[i];
        pgm[i] = NULL;
    }
}


QGLShaderProgram *TwoPassGaussian::shader()
// ----------------------------------------------------------------------------
//   Create the shader for the current number of samples
// ----------------------------------------------------------------------------
{
    uint s = samples-1;
    if (!pgm[s])
    {
        std::ostringstream vertex, fragment;

        // Compute the gauss multiplicative factors
        float gaussFactor[64] = { 0 };
        float scale = -1.0 / (0.2*samples * samples);
        float mid = 0.5 * (samples-1);
        float sum = 0.0;
        for (uint i = 0; i < samples; i++)
        {
            gaussFactor[i] = exp(scale * (i-mid)*(i-mid));
            sum += gaussFactor[i];
        }
        for (uint i = 0; i < samples; i++)
            gaussFactor[i] /= sum;

        // Compute the vertex shader
        vertex <<
            "/* Copyright (C) 2013 Taodyne SAS - All rights reserved */\n"
            "uniform vec2 delta;\n"
            "varying vec2 texCoord[" << samples << "];\n"
            "void main()\n"
            "{\n"
            "    gl_Position = ftransform();\n"
            "    vec4 tc4 = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
            "    vec2 tc = tc4.st;\n";
        for (uint i = 0; i < samples; i++)
            vertex << "    texCoord[" << i << "] = tc + "
                   << std::fixed << std::setprecision(11)
                   << (i - mid) << " * delta;\n";
        vertex <<
            "}\n";

        // Compute the fragment shader
        fragment <<
            "/* Copyright (C) 2013 Taodyne - All rights reserved */\n"
            "uniform sampler2D texture;\n"
            "varying vec2 texCoord[" << samples << "];\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor =\n";
        for (uint i = 0; i < samples; i++)
            fragment << (i > 0 ? "\n       + " : "         ") <<
                "texture2D(texture, texCoord[" << i << "]) * " <<
                std::fixed << std::setprecision(11) <<
                gaussFactor[i];
        fragment <<
            ";\n"
            "}";

        text vSrc = vertex.str();
        text fSrc = fragment.str();

        IFTRACE(filters)
            debug() << "TWO-PASS GAUSSIAN - VERTEX:\n" << vSrc
                      << "\n\nTWO_PASS_GAUSSIAN - FRAGMENT:\n" << fSrc << "\n";


        QGLShaderProgram *p = new QGLShaderProgram(context);
        if (!p->addShaderFromSourceCode(QGLShader::Vertex, vSrc.c_str())   ||
            !p->addShaderFromSourceCode(QGLShader::Fragment, fSrc.c_str()) ||
            !p->link())
        {
            text error = p->log().toUtf8().constData();
            debug() << "Error building shader for two-pass gaussian filter:\n";
            debug() << error << "\n";
            delete p;
            return NULL;
        }

        uint pid = p->programId();
        textureID[s]   = GL.GetUniformLocation(pid, "texture");
        deltaID[s]     = GL.GetUniformLocation(pid, "delta");

        // Store for next time
        pgm[s] = p;
    }
    return pgm[s];
}


void TwoPassGaussian::Draw()
// ----------------------------------------------------------------------------
//    Draw the given pass for the gaussian pass
// ----------------------------------------------------------------------------
{
    checkGLContext();
    if (QGLShaderProgram *p = shader())
    {
        uint pid = p->programId();
        if (pid)
        {
            tao->SetShader(pid);

            uint s = samples-1;
            GL.Uniform(textureID[s], 0);
            if (vertical)
                GL.Uniform(deltaID[s], 0.0f, 1.0f / height);
            else
                GL.Uniform(deltaID[s], 1.0f / width, 0.0f);
        }
    }
}


