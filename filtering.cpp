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

Filter::Filter()
// ----------------------------------------------------------------------------
//   Construction
// ----------------------------------------------------------------------------
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


void Filter::identify_callback(void *)
// ----------------------------------------------------------------------------
//   Identify callback: don't do anything
// ----------------------------------------------------------------------------
{
}


void Filter::delete_callback(void *arg)
// ----------------------------------------------------------------------------
//   Delete callback: destroy object
// ----------------------------------------------------------------------------
{
    delete (Filter *)arg;
}


void Filter::Draw()
{
}
