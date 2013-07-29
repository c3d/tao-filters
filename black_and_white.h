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
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriété de Taodyne SAS - Confidentiel
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
    BlackAndWhite(int unit);
    ~BlackAndWhite();

    void setLevels(GLfloat color_levels[3]);

    // Draw black and white filter
    virtual void    Draw();

protected:
    virtual void    createShaders();

private:
    int    unit;       // texture parameters
    GLfloat levels[3];  // color levels

    static bool failed;
    static QGLShaderProgram* pgm;
    static std::map<text, GLint> uniforms;
    static const QGLContext* context;
};


#endif // CEL_SHADING_H
