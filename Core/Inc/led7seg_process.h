/*
 * led7seg_process.h
 *
 *  Created on: Sep 10, 2024
 *      Author: ASUS
 */

#ifndef INC_LED7SEG_PROCESS_H_
#define INC_LED7SEG_PROCESS_H_



extern void initLed7Seg(void);
extern void setLed7Seg(uint8_t idx, uint8_t value); // set value for led variable, call in fsm process
extern void Led7Seg_Scanning(void); // implement fsm, call in interrupt callback
extern void setLed7Seg_process(uint8_t value); // set code for led


#endif /* INC_LED7SEG_PROCESS_H_ */
