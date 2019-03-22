#ifndef CONVOLUTION_FILTER_H
#define CONVOLUTION_FILTER_H
// *****************************************************************************
// convolution_filter.h                                            Tao3D project
// *****************************************************************************
//
// File description:
//
//      Define a convolution filter.
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
