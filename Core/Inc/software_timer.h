/*
 * software_timer.h
 *
 *  Created on: Sep 10, 2024
 *      Author: ASUS
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "button.h"
#include "main.h"

#define TIMER_CYCLE_1 1
#define TIMER_CYCLE_2 1
#define TIMER_CYCLE_3 1


extern unsigned char timer1_flag;
extern unsigned char timer2_flag;
extern unsigned char timer3_flag;

extern void timerInit(void);
extern void setTimer1(int duration);
extern void setTimer2(int duration);
extern void setTimer3(int duration);
void timer1Run(void);
void timer2Run(void);
void timer3Run(void);







#endif /* INC_SOFTWARE_TIMER_H_ */
