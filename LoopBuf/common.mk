ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

# c file
EXTRA_SRCVPATH=$(PROJECT_ROOT)/src/
# head file
EXTRA_INCVPATH  = $(PROJECT_ROOT)/inc/
EXTRA_INCVPATH += $(PROJECT_ROOT)/../com/

CCFLAGS=-O0 -g

NAME=libcShm
USEFILE=$(PROJECT_ROOT)/cShm.use

include $(MKFILES_ROOT)/qtargets.mk
