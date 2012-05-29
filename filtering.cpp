// ****************************************************************************
//  filtering.cpp                                                   Tao project
// ****************************************************************************
//
//   File Description:
//
//   Filtering implementation.
//
//
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
#include "filtering.h"

const Tao::ModuleApi *Filter::tao = NULL;

bool Filter::tested = false;
bool Filter::licensed = false;

// ============================================================================
//
//    Filter
//
// ============================================================================

Filter::Filter(const QGLContext **pcontext)
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
    : pcontext(pcontext)
{
}


Filter::~Filter()
// ----------------------------------------------------------------------------
//   Destruction
// ----------------------------------------------------------------------------
{
}


void Filter::render_callback(void *arg)
// ----------------------------------------------------------------------------
//   Rendering callback: call the render function for the object
// ----------------------------------------------------------------------------
{
    ((Filter *)arg)->Draw();
}


void Filter::identify_callback(void *arg)
// ----------------------------------------------------------------------------
//   Identify callback: don't do anything
// ----------------------------------------------------------------------------
{
    (void) arg;
}


void Filter::delete_callback(void *arg)
// ----------------------------------------------------------------------------
//   Delete callback: destroy object
// ----------------------------------------------------------------------------
{
    delete (Filter *)arg;
}


void Filter::Draw()
// ----------------------------------------------------------------------------
//   Draw filter
// ----------------------------------------------------------------------------
{
}


void Filter::checkGLContext()
// ----------------------------------------------------------------------------
//   Re-create context-dependent resources if GL context has changed
// ----------------------------------------------------------------------------
{
    tao->makeGLContextCurrent();
    if (*pcontext != QGLContext::currentContext())
    {
        IFTRACE(filters)
                debug() << "Context has changed" << "\n";

        *pcontext = QGLContext::currentContext();
        createShaders();
    }
}


void Filter::createShaders()
// ----------------------------------------------------------------------------
//   Create shader programs for shading effect
// ----------------------------------------------------------------------------
{
}


std::ostream & Filter::debug()
// ----------------------------------------------------------------------------
//   Convenience method to log with a common prefix
// ----------------------------------------------------------------------------
{
    std::cerr << "[Filters] " << (void*)this << " ";
    return std::cerr;
}
