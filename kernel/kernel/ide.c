#include <stdint.h>

#include <stdio.h>

#include <kernel/ide.h>
#include <kernel/iobase.h>

uint8_t ide_buf[2048] = {0};

void ide_initialize(uint32_t BAR0, uint32_t BAR1, uint32_t BAR2, uint32_t BAR3, uint32_t BAR4) {
  
  int i, j, k, count = 0;
  
  // set I/O ports
  channels[ATA_PRIMARY].base    = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
  channels[ATA_PRIMARY].ctrl    = (BAR1 & 0xFFFFFFFC) + 0x3F6 * (!BAR1);
  channels[ATA_SECONDARY].base  = (BAR2 & 0xFFFFFFFC) + 0x170 * (!BAR2);
  channels[ATA_SECONDARY].ctrl  = (BAR3 & 0xFFFFFFFC) + 0x376 * (!BAR3);
  channels[ATA_PRIMARY].bmide   = (BAR4 & 0xFFFFFFFC) + 0;
  channels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8;
  
  // Disable IRQ's
  ide_write(ATA_PRIMARY, ATA_REG_CONTROL, 2);
  ide_write(ATA_SECONDARY, ATA_REG_CONTROL, 2);
  
  for(i = 0; i < 2; i++) {
    for(j = 0; j < 2; j++) {
      uint8_t err = 0, type = IDE_ATA, status;
      ide_devices[count].reserved = 0;
      
      ide_write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4));
      // Currently relying on the virtual machine to instantly
      // handle hardware stuff for us. On a real machine we have to
      // wait 1 ms here.
      // sleep(1);
      
      ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
      // sleep(1);
      
      // No device if status = 0
      if(ide_read(i, ATA_REG_COMMAND) == 0) continue;
      
      while(1) {
        status = ide_read(i, ATA_REG_STATUS);
        if((status & ATA_SR_ERR)) {err = 1; break;}
        if((status & ATA_SR_BSY) && (status & ATA_SR_DRQ)) { break;}
      }
      
      if(err != 0) {
        uint8_t cl = ide_read(i, ATA_REG_LBA1);
        uint8_t ch = ide_read(i, ATA_REG_LBA2);
        
        if(cl == 0x14 && ch == 0xEB)
          type = IDE_ATAPI;
        else if(cl == 0x69 && ch == 0x96)
          type = IDE_ATAPI;
        else
          continue; // Unknown type
          
        ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
        //sleep(1);
      }
      
      ide_read_buffer(i, ATA_REG_DATA, (uint32_t) ide_buf, 128);
      
      ide_devices[count].reserved = 1;
      ide_devices[count].type = type;
      ide_devices[count].channel = i;
      ide_devices[count].drive = j;
      ide_devices[count].signature = *((uint16_t *) (ide_buf + ATA_IDENT_DEVICETYPE));
      ide_devices[count].capabilities = *((uint16_t *) (ide_buf + ATA_IDENT_CAPABILITIES));
      ide_devices[count].command_sets = *((uint32_t *) (ide_buf + ATA_IDENT_COMMANDSETS));
      
      if(ide_devices[count].command_sets & (1 << 26)) {
        ide_devices[count].size = *((uint32_t *) (ide_buf + ATA_IDENT_MAX_LBA_EXT));
      } else {
        ide_devices[count].size = *((uint32_t *) (ide_buf + ATA_IDENT_MAX_LBA));
      }
      
      for (k = 0; k < 40; k+=2) {
        ide_devices[count].model[k] = ide_buf[ATA_IDENT_MODEL + k + 1];
        ide_devices[count].model[k + 1] = ide_buf[ATA_IDENT_MODEL + k];
      }
      ide_devices[count].model[40] = 0;
      
      count ++;
    }
  }
  
  for (i = 0; i < 4; i++) {
    if(ide_devices[i].reserved == 1) {
      printf("Found %s Drive %dGB - %s\n",
        (const char *[]) {"ATA", "ATAPI"}[ide_devices[i].type],
        ide_devices[i].size / 1024 / 1024 / 2,
        ide_devices[i].model);
    }
  }
}

