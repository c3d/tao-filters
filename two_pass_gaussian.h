#ifndef TWO_PASS_GAUSSIAN_H
#define TWO_PASS_GAUSSIAN_H
// *****************************************************************************
// two_pass_gaussian.h                                             Tao3D project
// *****************************************************************************
//
// File description:
//
//     Two-pass gaussian blur
//
//
//
//
//
//
//
//
// *****************************************************************************
// This software is licensed under the GNU General Public License v3
// (C) 2014, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// (C) 2013, Catherine Burvelle <catherine@taodyne.com>
// (C) 2013-2014,2019, Christophe de Dinechin <christophe@dinechin.org>
// (C) 2014, Jérôme Forissier <jerome@taodyne.com>
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

struct TwoPassGaussian : public Filter
// ----------------------------------------------------------------------------
//    Horizontal or vertical gaussian filter
// ----------------------------------------------------------------------------
{
    TwoPassGaussian(uint w, uint h, uint n, bool vertical);
    ~TwoPassGaussian();

    enum { MAX_SAMPLES = 64 };

    // Draw the given filter
    virtual void        Draw();

protected:
    virtual void        createShaders();
    QGLShaderProgram *  shader();

private:
    uint   width, height; // texture parameters
    uint   samples;
    bool   vertical;

    static const QGLContext* context;
    static QGLShaderProgram* pgm[MAX_SAMPLES];
    static uint              textureID[MAX_SAMPLES];
    static uint              deltaID[MAX_SAMPLES];

};




#endif // TWO_PASS_GAUSSIAN_H
