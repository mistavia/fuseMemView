#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/events.o \
	${OBJECTDIR}/fileSystem.o \
	${OBJECTDIR}/fuseMemView.o \
	${OBJECTDIR}/machine.o \
	${OBJECTDIR}/memory.o \
	${OBJECTDIR}/network.o \
	${OBJECTDIR}/socket.o \
	${OBJECTDIR}/socketFuse.o \
	${OBJECTDIR}/window.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs glib-2.0` `pkg-config --libs ncurses` `pkg-config --libs gio-2.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk fusememview

fusememview: ${OBJECTFILES}
	${LINK.c} -o fusememview ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/events.o: events.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/events.o events.c

${OBJECTDIR}/fileSystem.o: fileSystem.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fileSystem.o fileSystem.c

${OBJECTDIR}/fuseMemView.o: fuseMemView.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fuseMemView.o fuseMemView.c

${OBJECTDIR}/machine.o: machine.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/machine.o machine.c

${OBJECTDIR}/memory.o: memory.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/memory.o memory.c

${OBJECTDIR}/network.o: network.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/network.o network.c

${OBJECTDIR}/socket.o: socket.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socket.o socket.c

${OBJECTDIR}/socketFuse.o: socketFuse.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/socketFuse.o socketFuse.c

${OBJECTDIR}/window.o: window.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -I/usr/include -I/usr/share/glib-2.0 -include /usr/include/ncurses.h -include /usr/include/netdb.h `pkg-config --cflags glib-2.0` `pkg-config --cflags ncurses` `pkg-config --cflags gio-2.0` -std=c99  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/window.o window.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} fusememview

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
