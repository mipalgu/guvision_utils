#
# Makefile
# Callum McColl, 2019-06-05 11:58
#

ALL_TARGETS=test robot-local

#C_SRCS!=ls *.c
CC_SRCS!=ls *.cc
ALL_HDRS!=ls *.h
SPECIFIC_LIBS=-lguunits
LOCAL=_LOCAL

.include "../../mk/c++17.mk"

${MODULE_BASE}_HDRS=${ALL_HDRS}
PKGCONFIG_NAME=guvision_utils
PKGCONFIG_VERSION=1.0
PKGCONFIG_DESCRIPTION=Simple utilities for interfacing with guvision.

.include "../../mk/cxxstd.mk"
.include "../../mk/prefs.mk"

${MODULE_BASE}_HDRS=${ALL_HDRS}

.include "../../mk/testdir.mk"
.include "../../mk/mipal.mk"
# vim:ft=make
#
