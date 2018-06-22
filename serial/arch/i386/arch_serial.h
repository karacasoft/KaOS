#ifndef __ARCH_SERIAL_H__
#define __ARCH_SERIAL_H__ 1

#define SERIAL_COM1_BASE 0x3F8
#define SERIAL_COM2_BASE 0x2F8
#define SERIAL_COM3_BASE 0x3E8
#define SERIAL_COM4_BASE 0x2E8

#define SERIAL_DATA_OFFSET 0
#define SERIAL_INT_EN_OFFSET 1

#define SERIAL_BAUD_DIV_LO_OFFSET 0
#define SERIAL_BAUD_DIV_HI_OFFSET 1

#define SERIAL_INT_ID_FIFO_OFFSET 2
#define SERIAL_LINE_CTRL_OFFSET 3
#define SERIAL_MODEM_CTRL_OFFSET 4
#define SERIAL_LINE_STATUS_OFFSET 5
#define SERIAL_MODEM_STATUS_OFFSET 6
#define SERIAL_SCRATCH_OFFSET 7


void arch_serial_send_char(uint16_t port, char ch);
char arch_serial_receive_char(uint16_t port);

#endif
