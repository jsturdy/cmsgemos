#
# Makefile for gemhardware package
#

BUILD_HOME := $(shell dirname `cd ../../; pwd`)

Project=cmsgemos
ShortProject=gem
Package=gemhardware/devices
LongPackage=gemhardware/devices
ShortPackage=hw/devices
PackageName=hwdevices

ProjectBase = $(BUILD_HOME)/$(Project)
CfgDir      = $(ProjectBase)/config

include $(CfgDir)/mfDefsGEM.mk
include $(CfgDir)/mfPythonDefsGEM.mk

Sources =version.cc
# Sources =utils/GEMCrateUtils.cc
Sources+=GEMHwDevice.cc
Sources+=amc/HwGenericAMC.cc
# Sources+=vfat/HwVFAT2.cc
# Sources+=glib/HwGLIB.cc
# Sources+=ctp7/HwCTP7.cc
# Sources+=optohybrid/HwOptoHybrid.cc

DynamicLibrary=gemhwdevices

IncludeDirs =$(XDAQ_ROOT)/include
IncludeDirs+=$(BUILD_HOME)/$(Project)/$(Package)/include
IncludeDirs+=$(BUILD_HOME)/$(Project)/gemhardware/utils/include
IncludeDirs+=$(BUILD_HOME)/$(Project)/gemutils/include
IncludeDirs+=$(uHALROOT)/include
IncludeDirs+=$(XHAL_ROOT)/include

DependentLibraryDirs+=$(BUILD_HOME)/$(Project)/gemhardware/utils/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM)
DependentLibraryDirs+=$(BUILD_HOME)/$(Project)/gemutils/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM)
DependentLibraryDirs+=$(uHALROOT)/lib
DependentLibraryDirs+=$(XHAL_ROOT)/lib

LibraryDirs+=$(BUILD_HOME)/$(Project)/gemhardware/utils/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM)
LibraryDirs+=$(BUILD_HOME)/$(Project)/gemutils/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM)
LibraryDirs+=$(uHALROOT)/lib
LibraryDirs+=$(XHAL_ROOT)/lib

DependentLibraries =cactus_uhal_uhal xhal
DependentLibraries+=gemutils

UserCFlags+=-O0 -g3 -fno-inline
UserCCFlags+=-O0 -g3 -fno-inline
CFlags+=-O0 -g3 -fno-inline
CCFlags+=-O0 -g3 -fno-inline

include $(XDAQ_ROOT)/config/Makefile.rules
include $(BUILD_HOME)/$(Project)/config/mfRPMDefsGEM.mk

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
	@echo GCCVERSION    $(GCCVERSION)
	@echo CLANGVERSION  $(CLANGVERSION)
