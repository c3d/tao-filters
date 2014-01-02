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


// ============================================================================
//
//   Controling the filtering amount
//
// ============================================================================

Tree_p filtering_amount(Tree_p /* self */, scale a)
// ----------------------------------------------------------------------------
//   Set the filtering amount to the given value
// ----------------------------------------------------------------------------
{
    Filter::amount = a;
    return XL::xl_true;
}


Real_p filtering_amount(Tree_p self)
// ----------------------------------------------------------------------------
//   Return the current filtering amount
// ----------------------------------------------------------------------------
{
    return new Real(Filter::amount, self->Position());
}



// ============================================================================
//
//    Horizontal or vertical blur filter
//
// ============================================================================

Tree_p gaussian_pass(uint w, uint h, uint n, bool vert)
// ----------------------------------------------------------------------------
//  Define a single-direction gaussian filter
// ----------------------------------------------------------------------------
{
    // Check parameters
    if (w < 1)  w = 1;
    if (h < 1)  h = 1;
    if (n < 1)  n = 1;
    if (n > TwoPassGaussian::MAX_SAMPLES) n = TwoPassGaussian::MAX_SAMPLES;

    TwoPassGaussian *gauss = new TwoPassGaussian(w, h, n, vert);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              gauss, Filter::delete_callback);
    return xl_true;
}



// ============================================================================
//
//   Convolution filters
//
// ============================================================================

Tree_p gaussian(uint width, uint height)
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

    ConvolutionFilter* conv = new ConvolutionFilter(width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.0);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p mean(uint width, uint height)
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

    ConvolutionFilter* conv = new ConvolutionFilter(width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.0);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p emboss(uint width, uint height)
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

    ConvolutionFilter* conv = new ConvolutionFilter(width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.5);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p sharpness(uint width, uint height)
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

    ConvolutionFilter* conv = new ConvolutionFilter(width, height);
    conv->setKernel(kernel);
    conv->setLevel(0.0);
    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              conv, Filter::delete_callback);
    return xl_true;
}


Tree_p laplacian(uint width, uint height)
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

    ConvolutionFilter* conv = new ConvolutionFilter(width, height);
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

static GLfloat erodeRadius   = 1.0e6;
static GLfloat erodeColor[4] = { -1, -1, -1, -1 };

Tree_p erode_radius(double r)
// ----------------------------------------------------------------------------
//  Set erosion radius
// ----------------------------------------------------------------------------
{
    erodeRadius = r;
    return xl_true;
}


Tree_p erode_color(double r, double g, double b, double a)
// ----------------------------------------------------------------------------
//  Set erosion color. By default, this is the texture color.
// ----------------------------------------------------------------------------
{
    erodeColor[0] = r;
    erodeColor[1] = g;
    erodeColor[2] = b;
    erodeColor[3] = a;
    return xl_true;
}


Tree_p erode(double x, double y, double threshold)
// ----------------------------------------------------------------------------
//  Define an erosion filter
// ----------------------------------------------------------------------------
{
    Erosion* erosion = new Erosion(x, y, threshold);
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

static GLfloat levels[4] = { 0.299, 0.587, 0.114, 0.0 };

Tree_p black_and_white_levels(double r, double g, double b, double a)
// ----------------------------------------------------------------------------
//  Set black and white levels.
// ----------------------------------------------------------------------------
{
    levels[0] = r;
    levels[1] = g;
    levels[2] = b;
    levels[3] = a;
    return xl_true;
}


Tree_p black_and_white()
// ----------------------------------------------------------------------------
//  Define a black and white filter
// ----------------------------------------------------------------------------
{
    BlackAndWhite* bw = new BlackAndWhite(levels);

    Filter::tao->AddToLayout2(Filter::render_callback,
                              Filter::identify_callback,
                              bw, Filter::delete_callback);
    return xl_true;
}



// ============================================================================
//
//    Module initialization
//
// ============================================================================

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
