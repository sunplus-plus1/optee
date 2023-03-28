#include <drivers/sp_uart.h>
#include <io.h>
#include <keep.h>
#include <util.h>

#define SP_UART_DR           (0x0)
#define SP_UART_LSR          (0x4)

#define UART_LSR_TX_RDY     (1 << 0)
#define UART_LSR_RX_RDY     (1 << 1)
#define UART_TX_EMPTY       (1 << 6)


static vaddr_t chip_to_base(struct serial_chip *chip)
{
	struct sp_uart_data *pd = container_of(chip, struct sp_uart_data, chip);

	return io_pa_or_va(&pd->base);
}

static void sp_uart_flush(struct serial_chip *chip)
{
	vaddr_t base = chip_to_base(chip);

	while (!(io_read32(base + SP_UART_LSR) & UART_TX_EMPTY))
		;
}

static bool sp_uart_have_rx_data(struct serial_chip *chip)
{
	vaddr_t base = chip_to_base(chip);

	return (io_read32(base + SP_UART_LSR) & UART_LSR_RX_RDY);
}

static void sp_uart_putc(struct serial_chip *chip, int ch)
{
	vaddr_t base = chip_to_base(chip);

	while (!(io_read32(base + SP_UART_LSR) & UART_LSR_TX_RDY))
		;
	io_write32(base + SP_UART_DR, ch);
}

static int sp_uart_getchar(struct serial_chip *chip)
{
	vaddr_t base = chip_to_base(chip);

	while (!sp_uart_have_rx_data(chip))
		;

	return io_read32(base + SP_UART_DR) & 0xff;
}

static const struct serial_ops sp_uart_ops = {
	.flush = sp_uart_flush,
	.getchar = sp_uart_getchar,
	.have_rx_data = sp_uart_have_rx_data,
	.putc = sp_uart_putc,
};
DECLARE_KEEP_PAGER(sp_uart_ops);

void sp_uart_init(struct sp_uart_data *pd, paddr_t base)
{
	pd->base.pa = base;
    pd->base.va = 0;
	pd->chip.ops = &sp_uart_ops;
}