uint8_t ide_read(uint8_t channel, uint8_t reg) {
  uint8_t result;
  
  if(reg > 0x07 && reg < 0x0C)
    ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
  if(reg < 0x08)
    result = inb(channels[channel].base + reg - 0x00);
  else if(reg < 0x0C)
    result = inb(channels[channel].base + reg - 0x06);
  else if(reg < 0x0E)
    result = inb(channels[channel].ctrl + reg - 0x0A);
  else if(reg < 0x16)
    result = inb(channels[channel].bmide + reg - 0x0E);
  if(reg > 0x07 && reg < 0x0C)
    ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
  return result;
}

void ide_write(uint8_t channel, uint8_t reg, uint8_t data) {
  if(reg > 0x07 && reg < 0x0C)
    ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
  if(reg < 0x08)
    outb(channels[channel].base + reg - 0x00, data);
  else if(reg < 0x0C)
    outb(channels[channel].base + reg - 0x06, data);
  else if(reg < 0x0E)
    outb(channels[channel].ctrl + reg - 0x0A, data);
  else if(reg < 0x16)
    outb(channels[channel].bmide + reg - 0x0E, data);
  if(reg > 0x07 && reg < 0x0C)
    ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}

void ide_read_buffer(uint8_t channel, uint8_t reg, uint32_t buffer, uint32_t quads) {
  if(reg > 0x07 && reg < 0x0C)
    ide_write(channel, ATA_REG_CONTROL, 0x80 | channels[channel].nIEN);
  if(reg < 0x08)
    insl(channels[channel].base + reg - 0x00, (uint32_t *) buffer, quads);
  else if(reg < 0x0C)
    insl(channels[channel].base + reg - 0x06, (uint32_t *) buffer, quads);
  else if(reg < 0x0E)
    insl(channels[channel].ctrl + reg - 0x0A, (uint32_t *) buffer, quads);
  else if(reg < 0x16)
    insl(channels[channel].bmide + reg - 0x0E, (uint32_t *) buffer, quads);
  if(reg > 0x07 && reg < 0x0C)
    ide_write(channel, ATA_REG_CONTROL, channels[channel].nIEN);
}

uint8_t ide_print_error(uint32_t drive, uint8_t err) {
  if(err == 0)
    return err;
  
  printf("IDE: ");
  if(err == 1) {
    printf("- Device Fault\n    ");
    err = 19;
  }
  else if(err == 2) {
    uint8_t st = ide_read(ide_devices[drive].channel, ATA_REG_ERROR);
    if(st & ATA_ER_AMNF) { printf("- No Address Mark Found\n    "); err = 7; }
    if(st & ATA_ER_TK0NF) { printf("- No Media or Media Error\n    "); err = 3; }
    if(st & ATA_ER_ABRT) { printf("- Command Aborted\n    "); err = 20; }
    if(st & ATA_ER_MCR) { printf("- No Media or Media Error\n    "); err = 3; }
    if(st & ATA_ER_IDNF) { printf("- ID Mark Not Found\n    "); err = 21; }
    if(st & ATA_ER_MC) { printf("- No Media or Media Error\n    "); err = 3; }
    if(st & ATA_ER_UNC) { printf("- Uncorrectable Data Error\n    "); err = 22; }
    if(st & ATA_ER_BBK) { printf("- Bad Sectors\n    "); err = 13; }
  } 
  else if(err == 3) {
    printf("- Reads nothing\n    "); err = 23;
  }
  else if(err == 4) {
    printf("- Write protected\n    "); err = 8;
  }
  
  printf("- [%s %s] %s\n",
    (const char *[]) {"Primary", "Secondary"}[ide_devices[drive].channel],
    (const char *[]) {"Master", "Slave"}[ide_devices[drive].drive],
    ide_devices[drive].model);
  
  return err;
}

void wait_for_interrupt(ide_int_handler_t interrupt_handler) {
  // TODO
}

