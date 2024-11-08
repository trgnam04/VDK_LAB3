/*
 * button.h
 *
 *  Created on: Sep 10, 2024
 *      Author: ASUS
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include <stdint.h>

extern void button_reading(void);
extern unsigned char is_button_press(uint8_t idx);
extern unsigned char is_button_press1s(uint8_t idx);
void updateButtonState(uint8_t idx);

extern uint8_t button_flag;

#endif /* INC_BUTTON_H_ */
