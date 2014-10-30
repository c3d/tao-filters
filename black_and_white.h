#ifndef BLACK_AND_WHITE_H
#define BLACK_AND_WHITE_H
// ****************************************************************************
//  black_and_white.h                                               Tao project
// ****************************************************************************
//
//   File Description:
//
//      Define a black and white filter.
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

struct BlackAndWhite : public Filter
{
    BlackAndWhite(GLfloat levels[4]);
    ~BlackAndWhite();

    void setLevels(GLfloat color_levels[4]);

    // Draw black and white filter
    virtual void    Draw();

protected:
    virtual void    createShaders();

private:
    GLfloat levels[4];  // color levels

    static bool failed;
    static QGLShaderProgram* pgm;
    static uint colorMapID, levelsID, amountID;
    static const QGLContext* context;
};


#endif // CEL_SHADING_H
