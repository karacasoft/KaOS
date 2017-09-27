#include <stdint.h>

#include <kernel/timer.h>
#include <kernel/irq.h>
#include <stdio.h>

uint32_t timer_frequency = 1000; // hz
uint32_t countdown = 0;

void init_timer() {
  // Find freq divisor for 1000Hz
  int divisor = 1193182 / timer_frequency;
  
  // Set freq divisor
  outb(TIMER_MODE_PORT, 0x34);
  
  outb(TIMER_CHANNEL_0_PORT, (divisor & 0xFF)); // send low byte
  outb(TIMER_CHANNEL_0_PORT, (divisor >> 8) & 0xFF); // send high byte
  
  hook_irq_handler(0, _timer_irq);
  
}

void _timer_irq() {
  if(countdown > 0) countdown--;
}

void sleep(uint32_t ms) {
  countdown = ms;
  disable_interrupts();
  while(countdown > 0) {
    //printf("%d", countdown);
    enable_interrupts();
    asm volatile ("nop\nnop\nnop\nnop\nnop\nnop");
  }
  enable_interrupts();
  return;
}

