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
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
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
    ConvolutionFilter(int w, int h);
    ~ConvolutionFilter();

    void setLevel(float l);
    void setKernel(float* k);

    // Draw convolution filter
    virtual void    Draw();

protected:
    virtual void    createShaders();

private:
    int   w, h;                 // Texture size
    float level;                // Gray level
    float kernel[9];            // Convolution kernel

    static bool failed;
    static QGLShaderProgram* pgm;
    static uint widthID, heightID, colorMapID, levelID, amountID, kernelID;
    static const QGLContext* context;
};


#endif // CONVOLUTION_FILTER_H
