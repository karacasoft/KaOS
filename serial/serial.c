#include <serial.h>

extern void arch_serial_send_char(uint16_t port, char ch);
extern char arch_serial_receive_char(uint16_t port);

void serial_send_char(serial_port_t *port, char ch) {
    arch_serial_send_char(port->base_address, ch);
}

char serial_receive_char(serial_port_t *port) {
    return arch_serial_receive_char(port->base_address);
}
