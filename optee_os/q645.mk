CROSS_COMPILE = ../../crossgcc/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
AARCH32_CROSS_COMPILE = ../../crossgcc/gcc-arm-9.2-2019.12-x86_64-arm-none-eabi/bin/arm-none-eabi-
OPTEE_HEADER_BIN	:= tee-header_v2.sp
OPTEE_PAGER_BIN		:= tee-pager_v2.sp
OPTEE_PAGEABLE_BIN  := tee-pageable_v2.sp

BINARIES_PATH		?= ./out/bin

define install_in_binaries
	echo "  INSTALL $(shell basename $1) to $(BINARIES_PATH)" && \
	mkdir -p $(BINARIES_PATH) && \
	ln -sf $1 $(BINARIES_PATH)
endef

OPTEE_OS_COMMON_FLAGS ?= \
	O=out/arm \
	CFG_ARM64_core=y \
	PLATFORM=sp \
	PLATFORM_FLAVOR=Q645 \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	CROSS_COMPILE_core=$(CROSS_COMPILE) \
	CROSS_COMPILE_ta_arm64="$(CROSS_COMPILE)" \
	CROSS_COMPILE_ta_arm32="$(AARCH32_CROSS_COMPILE)" \
	CFG_TEE_CORE_LOG_LEVEL=2 \
	DEBUG=0 \
	CFG_TEE_BENCHMARK=n

.PHONY: optee-os-common
optee-os-common:
	$(MAKE)  $(OPTEE_OS_COMMON_FLAGS)

all: optee-os-common
	@$(call install_in_binaries,./out/arm/core/$(OPTEE_HEADER_BIN))
	@$(call install_in_binaries,./out/arm/core/$(OPTEE_PAGER_BIN))
	@$(call install_in_binaries,./out/arm/core/$(OPTEE_PAGEABLE_BIN))    
