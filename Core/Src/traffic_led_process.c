/*
 * traffic_led_process.c
 *
 *  Created on: Sep 13, 2024
 *      Author: ASUS
 */

#include "main.h"
#include "software_timer.h"
#include "traffic_led_process.h"
#include "led7seg_process.h"
#include "physic.h"
#include "button.c"


#define DEFAULT_RED		15
#define DEFAULT_YELLOW	3
#define DEFAULT_GREEN	12

uint16_t led_red1_counter;
uint16_t led_red2_counter;
uint16_t led_yellow1_counter;
uint16_t led_yellow2_counter;
uint16_t led_green1_counter;
uint16_t led_green2_counter;

uint16_t modify_led_counter = 0;

unsigned char tempState = 0;

enum traffic_state {INIT_STATE, ERROR_STATE, AUTO_MODE, SETTING_RED_MODE, SETTING_YELLOW_MODE, SETTING_GREEN_MODE};
enum traffic_state trafficState;

enum traffic_phase {INIT_PHASE, PHASE1, PHASE2, PHASE3, PHASE4};
enum traffic_phase trafficPhase;

void init_traffic_process(void){
	trafficState = INIT_STATE;
	trafficPhase = INIT_PHASE;
	init_traffic_time();
}

void init_traffic_time(void){
	led_red1_counter = DEFAULT_RED;
	led_red2_counter = DEFAULT_RED;
	led_yellow1_counter = DEFAULT_YELLOW;
	led_yellow2_counter = DEFAULT_YELLOW;
	led_green1_counter = DEFAULT_GREEN;
	led_green2_counter = DEFAULT_GREEN;

}

void auto_mode_process(void){
	switch(trafficPhase){
	case INIT_PHASE:{
		testAllLed();

		trafficPhase = PHASE1;
		break;
	}
	case PHASE1:{
		led_red1_counter--;
		led_green2_counter--;

		turnOnGreen(2);
		turnOnRed(1);

		setLed7Seg(0, led_red1_counter / 10);
		setLed7Seg(1, led_red1_counter % 10);

		setLed7Seg(2, led_green2_counter / 10);
		setLed7Seg(3, led_green2_counter % 10);

		if(!led_green2_counter){
			trafficPhase = PHASE2;
		}

		break;
	}
	case PHASE2:{
		led_red1_counter--;
		led_yellow2_counter--;

		turnOnYellow(2);
		turnOnRed(1);

		setLed7Seg(0, led_red1_counter / 10);
		setLed7Seg(1, led_red1_counter % 10);

		setLed7Seg(2, led_yellow2_counter / 10);
		setLed7Seg(3, led_yellow2_counter % 10);

		if(!led_yellow2_counter){
			trafficPhase = PHASE3;
		}

		break;
	}
	case PHASE3:{
		led_red2_counter--;
		led_green1_counter--;

		turnOnRed(2);
		turnOnGreen(1);

		setLed7Seg(0, led_green1_counter / 10);
		setLed7Seg(1, led_green1_counter % 10);

		setLed7Seg(2, led_red2_counter / 10);
		setLed7Seg(3, led_red2_counter % 10);

		if(!led_green1_counter){
			trafficPhase = PHASE4;
		}

		break;
	}
	case PHASE4:{
		led_red2_counter--;
		led_yellow1_counter--;

		turnOnRed(2);
		turnOnYellow(1);

		setLed7Seg(0, led_yellow1_counter / 10);
		setLed7Seg(1, led_yellow1_counter % 10);

		setLed7Seg(2, led_red2_counter / 10);
		setLed7Seg(3, led_red2_counter % 10);

		if(!led_yellow1_counter){
			trafficPhase = PHASE1;
		}


		break;
	}
	}
}

void resetAllLed(void){
	HAL_GPIO_WritePin(LED_RED1_GPIO_Port, LED_RED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_RED2_GPIO_Port, LED_RED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port, LED_GREEN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port, LED_GREEN2_Pin, GPIO_PIN_RESET);

	setLed7Seg(0, 0);
	setLed7Seg(1, 0);
	setLed7Seg(2, 0);
	setLed7Seg(3, 0);

}

void blink_led_red(void){
	if(timer1_flag){
		HAL_GPIO_TogglePin(GPIOA, LED_RED1_Pin | LED_RED2_Pin);
		setTimer1(50);
	}
}

void blink_led_yellow(void){
	if(timer1_flag){
		HAL_GPIO_TogglePin(GPIOA, LED_YELLOW1_Pin | LED_YELLOW2_Pin);
		setTimer1(50);
	}
}

void blink_led_green(void){
	if(timer1_flag){
		HAL_GPIO_TogglePin(GPIOA, LED_GREEN1_Pin | LED_GREEN2_Pin);
		setTimer1(50);
	}
}

unsigned char check_error(){
	return !(led_red1_counter == (led_yellow1_counter + led_green1_counter))
			&& !(led_red2_counter == (led_yellow2_counter + led_green2_counter));
}

void increase_led_counter(void){
	modify_led_counter = (modify_led_counter + 1) % 100;
}

void decrease_led_counter(void){
	modify_led_counter = modify_led_counter >= 1 ? (modify_led_counter - 1) % 100 : 99;
}

void traffic_process(void){
	switch(trafficState){
	case ERROR_STATE:{
		break;
	}
	case INIT_STATE:{
		if(check_error())
			trafficState = ERROR_STATE;
		else
			trafficState = AUTO_MODE;
		break;
	}
	case AUTO_MODE:{
		if(timer3_flag){
			auto_mode_process();
			setTimer3(100);
		}


		if(is_button_press(0)){
			trafficState = SETTING_RED_MODE;
		}
		break;
	}
	case SETTING_RED_MODE:{
		resetAllLed();
		blink_led_red();
		modify_led_counter = led_red1_counter;

		if(is_button_press(1)){
			modify_led_counter = (modify_led_counter + 1) % 100;
		}



		setLed7Seg(0, modify_led_counter / 10);
		setLed7Seg(1, modify_led_counter % 10);

		setLed7Seg(2, 0);
		setLed7Seg(3, 1);

		led_red1_counter = modify_led_counter;
		led_red2_counter = modify_led_counter;

		if(is_button_press(0)){
			trafficState = SETTING_GREEN_MODE;
		}

		break;
	}
	case SETTING_GREEN_MODE:{
		resetAllLed();
		blink_led_green();
		modify_led_counter = led_green1_counter;



		if(is_button_press(1)){
			modify_led_counter = (modify_led_counter + 1) % 100;
		}


		setLed7Seg(0, modify_led_counter / 10);
		setLed7Seg(1, modify_led_counter % 10);

		setLed7Seg(2, 0);
		setLed7Seg(3, 2);

		led_green1_counter = modify_led_counter;
		led_green2_counter = modify_led_counter;

		if(is_button_press(0)){
			trafficState = SETTING_YELLOW_MODE;
		}
		break;
	}
	case SETTING_YELLOW_MODE:{
		resetAllLed();
		blink_led_yellow();
		modify_led_counter = led_yellow1_counter;



		if(is_button_press(1)){
			modify_led_counter = (modify_led_counter + 1) % 100;
		}


		setLed7Seg(0, modify_led_counter / 10);
		setLed7Seg(1, modify_led_counter % 10);

		setLed7Seg(2, 0);
		setLed7Seg(3, 3);

		led_yellow1_counter = modify_led_counter;
		led_yellow2_counter = modify_led_counter;

		if(is_button_press(0)){
			trafficState = INIT_STATE;
		}

		break;
	}
	}
}
