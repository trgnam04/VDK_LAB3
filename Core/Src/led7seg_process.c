/*
 * led7seg_process.c
 *
 *  Created on: Sep 10, 2024
 *      Author: ASUS
 */
#include "main.h"
#include <string.h>
#include "led7seg_process.h"

uint8_t counter = 0;
uint8_t led7seg_buffer[4];
const uint8_t LED7SEG_CODES[10] = {
    0b00111111, // 0: A, B, C, D, E, F
    0b00000110, // 1: B, C
    0b01011011, // 2: A, B, D, E, G
    0b01001111, // 3: A, B, C, D, G
    0b01100110, // 4: B, C, F, G
    0b01101101, // 5: A, C, D, F, G
    0b01111101, // 6: A, C, D, E, F, G
    0b00000111, // 7: A, B, C
    0b01111111, // 8: A, B, C, D, E, F, G
    0b01101111  // 9: A, B, C, D, F, G
};



void initLed7Seg(void){
	memset(led7seg_buffer, 0x00, sizeof(led7seg_buffer));
}

void setLed7Seg(uint8_t idx, uint8_t value){
	led7seg_buffer[idx] = value;
}

void Led7Seg_Scanning(void){
	switch(counter){
	case 0:{
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);

		setLed7Seg_process(led7seg_buffer[counter]);
		break;
	}
	case 1:{
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);

		setLed7Seg_process(led7seg_buffer[counter]);
		break;
	}
	case 2:{
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);

		setLed7Seg_process(led7seg_buffer[counter]);
		break;
	}
	case 3:{
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);

		setLed7Seg_process(led7seg_buffer[counter]);
		break;
	}
	default:{
		break;
	}
	}
	counter = (counter + 1) % 4;
}

void setLed7Seg_process(uint8_t value){
	HAL_GPIO_WritePin(LED_7SEG1_GPIO_Port, LED_7SEG1_Pin, !((LED7SEG_CODES[value] >> 0) & 0x01));
	HAL_GPIO_WritePin(LED_7SEG2_GPIO_Port, LED_7SEG2_Pin, !((LED7SEG_CODES[value] >> 1) & 0x01));
	HAL_GPIO_WritePin(LED_7SEG3_GPIO_Port, LED_7SEG3_Pin, !((LED7SEG_CODES[value] >> 2) & 0x01));
	HAL_GPIO_WritePin(LED_7SEG4_GPIO_Port, LED_7SEG4_Pin, !((LED7SEG_CODES[value] >> 3) & 0x01));
	HAL_GPIO_WritePin(LED_7SEG5_GPIO_Port, LED_7SEG5_Pin, !((LED7SEG_CODES[value] >> 4) & 0x01));
	HAL_GPIO_WritePin(LED_7SEG6_GPIO_Port, LED_7SEG6_Pin, !((LED7SEG_CODES[value] >> 5) & 0x01));
	HAL_GPIO_WritePin(LED_7SEG7_GPIO_Port, LED_7SEG7_Pin, !((LED7SEG_CODES[value] >> 6) & 0x01));
}


