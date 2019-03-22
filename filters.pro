# ******************************************************************************
# filters.pro                                                      Tao3D project
# ******************************************************************************
#
# File description:
# Qt build file for the Filters module
#
#
#
#
#
#
#
# ******************************************************************************
# This software is licensed under the GNU General Public License v3
# (C) 2011-2014, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
# (C) 2011-2013, Catherine Burvelle <catherine@taodyne.com>
# (C) 2011-2015,2019, Christophe de Dinechin <christophe@dinechin.org>
# (C) 2011-2014, Jérôme Forissier <jerome@taodyne.com>
# (C) 2011-2014, Baptiste Soulisse <baptiste.soulisse@taodyne.com>
# ******************************************************************************
# This file is part of Tao3D
#
# Tao3D is free software: you can r redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Tao3D is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Tao3D, in a file named COPYING.
# If not, see <https://www.gnu.org/licenses/>.
# ******************************************************************************

MODINSTDIR = filters

include(../modules.pri)



INCLUDEPATH += $${TAOTOPSRC}/tao/include/tao/
HEADERS = \
          filters.h \
          filtering.h \
          two_pass_gaussian.h \
          convolution_filter.h \
          black_and_white.h \
          erosion.h

SOURCES = filters.cpp \
          filtering.cpp \
          two_pass_gaussian.cpp \
          convolution_filter.cpp \
          black_and_white.cpp \
          erosion.cpp

TBL_SOURCES  = filters.tbl

OTHER_FILES = filters.xl filters.tbl traces.tbl
QT          += core \
               gui \
               opengl

INSTALLS    += thismod_icon

QMAKE_SUBSTITUTES = doc/Doxyfile.in
DOXYFILE = doc/Doxyfile
DOXYLANG = en,fr
include(../modules_doc.pri)
