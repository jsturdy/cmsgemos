#
# Global Makefile for GEM
#

SUBPACKAGES := \
        gemutils \
        gembase \
        gemhardware/devices \
        gemhardware/managers \
        gemreadout \
        gemsupervisor \
        gempython \
        gemdaqmonitor \
        gemonlinedb \
        # gemHwMonitor \

# SUBPACKAGES.DOC      := $(patsubst %,%.doc,    ${SUBPACKAGES})
# SUBPACKAGES.CHECK    := $(patsubst %,%.check,    ${SUBPACKAGES})
SUBPACKAGES.DEBUG    := $(patsubst %,%.debug,    ${SUBPACKAGES})
SUBPACKAGES.INSTALL  := $(patsubst %,%.install,  ${SUBPACKAGES})
SUBPACKAGES.RPM      := $(patsubst %,%.rpm,      ${SUBPACKAGES})
SUBPACKAGES.CLEANRPM := $(patsubst %,%.cleanrpm, ${SUBPACKAGES})
SUBPACKAGES.CLEAN    := $(patsubst %,%.clean,    ${SUBPACKAGES})
SUBPACKAGES.TESTS    := $(patsubst %,%.tests,    ${SUBPACKAGES})
SUBPACKAGES.RUNTESTS := $(patsubst %,%.run-tests, ${SUBPACKAGES})
SUBPACKAGES.RUNTESTSCI := $(patsubst %,%.run-tests-ci, ${SUBPACKAGES})

#OS:=linux
#ARCH:=x86_64
#LIBDIR:=lib/$(OS)/$(ARCH)

default: all

all: $(SUBPACKAGES)

release: all doc

gcc47: UserCFlags+=${GCC47Flags}
gcc47: UserCCFlags+=${GCC47Flags}
gcc47: $(SUBPACKAGES)

gcc48: UserCFlags+=${GCC47Flags}
gcc48: UserCFlags+=${GCC48Flags}
gcc48: UserCCFlags+=${GCC47Flags}
gcc48: UserCCFlags+=${GCC48Flags}
gcc48: $(SUBPACKAGES)

gcc49: UserCFlags+=${GCC47Flags}
gcc49: UserCFlags+=${GCC48Flags}
gcc49: UserCFlags+=${GCC49Flags}
gcc49: UserCCFlags+=${GCC47Flags}
gcc49: UserCCFlags+=${GCC48Flags}
gcc49: UserCCFlags+=${GCC49Flags}
gcc49: $(SUBPACKAGES)

debug: UserCFlags+=${DEBUG_CFlags}
debug: UserCCFlags+=${DEBUG_CCFlags}
debug: $(SUBPACKAGES)

profile: UserCFlags+=${PROFILING_Flags}
profile: UserCCFlags+=${PROFILING_Flags}
profile: UserDynamicLinkFlags+=${PROFILING_LDFlags}
profile: DependentLibraries+=${PROFILING_LIBS}
profile: $(SUBPACKAGES)

dbgprofile: UserCFlags+=${DEBUG_CFlags} ${PROFILING_Flags}
dbgprofile: UserCCFlags+=${DEBUG_CCFlags} ${PROFILING_Flags}
dbgprofile: UserDynamicLinkFlags+=${PROFILING_LDFlags}
dbgprofile: DependentLibraries+=${PROFILING_LIBS}
dbgprofile: $(SUBPACKAGES)

