#ifndef TWO_PASS_GAUSSIAN_H
#define TWO_PASS_GAUSSIAN_H
// ****************************************************************************
//  two_pass_gaussian.h                                            Tao project
// ****************************************************************************
//
//   File Description:
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
// ****************************************************************************
// This software is licensed under the GNU General Public License v3.
// See file COPYING for details.
//  (C) 2011 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

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
