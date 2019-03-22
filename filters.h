#ifndef FILTERS_H
#define FILTERS_H
// *****************************************************************************
// filters.h                                                       Tao3D project
// *****************************************************************************
//
// File description:
//
//    Prototype of the function used by filters.tbl to
//    implement the new XL primitive
//
//
//
//
//
//
// *****************************************************************************
// This software is licensed under the GNU General Public License v3
// (C) 2011-2012,2014, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// (C) 2011-2013, Catherine Burvelle <catherine@taodyne.com>
// (C) 2011-2014,2019, Christophe de Dinechin <christophe@dinechin.org>
// (C) 2011-2012,2014, Jérôme Forissier <jerome@taodyne.com>
// (C) 2011-2012,2014, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
// *****************************************************************************
// This file is part of Tao3D
//
// Tao3D is free software: you can r redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Tao3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Tao3D, in a file named COPYING.
// If not, see <https://www.gnu.org/licenses/>.
// *****************************************************************************
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

// Filtering amount
Tree_p filtering_amount(Tree_p self, scale a);
Real_p filtering_amount(Tree_p self);

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
Tree_p erode_color(double r, double g, double b, double a);
Tree_p erode(double x, double y, double threshold);

// Black and white filter
Tree_p black_and_white_levels(double r, double g, double b, double a);
Tree_p black_and_white();

#endif
