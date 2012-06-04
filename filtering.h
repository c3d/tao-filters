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
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriÃ©tÃ© de Taodyne SAS - Confidentiel
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************

#include "tao/coords3d.h"
#include "tao/module_api.h"
#include "tao/tao_gl.h"
#include <QObject>

using namespace std;
using namespace Tao;

struct Filter : public QObject
{
    Filter(const QGLContext **pcontext = NULL);
    ~Filter();

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
    static bool tested, licensed;

    // Pointer to Tao functions
    static const Tao::ModuleApi *tao;
};



#endif
