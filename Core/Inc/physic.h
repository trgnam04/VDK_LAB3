/*
 * physic.h
 *
 *  Created on: Sep 16, 2024
 *      Author: ASUS
 */

#ifndef INC_PHYSIC_H_
#define INC_PHYSIC_H_

#include "main.h"
#include "software_timer.h"
#include "led7seg_process.h"


extern void turnOnRed(uint8_t index);
extern void turnOnYellow(uint8_t index);
extern void turnOnGreen(uint8_t index);

extern void test7seg(void);
extern void testAllLed(void);

extern void turnOnAllLed(void);
extern void turnOffAllLed(void);

extern void blinkRed(void);
extern void blinkYellow(void);
extern void blinkGreen(void);







#endif /* INC_PHYSIC_H_ */
