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
#include "convolution_filter.h"
#include "erosion.h"
#include "black_and_white.h"

using namespace XL;

// Convolution filters
Tree_p gaussian(Tree_p, uint unit, uint width, uint height);
Tree_p mean(Tree_p, uint unit, uint width, uint height);
Tree_p emboss(Tree_p, uint unit, uint width, uint height);
Tree_p sharpness(Tree_p, uint unit, uint width, uint height);
Tree_p laplacian(Tree_p, uint unit, uint width, uint height);

// Erosion filter
Tree_p erode_radius(Tree_p, Real_p r);
Tree_p erode_color(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p erode(Tree_p, uint unit, Real_p x, Real_p y, Real_p threshold);

// Black and white filter
Tree_p black_and_white_levels(Tree_p, Real_p r, Real_p g, Real_p b);
Tree_p black_and_white(Tree_p, uint unit);

#endif
