#ifndef BSP_TIMER_H
#define BSP_TIMER_H

#include <stdint.h>

extern void delay_ms(uint32_t ms);
extern void timer_init(void);
extern void stm0_init(void);

#endif // !BSP_TIMER_H
