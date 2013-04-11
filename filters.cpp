// ****************************************************************************
//  filters.cpp                                                     Tao project
// ****************************************************************************
//
//   File Description:
//
//     Implementation of the XL primitives for the "filters" module.
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

#include "filters.h"
#include <iostream>
#include "coords3d.h"

XL_DEFINE_TRACES

static GLfloat erodeRadius   = 1.0;
static GLfloat erodeColor[3] = {2.0, 2.0, 2.0};

static GLfloat levels[3] = { 0.299, 0.587, 0.114 };

// ============================================================================
//
//   Convolution filters
//
// ============================================================================

Tree_p gaussian(Tree_p, uint unit, uint width, uint height)
// ----------------------------------------------------------------------------
//  Define a gaussian convolution
// ----------------------------------------------------------------------------
{
    // Define a gaussian kernel
    GLfloat kernel[9] = {1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0,
                         2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0,
                         1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0 };

    if (width < 1)  width = 1;
    if (height < 1) height = 1;

    ConvolutionFilter* conv = new ConvolutionFilter(unit, width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.0);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p mean(Tree_p, uint unit, uint width, uint height)
// ----------------------------------------------------------------------------
//  Define a mean convolution
// ----------------------------------------------------------------------------
{
    // Define a mean kernel
    GLfloat kernel[9] = {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                         1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0,
                         1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0};

    if (width < 1)  width = 1;
    if (height < 1) height = 1;

    ConvolutionFilter* conv = new ConvolutionFilter(unit, width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.0);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p emboss(Tree_p, uint unit, uint width, uint height)
// ----------------------------------------------------------------------------
//  Define an emboss convolution
// ----------------------------------------------------------------------------
{
    // Define a emboss kernel
    GLfloat kernel[9] = {2.0,  0.0,  0.0,
                         0.0, -1.0,  0.0,
                         0.0,  0.0, -1.0};

    if (width < 1)  width = 1;
    if (height < 1) height = 1;

    ConvolutionFilter* conv = new ConvolutionFilter(unit, width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.5);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p sharpness(Tree_p, uint unit, uint width, uint height)
// ----------------------------------------------------------------------------
//  Define a sharpness convolution
// ----------------------------------------------------------------------------
{
    // Define a sharpness kernel
    GLfloat kernel[9] = {-1.0, -1.0, -1.0,
                         -1.0,  9.0, -1.0,
                         -1.0, -1.0, -1.0};

    if (width < 1)  width = 1;
    if (height < 1) height = 1;

    ConvolutionFilter* conv = new ConvolutionFilter(unit, width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.0);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p laplacian(Tree_p, uint unit, uint width, uint height)
// ----------------------------------------------------------------------------
//  Define a laplacian convolution
// ----------------------------------------------------------------------------
{
    // Define a laplacian kernel
    GLfloat kernel[9] = {-1.0, -1.0, -1.0,
                         -1.0,  8.0, -1.0,
                         -1.0, -1.0, -1.0};

    if (width < 1)  width = 1;
    if (height < 1) height = 1;

    ConvolutionFilter* conv = new ConvolutionFilter(unit, width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.5);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


// ============================================================================
//
//   Erosion filter
//
// ============================================================================

Tree_p erode_radius(Tree_p, Real_p r)
// ----------------------------------------------------------------------------
//  Set erosion radius
// ----------------------------------------------------------------------------
{
    erodeRadius = r;

    return xl_true;
}


Tree_p erode_color(Tree_p, Real_p r, Real_p g, Real_p b)
// ----------------------------------------------------------------------------
//  Set erosion color. By default, this is the texture color.
// ----------------------------------------------------------------------------
{
    erodeColor[0] = r;
    erodeColor[1] = g;
    erodeColor[2] = b;

    return xl_true;
}


Tree_p erode(Tree_p, uint unit, Real_p x, Real_p y, Real_p threshold)
// ----------------------------------------------------------------------------
//  Define an erosion filter
// ----------------------------------------------------------------------------
{
    Erosion* erosion = new Erosion(unit, x, y, threshold);
    erosion->setColor(erodeColor);
    erosion->setRadius(erodeRadius);

    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              erosion, Filter::delete_callback);
    return xl_true;
}


// ============================================================================
//
//   Black and white filter
//
// ============================================================================

Tree_p black_and_white_levels(Tree_p, Real_p r, Real_p g, Real_p b)
// ----------------------------------------------------------------------------
//  Set black and white levels.
// ----------------------------------------------------------------------------
{
    levels[0] = r;
    levels[1] = g;
    levels[2] = b;

    return xl_true;
}


Tree_p black_and_white(Tree_p, uint unit)
// ----------------------------------------------------------------------------
//  Define a black and white filter
// ----------------------------------------------------------------------------
{
    BlackAndWhite* bw = new BlackAndWhite(unit);
    bw->setLevels(levels);

    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              bw, Filter::delete_callback);
    return xl_true;
}


int module_init(const Tao::ModuleApi *api, const Tao::ModuleInfo *)
// ----------------------------------------------------------------------------
//   Initialize the Tao module
// ----------------------------------------------------------------------------
{
    glewInit();
    XL_INIT_TRACES();

    Filter::tao = api;

    return 0;
}


int module_exit()
// ----------------------------------------------------------------------------
//   Uninitialize the Tao module
// ----------------------------------------------------------------------------
{
    return 0;
}
