# ******************************************************************************
#  filters.pro                                                  Tao project
# ******************************************************************************
# File Description:
# Qt build file for the Filters module
# ******************************************************************************
# This software is property of Taodyne SAS - Confidential
# Ce logiciel est la propriété de Taodyne SAS - Confidentiel
# (C) 2010 Jerome Forissier <jerome@taodyne.com>
# (C) 2010 Taodyne SAS
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
