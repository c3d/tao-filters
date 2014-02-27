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
    Erosion(float x, float y, float threshold);
    ~Erosion();

    void setColor(GLfloat erode_color[4]);
    void setRadius(float radius);

    // Draw erosion filter
    virtual void    Draw();

protected:
    virtual void    createShaders();

private:
    GLfloat color[4];           // Erosion color
    float   x, y;               // Erosion center
    float   threshold;          // Erosion threshold
    float   radius;             // Erosion radius

    static bool failed;
    static QGLShaderProgram* pgm;
    static uint colorMapID, radiusID, amountID, thresholdID, colorID, centerID;
    static const QGLContext* context;
};


#endif // CEL_SHADING_H
