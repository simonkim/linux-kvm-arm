#
# This file is subject to the terms and conditions of the GNU General Public
# License.  See the file "COPYING" in the main directory of this archive
# for more details.
#
# Copyright (C) 2001 - 2005  Tensilica Inc.
#
# This file is included by the global makefile so that you can add your own
# architecture-specific flags and dependencies. Remember to do have actions
# for "archclean" and "archdep" for cleaning up and making dependencies for
# this architecture

# Core configuration.
# (Use VAR=<xtensa_config> to use another default compiler.)

variant-$(CONFIG_XTENSA_VARIANT_FSF)		:= fsf
variant-$(CONFIG_XTENSA_VARIANT_DC232B)		:= dc232b
variant-$(CONFIG_XTENSA_VARIANT_S6000)		:= s6000
variant-$(CONFIG_XTENSA_VARIANT_LINUX_CUSTOM)	:= custom

VARIANT = $(variant-y)
export VARIANT

# Test for cross compiling

ifneq ($(VARIANT),)
  COMPILE_ARCH = $(shell uname -m)

  ifneq ($(COMPILE_ARCH), xtensa)
    ifndef CROSS_COMPILE
      CROSS_COMPILE = xtensa_$(VARIANT)-
    endif
  endif
endif

# Platform configuration

platform-$(CONFIG_XTENSA_PLATFORM_XT2000)	:= xt2000
platform-$(CONFIG_XTENSA_PLATFORM_ISS)		:= iss
platform-$(CONFIG_XTENSA_PLATFORM_S6105)	:= s6105
platform-$(CONFIG_XTENSA_PLATFORM_XTFPGA)	:= xtfpga

PLATFORM = $(platform-y)
export PLATFORM

# temporarily until string.h is fixed
KBUILD_CFLAGS += -ffreestanding -D__linux__

KBUILD_CFLAGS += -pipe -mlongcalls

KBUILD_CFLAGS += $(call cc-option,-mforce-no-pic,)

ifneq ($(CONFIG_LD_NO_RELAX),)
LDFLAGS := --no-relax
endif

ifeq ($(shell echo -e __XTENSA_EB__ | $(CC) -E - | grep -v "\#"),1)
CHECKFLAGS += -D__XTENSA_EB__
endif
ifeq ($(shell echo -e __XTENSA_EL__ | $(CC) -E - | grep -v "\#"),1)
CHECKFLAGS += -D__XTENSA_EL__
endif

vardirs := $(patsubst %,arch/xtensa/variants/%/,$(variant-y))
plfdirs := $(patsubst %,arch/xtensa/platforms/%/,$(platform-y))

ifeq ($(KBUILD_SRC),)
KBUILD_CPPFLAGS += $(patsubst %,-I%include,$(vardirs) $(plfdirs))
else
KBUILD_CPPFLAGS += $(patsubst %,-I$(srctree)/%include,$(vardirs) $(plfdirs))
endif

KBUILD_DEFCONFIG := iss_defconfig

# Only build variant and/or platform if it includes a Makefile

buildvar := $(shell test -e $(srctree)/arch/xtensa/variants/$(VARIANT)/Makefile && echo arch/xtensa/variants/$(VARIANT)/)
buildplf := $(shell test -e $(srctree)/arch/xtensa/platforms/$(PLATFORM)/Makefile && echo arch/xtensa/platforms/$(PLATFORM)/)

# Find libgcc.a

LIBGCC := $(shell $(CC) $(KBUILD_CFLAGS) -print-libgcc-file-name)

head-y		:= arch/xtensa/kernel/head.o
core-y		+= arch/xtensa/kernel/ arch/xtensa/mm/
core-y		+= $(buildvar) $(buildplf)

libs-y		+= arch/xtensa/lib/ $(LIBGCC)

ifneq ($(CONFIG_BUILTIN_DTB),"")
core-$(CONFIG_OF) += arch/xtensa/boot/
endif

boot		:= arch/xtensa/boot

all: zImage

bzImage : zImage

zImage: vmlinux
	$(Q)$(MAKE) $(build)=$(boot) $@

%.dtb:
	$(Q)$(MAKE) $(build)=$(boot) $(boot)/$@

define archhelp
  @echo '* zImage      - Compressed kernel image (arch/xtensa/boot/images/zImage.*)'
endef
