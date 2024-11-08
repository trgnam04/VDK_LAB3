/*
 * traffic_led_process.c
 *
 *  Created on: Sep 13, 2024
 *      Author: ASUS
 */

#include "traffic_led_process.h"

#define DEFAULT_RED 15;
#define DEFAULT_YELLOW 3;
#define DEFAULT_GREEN 12;


static uint16_t init_red = 15;
static uint16_t init_yellow = 3;
static uint16_t init_green = 12;

static uint16_t led_red1_counter;
static uint16_t led_red2_counter;
static uint16_t led_yellow1_counter;
static uint16_t led_yellow2_counter;
static uint16_t led_green1_counter;
static uint16_t led_green2_counter;



static unsigned char tempState = 0;
static unsigned char tempState1 = 0;
static unsigned char tempState2 = 0;
static uint16_t modify_led_counter = 0;
static uint8_t increase_freq  = 0;

enum traffic_state {INIT_STATE, ERROR_STATE, AUTO_MODE, SETTING_RED_MODE, SETTING_YELLOW_MODE, SETTING_GREEN_MODE, MANUAL_MODE};
static enum traffic_state trafficState;

enum traffic_phase {INIT_PHASE, PHASE1, PHASE2, PHASE3, PHASE4};
static enum traffic_phase trafficPhase;

enum manual_state{INIT, S1, S2};
static enum manual_state manualState;

void init_traffic_process(void){
	trafficState = INIT_STATE;
	trafficPhase = INIT_PHASE;
	manualState = INIT;
	init_traffic_time();
}

void set_default_traffic_time(void){
	led_red1_counter = DEFAULT_RED;
	led_red2_counter = DEFAULT_RED;
	led_yellow1_counter = DEFAULT_YELLOW;
	led_yellow2_counter = DEFAULT_YELLOW;
	led_green1_counter = DEFAULT_GREEN;
	led_green2_counter = DEFAULT_GREEN;
}

void init_traffic_time(void){
	led_red1_counter = init_red;
	led_red2_counter = init_red;
	led_yellow1_counter = init_yellow;
	led_yellow2_counter = init_yellow;
	led_green1_counter = init_green;
	led_green2_counter = init_green;

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

void manual_mode_process(void){
	switch(manualState){
	case INIT:{
		manualState = S1;
		break;
	}
	case S1:{
		turnOnGreen(1);
		turnOnRed(2);

		if(is_button_press(2)){
			tempState2 = 1;
		}
		if(tempState2 == 1 && !is_button_press(2)){
			tempState2 = 0;
			manualState = S2;
		}

		break;
	}
	case S2:{
		turnOnGreen(2);
		turnOnRed(1);


		if(is_button_press(2)){
			tempState2 = 1;
		}
		if(tempState2 && !is_button_press(2)){
			tempState2 = 0;
			manualState = S1;
		}
		break;
	}
	}

}

unsigned char check_error(){
	return !(led_red1_counter == (led_yellow1_counter + led_green1_counter))
			&& !(led_red2_counter == (led_yellow2_counter + led_green2_counter));
}


void increase_led_counter(uint16_t* modifed_led){
	// push and release button 2 to increase the counter
	if(is_button_press(1)){
		tempState1 = 1;
	}
	if(tempState1 && !is_button_press(1)){
		modify_led_counter = (modify_led_counter + 1) % 100;
		tempState1 = 0;
	}

	// press button 2 to increase the counter every 0.5s

	if(is_button_press1s(1)){
		increase_freq = (increase_freq + 1) % 5;
		if(!increase_freq){
			modify_led_counter = (modify_led_counter + 1) % 100;
		}
	}

	// press button 3 to set
	if(is_button_press(2)){
		tempState2 = 1;
	}
	if(tempState2 && !is_button_press(2)){
		*modifed_led = modify_led_counter;
		tempState2 = 0;
	}

}

void traffic_process(void){

	switch(trafficState){
	case ERROR_STATE:{
		// display if error come
		turnOnAllLed();
		test7seg();

		// press and release button 0 to return auto mode with default traffic time
		if(is_button_press(0)){
			tempState = 1;
		}
		if(tempState && !is_button_press(0)){
			tempState = 0;
			init_traffic_time();
			trafficState = AUTO_MODE;
		}

		break;
	}
	case INIT_STATE:{
		init_traffic_time();

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


		// press and release button to change state
		if(is_button_press(0)){
			tempState = 1;
		}
		if(tempState && !is_button_press(0)){
			tempState = 0;
			modify_led_counter = 0;
			trafficState = SETTING_RED_MODE;
		}

		break;
	}
	case SETTING_RED_MODE:{
		turnOffAllLed();
		blinkRed();

		setLed7Seg(0, modify_led_counter / 10);
		setLed7Seg(1, modify_led_counter % 10);

		setLed7Seg(2, 0);
		setLed7Seg(3, 1);

		increase_led_counter(&init_red);


		// press and release button to change state
		if(is_button_press(0)){
			tempState = 1;
		}
		if(tempState && !is_button_press(0)){
			tempState = 0;
			modify_led_counter = 0;
			trafficState = SETTING_GREEN_MODE;
		}

		break;
	}
	case SETTING_GREEN_MODE:{
		turnOffAllLed();
		blinkGreen();


		setLed7Seg(0, modify_led_counter / 10);
		setLed7Seg(1, modify_led_counter % 10);

		setLed7Seg(2, 0);
		setLed7Seg(3, 2);

		increase_led_counter(&init_green);


		// press and release button to change state
		if(is_button_press(0)){
			tempState = 1;
		}
		if(tempState && !is_button_press(0)){
			tempState = 0;
			modify_led_counter = 0;
			trafficState = SETTING_YELLOW_MODE;
		}
		break;
	}
	case SETTING_YELLOW_MODE:{
		turnOffAllLed();
		blinkYellow();

		setLed7Seg(0, modify_led_counter / 10);
		setLed7Seg(1, modify_led_counter % 10);

		setLed7Seg(2, 0);
		setLed7Seg(3, 3);

		increase_led_counter(&init_yellow);


		// press and release button to change state
		if(is_button_press(0)){
			tempState = 1;
		}
		if(tempState && !is_button_press(0)){
			tempState = 0;
			modify_led_counter = 0;
			trafficState = MANUAL_MODE;
		}

		break;
	}
	case MANUAL_MODE:{
		manual_mode_process();


		if(is_button_press(0)){
			tempState = 1;
		}
		if(tempState && !is_button_press(0)){
			tempState = 0;
			trafficState = INIT_STATE;
		}
		break;
	}
	}
}
