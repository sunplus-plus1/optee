#include <platform_config.h>

#include <console.h>
#include <drivers/gic.h>
#include <drivers/sp_uart.h>
#include <kernel/boot.h>
#include <kernel/interrupt.h>
#include <kernel/panic.h>
#include <mm/core_memprot.h>
#include <mm/tee_pager.h>
#include <platform_config.h>
#include <stdint.h>

static struct gic_data gic_data;
static struct sp_uart_data console_data;

register_phys_mem_pgdir(MEM_AREA_IO_SEC, SP_GICC_BASE, SP_GICC_SIZE);
register_phys_mem_pgdir(MEM_AREA_IO_SEC, SP_GICD_BASE, SP_GICD_SIZE);
register_phys_mem_pgdir(MEM_AREA_IO_NSEC, CONSOLE_SP_UART_BASE,SP_UART_REG_SIZE);

register_phys_mem_pgdir(MEM_AREA_IO_SEC, SP_SPI_FLASH_BASE,SP_SPI_FLASH_SIZE);


void main_init_gic(void)
{
	vaddr_t gicc_base;
	vaddr_t gicd_base;

	gicc_base = (vaddr_t)phys_to_virt(SP_GICC_BASE, MEM_AREA_IO_SEC);
	gicd_base = (vaddr_t)phys_to_virt(SP_GICD_BASE, MEM_AREA_IO_SEC);

	if (!gicc_base || !gicd_base)
		panic();

	gic_init_base_addr(&gic_data, gicc_base, gicd_base);
	itr_init(&gic_data.chip);
}

void main_secondary_init_gic(void)
{
	gic_cpu_init(&gic_data);
}

void itr_core_handler(void)
{
	gic_it_handle(&gic_data);
}

void console_init(void)
{
	sp_uart_init(&console_data, CONSOLE_SP_UART_BASE);
	register_serial_console(&console_data.chip);
}
