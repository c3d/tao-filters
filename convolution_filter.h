#ifndef CONVOLUTION_FILTER_H
#define CONVOLUTION_FILTER_H
// ****************************************************************************
//  convolution_filter.h                                            Tao project
// ****************************************************************************
//
//   File Description:
//
//      Define a convolution filter.
//
//
//
//
//
// ****************************************************************************
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriÃ©tÃ© de Taodyne SAS - Confidentiel
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

#include "tao/coords3d.h"
#include "tao/module_api.h"
#include "tao/tao_gl.h"
#include "filtering.h"

using namespace std;
using namespace Tao;


struct ConvolutionFilter : public Filter
{
    ConvolutionFilter(uint unit, uint w, uint h);
    ~ConvolutionFilter();

    void setLevel(float l);
    void setKernel(float* k);

    // Draw convolution filter
    virtual void    Draw();

protected:
    virtual void    createShaders();

private:
    uint  unit, w, h; // texture parameters
    float level;      // gray level
    float kernel[9];  // convolution kernel

    static bool failed;
    static QGLShaderProgram* pgm;
    static std::map<text, GLint> uniforms;
    static const QGLContext* context;
};


#endif // CEL_SHADING_H
