#ifndef __IDE_H__
#define __IDE_H__ 1

#include <stdint.h>

// Status Codes
#define ATA_SR_BSY  0x80 // Drive Busy
#define ATA_SR_DRDY 0x40 // Drive Ready
#define ATA_SR_DF   0x20 // Drive Fault
#define ATA_SR_DSC  0x10 // Drive Seek Complete
#define ATA_SR_DRQ  0x08 // Data Request Ready
#define ATA_SR_CORR 0x04 // Corrected Data
#define ATA_SR_IDX  0x02 // Index
#define ATA_SR_ERR  0x01 // Error

// Error Codes
#define ATA_ER_BBK   0x80 // Bad sector
#define ATA_ER_UNC   0x40 // Uncorrectable Data
#define ATA_ER_MC    0x20 // No Media
#define ATA_ER_IDNF  0x10 // ID Mark Not Found
#define ATA_ER_MCR   0x08 // NO Media
#define ATA_ER_ABRT  0x04 // Command Aborted
#define ATA_ER_TK0NF 0x02 // Track 0 Not Found
#define ATA_ER_AMNF  0x01 // No address mark

// ATA Commands 
#define ATA_CMD_READ_PIO        0x20
#define ATA_CMD_READ_PIO_EXT    0x24
#define ATA_CMD_READ_DMA        0xC8
#define ATA_CMD_READ_DMA_EXT    0x25
#define ATA_CMD_WRITE_PIO       0x30
#define ATA_CMD_WRITE_PIO_EXT   0x34
#define ATA_CMD_WRITE_DMA       0xCA
#define ATA_CMD_WRITE_DMA_EXT   0x35
#define ATA_CMD_CACHE_FLUSH     0xE7
#define ATA_CMD_CACHE_FLUSH_EXT 0xEA
#define ATA_CMD_PACKET          0xA0
#define ATA_CMD_IDENTIFY_PACKET 0xA1
#define ATA_CMD_IDENTIFY        0xEC

// ATAPI Commands
#define ATAPI_CMD_READ  0xA8
#define ATAPI_CMD_EJECT 0x1B


#define ATA_IDENT_DEVICETYPE   0
#define ATA_IDENT_CYLINDERS    2
#define ATA_IDENT_HEADS        6
#define ATA_IDENT_SECTORS      12
#define ATA_IDENT_SERIAL       20
#define ATA_IDENT_MODEL        54
#define ATA_IDENT_CAPABILITIES 98
#define ATA_IDENT_FIELDVALID   106
#define ATA_IDENT_MAX_LBA      120
#define ATA_IDENT_COMMANDSETS  164
#define ATA_IDENT_MAX_LBA_EXT  200

#define ATAPI_IDENT_BYTE_COUNT 250


#define IDE_ATA            0x00
#define IDE_ATAPI          0x01
#define IDE_PATA           0x02
#define IDE_SATA           0x03
#define IDE_UNKNOWN_TYPE   0x04

#define ATA_MASTER   0x00
#define ATA_SLAVE    0x01

// Registers
#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
#define ATA_REG_CONTROL    0x0C
#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

// Channels:
#define ATA_PRIMARY   0x00
#define ATA_SECONDARY 0x01

// Directions:
#define ATA_READ  0x00
#define ATA_WRITE 0x01

typedef void (*ide_int_handler_t)(void);

struct IDEChannelRegisters {
  uint16_t base;  // I/O Base
  uint16_t ctrl;  // Control Base
  uint16_t bmide; // Bus Master IDE
  uint16_t nIEN;  // No interrupt
} channels[2];

extern uint8_t ide_buf[2048];
static uint8_t ide_irq_invoked = 0;
static uint8_t atapi_packet[12] = 
  {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


struct ide_device {
  uint8_t reserved;
  uint8_t channel;
  uint8_t drive;
  uint16_t type;
  uint16_t signature;
  uint16_t capabilities;
  uint32_t command_sets;
  uint32_t size;
  char model[41];
} ide_devices[4];

extern void ide_initialize(uint32_t BAR0, uint32_t BAR1, uint32_t BAR2, uint32_t BAR3, uint32_t BAR4);

extern uint8_t ide_read(uint8_t channel, uint8_t reg);

extern void ide_write(uint8_t channel, uint8_t reg, uint8_t data);

extern uint8_t ide_polling(uint8_t channel, uint32_t advanced_check);

extern void ide_read_buffer(uint8_t channel, uint8_t reg, uint32_t buffer, uint32_t quads);

extern uint8_t ide_print_error(uint32_t drive, uint8_t error);

extern void ide_atapi_read_sector(uint8_t drive, uint32_t lba, uint8_t numsects, uint32_t edi);

extern void wait_for_interrupt();

#endif