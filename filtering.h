#ifndef FILTERING_H
#define FILTERING_H
// ****************************************************************************
//  filtering.h                                                     Tao project
// ****************************************************************************
//
//   File Description:
//
//      Define a filtering technique.
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
#include "tao/graphic_state.h"
#include <QGLContext>
#include <QGLShaderProgram>

using namespace std;
using namespace Tao;


struct Filter
{
    Filter(const QGLContext **pcontext = NULL);
    virtual ~Filter();

    // Draw filter
    virtual void    Draw();

    // Re-create shaders if GL context has changed
    void            checkGLContext();
    virtual void    createShaders();

    std::ostream &  debug();

    static void     render_callback(void *arg);
    static void     identify_callback(void *arg);
    static void     delete_callback(void *arg);

public:
    const QGLContext    **pcontext;

public:
    // Pointer to Tao functions
    static const Tao::ModuleApi *tao;
    static float                 amount;
};

#endif
