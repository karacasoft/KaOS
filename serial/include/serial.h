#ifndef __SERIAL_H__
#define __SERIAL_H__ 1

#include <stdint.h>

typedef struct __serial_port {
    uint16_t base_address;
} serial_port_t;

void serial_send_char(serial_port_t *port, char ch);
char serial_receive_char(serial_port_t *port);

#endif