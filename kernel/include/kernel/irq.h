#ifndef __IRQ_H__
#define __IRQ_H__ 1

void init_irq();
void hook_irq_handler(int index, void *handler);

#endif