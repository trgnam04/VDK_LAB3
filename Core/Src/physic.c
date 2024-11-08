/*
 * physic.c
 *
 *  Created on: Sep 16, 2024
 *      Author: ASUS
 */

#include "physic.h"

extern void turnOnAllLed(void){
	HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin | LED_RED2_Pin | LED_GREEN1_Pin | LED_GREEN2_Pin |
			LED_YELLOW1_Pin | LED_YELLOW2_Pin, GPIO_PIN_SET);

}
extern void turnOffAllLed(void){
	HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin | LED_RED2_Pin | LED_GREEN1_Pin | LED_GREEN2_Pin |
					LED_YELLOW1_Pin | LED_YELLOW2_Pin, GPIO_PIN_RESET);
}

void test7seg(void){
	setLed7Seg(0, 0);
	setLed7Seg(1, 0);
	setLed7Seg(2, 0);
	setLed7Seg(3, 0);
}

void testAllLed(void){
	turnOnAllLed();
	HAL_Delay(1000);
	turnOffAllLed();
}



void turnOnRed(uint8_t index){
	if(index == 1){
		HAL_GPIO_WritePin(GPIOA, LED_RED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN1_Pin | LED_YELLOW1_Pin, GPIO_PIN_RESET);
	}
	else if(index == 2){
		HAL_GPIO_WritePin(GPIOA, LED_RED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN2_Pin | LED_YELLOW2_Pin, GPIO_PIN_RESET);
	}

}

void turnOnYellow(uint8_t index){
	if(index == 1){
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN1_Pin | LED_RED1_Pin, GPIO_PIN_RESET);
	}
	else if(index == 2){
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN2_Pin | LED_RED2_Pin, GPIO_PIN_RESET);
	}

}

void turnOnGreen(uint8_t index){
	if(index == 1){
		HAL_GPIO_WritePin(GPIOA, LED_GREEN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW1_Pin | LED_RED1_Pin, GPIO_PIN_RESET);
	}
	else if(index == 2){
		HAL_GPIO_WritePin(GPIOA, LED_GREEN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW2_Pin | LED_RED2_Pin, GPIO_PIN_RESET);
	}
}


void blinkRed(void){
	if(timer1_flag){
		HAL_GPIO_TogglePin(GPIOA, LED_RED1_Pin | LED_RED2_Pin);
		setTimer1(50);
	}
}

void blinkYellow(void){
	if(timer1_flag){
		HAL_GPIO_TogglePin(GPIOA, LED_YELLOW1_Pin | LED_YELLOW2_Pin);
		setTimer1(50);
	}
}

void blinkGreen(void){
	if(timer1_flag){
		HAL_GPIO_TogglePin(GPIOA, LED_GREEN2_Pin | LED_GREEN1_Pin);
		setTimer1(50);
	}
}

