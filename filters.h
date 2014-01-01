#ifndef FILTERS_H
#define FILTERS_H
// ****************************************************************************
//  filters.h                                                       Tao project
// ****************************************************************************
//
//   File Description:
//
//    Prototype of the function used by filters.tbl to
//    implement the new XL primitive
//
//
//
//
//
//
// ****************************************************************************
// This software is property of Taodyne SAS - Confidential
// Ce logiciel est la propriété de Taodyne SAS - Confidentiel
//  (C) 1992-2010 Christophe de Dinechin <christophe@taodyne.com>
//  (C) 2010 Jerome Forissier <jerome@taodyne.com>
//  (C) 2011 Baptiste Soulisse <baptiste.soulisse@taodyne.com>
//  (C) 2011 Taodyne SAS
// ****************************************************************************
#include "tree.h"
#include "main.h"
#include "runtime.h"
#include "base.h"
#include "tao/module_api.h"
#include "filtering.h"
#include "two_pass_gaussian.h"
#include "convolution_filter.h"
#include "black_and_white.h"
#include "erosion.h"

using namespace XL;

// Two-pass gaussian filter
Tree_p gaussian_pass(uint width, uint height, uint n, bool vertical);

// Convolution filters
Tree_p gaussian(uint width, uint height);
Tree_p mean(uint width, uint height);
Tree_p emboss(uint width, uint height);
Tree_p sharpness(uint width, uint height);
Tree_p laplacian(uint width, uint height);

// Erosion filter
Tree_p erode_radius(double r);
Tree_p erode_color(double r, double g, double b);
Tree_p erode(double x, double y, double threshold);

// Black and white filter
Tree_p black_and_white_levels(double r, double g, double b);
Tree_p black_and_white();

#endif
