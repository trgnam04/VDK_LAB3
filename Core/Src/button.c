/*
 * button.c
 *
 *  Created on: Sep 10, 2024
 *      Author: ASUS
 */

#include "button.h"

#define NO_OF_BUTTON 3

#define BUTTON_IS_PRESSED  0
#define BUTTON_IS_RELEASED 1
#define DURATION_FOR_AUTO_INCREASING 100

static GPIO_PinState buttonBuffer[NO_OF_BUTTON];
static GPIO_PinState debounceButton1[NO_OF_BUTTON]; // scan every 20ms
static GPIO_PinState debounceButton2[NO_OF_BUTTON];
static GPIO_PinState debounceButton3[NO_OF_BUTTON];
static uint8_t flagforButtonPressed1s[NO_OF_BUTTON];
static uint8_t counterforButtonPressed1s[NO_OF_BUTTON];


void button_reading(void){
	for(int i = 0; i < NO_OF_BUTTON; i++){
		debounceButton1[i] = debounceButton2[i];
		debounceButton2[i] = debounceButton3[i];
		updateButtonState(i);

		if(debounceButton3[i] == debounceButton1[i]){
			buttonBuffer[i] = debounceButton1[i];
			if(buttonBuffer[i] == BUTTON_IS_PRESSED){
				if(counterforButtonPressed1s[i] < DURATION_FOR_AUTO_INCREASING){
					counterforButtonPressed1s[i]++;
				}
				else{
					flagforButtonPressed1s[i] = 1;
				}
			}
			else{
				flagforButtonPressed1s[i] = 0;
				counterforButtonPressed1s[i] = 0;
			}
		}
	}
}

void updateButtonState(uint8_t idx){
	switch(idx){
	case 0:{
		debounceButton3[idx] = HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin);
		break;
	}
	case 1:{
		debounceButton3[idx] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
		break;
	}
	case 2:{
		debounceButton3[idx] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
		break;
	}
	default:{
		break;
	}
	}
}

unsigned char is_button_press(uint8_t idx){
	if(idx > NO_OF_BUTTON) return 0;
	return (buttonBuffer[idx] == BUTTON_IS_PRESSED);
}

unsigned char is_button_press1s(uint8_t idx){
	if(idx > NO_OF_BUTTON) return 0;
	return (flagforButtonPressed1s[idx] == 1);
}



