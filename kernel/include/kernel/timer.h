#ifndef __TIMER_H__
#define __TIMER_H__ 1

#include <stdint.h>

#define TIMER_CHANNEL_0_PORT 0x40
#define TIMER_CHANNEL_1_PORT 0x41
#define TIMER_CHANNEL_2_PORT 0x42
#define TIMER_MODE_PORT      0x43

#define TIMER_MODE_BCD (1 << 0)

// TODO shift operation wrong?
#define TIMER_OP_MODE_0 (0 << 1)
#define TIMER_OP_MODE_1 (1 << 1)
#define TIMER_OP_MODE_2 (2 << 1)
#define TIMER_OP_MODE_3 (3 << 1)
#define TIMER_OP_MODE_4 (4 << 1)
#define TIMER_OP_MODE_5 (5 << 1)

#define TIMER_ACCESS_MODE_LATCH_COUNT       (0 << 4)
#define TIMER_ACCESS_MODE_LOW_BYTE_ONLY     (1 << 4)
#define TIMER_ACCESS_MODE_HIGH_BYTE_ONLY    (2 << 4)
#define TIMER_ACCESS_MODE_LOW_AND_HIGH_BYTE (3 << 4)

#define TIMER_CHANNEL_SELECT_0                 (0 << 6)
#define TIMER_CHANNEL_SELECT_1                 (1 << 6)
#define TIMER_CHANNEL_SELECT_2                 (2 << 6)
#define TIMER_CHANNEL_SELECT_READ_BACK_COMMAND (3 << 6)

extern void _timer_irq();

extern void init_timer();
extern void sleep(uint32_t ms);

#endif