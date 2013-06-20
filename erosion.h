#ifndef EROSION_H
#define EROSION_H
// ****************************************************************************
//  erosion.h                                                       Tao project
// ****************************************************************************
//
//   File Description:
//
//      Define an erosion filter.
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

struct Erosion : public Filter
{
    Erosion(uint unit, float x, float y, float threshold);
    ~Erosion();

    void setColor(GLfloat erode_color[3]);
    void setRadius(float radius);

    // Draw erosion filter
    virtual void    Draw();

protected:
    virtual void    createShaders();

private:
    uint    unit;      // texture parameters
    GLfloat color[3];  // erosion color
    float   x, y;      // erosion center
    float   threshold; // erosion threshold
    float   radius;    // erosion radius

    static bool failed;
    static QGLShaderProgram* pgm;
    static std::map<text, GLint> uniforms;
    static const QGLContext* context;
};


#endif // CEL_SHADING_H
