#
# Makefile
# Callum McColl, 2019-06-05 11:58
#

ALL_TARGETS?=test robot-local

SUPPORTED_CPP_STDS=17 20

DEPENDS=gu_util

CC_SRCS!=ls *.cc
CPP_SRCS=math_fnc.cpp
ALL_HDRS!=ls *.h
DOC_HDRS=${ALL_HDRS}
SPECIFIC_LIBS=-lguunits

PKGCONFIG_NAME=guvision_utils
PKGCONFIG_VERSION=1.0
PKGCONFIG_DESCRIPTION=Simple utilities for interfacing with guvision.

.include "../../mk/c++17.mk"
.include "../../mk/cxxstd.mk"
.include "../../mk/prefs.mk"

${MODULE_BASE}_HDRS=${ALL_HDRS}

.include "../../mk/testdir.mk"
.include "../../mk/mipal.mk"
# vim:ft=make
#
