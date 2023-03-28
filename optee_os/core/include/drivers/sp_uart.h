#ifndef SP_UART_H
#define SP_UART_H

#include <types_ext.h>
#include <drivers/serial.h>

struct sp_uart_data {
	struct io_pa_va base;
	struct serial_chip chip;
};

void sp_uart_init(struct sp_uart_data *pd, paddr_t pbase);

#endif /* SP_UART_H */