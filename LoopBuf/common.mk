ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

# c file
EXTRA_SRCVPATH=$(PROJECT_ROOT)/src/
# head file
EXTRA_INCVPATH  =$(PROJECT_ROOT)/inc/
EXTRA_INCVPATH +=$(PROJECT_ROOT)/../com/
EXTRA_INCVPATH +=$(PROJECT_ROOT)/../cShmLib/inc
EXTRA_INCVPATH +=$(PROJECT_ROOT)/../../src/lib/hw_vendor/nxp/imx8/sci/aarch64/
EXTRA_INCVPATH +=$(PROJECT_ROOT)/../../src/hardware/support/sc-imx8/public/
EXTRA_INCVPATH +=$(PROJECT_ROOT)/../../src/lib/hw_vendor/nxp/imx8/sci/public/
EXTRA_INCVPATH +=$(PROJECT_ROOT)/../src/lib/hw_vendor/nxp/imx8/sci/public/
EXTRA_INCVPATH +=$(PROJECT_ROOT)/../src/hardware/support/sc-imx8/public/

CCFLAGS=-O0 -g

NAME=cShm
USEFILE=$(PROJECT_ROOT)/cShm.use

include $(MKFILES_ROOT)/qtargets.mk
