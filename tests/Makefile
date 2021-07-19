HDRS!=ls *.h 2>/dev/null || :
C_SRCS!=ls *.c 2>/dev/null || :
CC_SRCS!=ls *.cc 2>/dev/null || :
CPP_SRCS!=ls *.cpp 2>/dev/null || :
CXXFLAGS+=-I../../../../../Common -I../../../../gusimplewhiteboard
SPECIFIC_LIBS+=-lguunits

.include "../../../mk/gtest.mk"
.include "../../../mk/mipal.mk"
