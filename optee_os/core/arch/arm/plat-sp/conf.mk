
include core/arch/arm/cpu/cortex-armv8-0.mk
CFG_ARM64_core ?= y

$(call force,CFG_SP_UART,y)   
$(call force,CFG_GIC,y)		 
$(call force,CFG_WITH_ARM_TRUSTED_FW,y) 

$(call force,CFG_TEE_CORE_NB_CORE,4)   
$(call force,CFG_WITH_LPAE,y)

$(call force,CFG_SECURE_TIME_SOURCE_CNTPCT,y)  

CFG_SHMEM_START ?= 0x0F300000     
CFG_SHMEM_SIZE  ?= 0x00400000

CFG_TZDRAM_START ?= 0x300000			/*  the same as BL32_BASE  in tf-a*/
CFG_TZDRAM_SIZE  ?= 0x00200000

CFG_TEE_RAM_VA_SIZE ?= 0x00100000

CFG_WITH_STATS ?= y