doc:  $(SUBPACKAGES)
	@echo "Generating doxygen"
	@mkdir ./doc/build
	@rm -fr ./doc/build/* 2> /dev/null
	@doxygen -s ./doc/cmsgemos.cfg
#	@git checkout gh-pages  > /dev/null 2>&1
#	@git add -f ./doc/html  > /dev/null 2>&1
#	@git commit -m "generating doxygen" ./doc/html  > /dev/null 2>&1
#	@git tag ./doc/html  > /dev/null 2>&1

install: $(LIBDIR) $(SUBPACKAGES) $(SUBPACKAGES.INSTALL)

rpm: $(SUBPACKAGES) $(SUBPACKAGES.RPM)

cleanrpm: $(SUBPACKAGES.CLEANRPM)

clean: $(SUBPACKAGES.CLEAN)

tests: $(SUBPACKAGES) $(SUBPACKAGES.TESTS)

run-tests: $(SUBPACKAGES.RUNTESTS)

run-tests-ci: $(SUBPACKAGES.RUNTESTSCI)

debug: $(SUBPACKAGES.DEBUG)

# check: $(SUBPACKAGES.CHECK)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(SUBPACKAGES):
	$(MAKE) -C $@

$(SUBPACKAGES.RPM):
	$(MAKE) -C $(patsubst %.rpm,%, $@) rpm

$(SUBPACKAGES.CLEANRPM):
	$(MAKE) -C $(patsubst %.cleanrpm,%, $@) cleanrpm

# $(SUBPACKAGES.CHECK):
# 	$(MAKE) -C $(patsubst %.check,%, $@) check

# $(SUBPACKAGES.DEBUG):
# 	$(MAKE) -C $(patsubst %.debug,%, $@) debug

$(SUBPACKAGES.INSTALL):
	-find  $(patsubst %.install,%, $@)/lib -name *.so -print -exec cp {} ${LIBDIR} \;

$(SUBPACKAGES.CLEAN):
	$(MAKE) -C $(patsubst %.clean,%, $@) clean

$(SUBPACKAGES.TESTS): all
	$(MAKE) -C $(patsubst %.tests,%, $@) tests

$(SUBPACKAGES.RUNTESTS): tests
	$(MAKE) -C $(patsubst %.run-tests,%, $@) run-tests

$(SUBPACKAGES.RUNTESTSCI): tests
	$(MAKE) -C $(patsubst %.run-tests-ci,%, $@) run-tests-ci

.PHONY: $(SUBPACKAGES) $(SUBPACKAGES.INSTALL) $(SUBPACKAGES.CLEAN) $(SUBPACKAGES.CHECK) $(SUBPACKAGES.DEBUG)

#$(SUBPACKAGES.CHECK) $(SUBPACKAGES.DEBUG)

gemhardware/devices: gemutils

gemhardware/managers: gemutils gembase gemreadout gemhardware/devices

gemHwMonitor: gemutils gembase gemhardware/devices

## only gemhardware.devices... how to fix this?
gempython: gemhardware/devices

gembase: gemutils

gemsupervisor: gemutils gembase gemhardware gemreadout

gemutils:

gemonlinedb: gemutils gembase

gemreadout: gemutils gembase gemhardware/devices

gemdaqmonitor: gembase gemhardware/devices

print-env:
	@echo BUILD_HOME    $(BUILD_HOME)
	@echo XDAQ_ROOT     $(XDAQ_ROOT)
	@echo XDAQ_OS       $(XDAQ_OS)
	@echo XDAQ_PLATFORM $(XDAQ_PLATFORM)
	@echo LIBDIR        $(LIBDIR)
	@echo ROOTCFLAGS    $(ROOTCFLAGS)
	@echo ROOTLIBS      $(ROOTLIBS)
	@echo ROOTGLIBS     $(ROOTGLIBS)
	@echo GIT_VERSION   $(GIT_VERSION)
	@echo GEMDEVLOPER   $(GEMDEVLOPER)
	@echo CC            $(CC)
	@echo CPP           $(CPP)
	@echo CXX           $(CXX)
	@echo LD            $(LD)
	@echo AR            $(AR)
	@echo NM            $(NM)
	@echo RANLIB        $(RANLIB)
	@echo GCCVERSION    $(GCCVERSION)
	@echo CLANGVERSION  $(CLANGVERSION)
	@echo DependentLibraryDirs  $(DependentLibraryDirs)
#
# Makefile for gemhardware package
#

Project=cmsgemos
ShortProject=gem
Package=gemhardware
LongPackage=gemhardware
ShortPackage=hw
PackageName=hw

GEMHARDWARE_VER_MAJOR=1
GEMHARDWARE_VER_MINOR=0
GEMHARDWARE_VER_PATCH=1

include $(BUILD_HOME)/$(Project)/config/mfDefsGEM.mk
include $(BUILD_HOME)/$(Project)/config/mfPythonDefsGEM.mk

include $(XDAQ_ROOT)/config/Makefile.rules
include $(BUILD_HOME)/$(Project)/config/mfRPMDefsGEM.mk

.PHONY: devices managers _hackery

_hackery:
	if [[ -L Makefile ]]; \
	then \
	unlink Makefile; \
	cp Makefile.progress Makefile; \
	fi

devices:
	$(MAKE) _hackery
	cp Makefile Makefile.progress
	ln -sf Makefile.devices Makefile
	$(MAKE); ret=$$?; \
	$(MAKE) -f Makefile.progress _hackery; \
	exit $$ret

managers: devices
	$(MAKE) _hackery
	cp Makefile Makefile.progress
	ln -sf Makefile.managers Makefile; \
	$(MAKE); ret=$$?; \
	$(MAKE) -f Makefile.progress _hackery; \
	exit $$ret

_all: devices managers

print-env:
	@echo BUILD_HOME    $(BUILD_HOME)
	@echo XDAQ_ROOT     $(XDAQ_ROOT)
	@echo XDAQ_OS       $(XDAQ_OS)
	@echo XDAQ_PLATFORM $(XDAQ_PLATFORM)
	@echo LIBDIR        $(LIBDIR)
	@echo ROOTCFLAGS    $(ROOTCFLAGS)
	@echo ROOTLIBS      $(ROOTLIBS)
	@echo ROOTGLIBS     $(ROOTGLIBS)
	@echo GIT_VERSION   $(GIT_VERSION)
	@echo GEMDEVELOPER  $(GEMDEVELOPER)
	@echo CC            $(CC)
	@echo CPP           $(CPP)
	@echo CXX           $(CXX)
	@echo LD            $(LD)
	@echo AR            $(AR)
	@echo NM            $(NM)
	@echo RANLIB        $(RANLIB)
	@echo UserCFlags    $(UserCFlags)
	@echo CCVERSION     $(CCVERSION)
	@echo CLANGNUM      $(CLANGNUM)
	@echo GCCNUM        $(GCCNUM)
