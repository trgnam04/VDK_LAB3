/*
 * traffic_led_process.h
 *
 *  Created on: Sep 13, 2024
 *      Author: ASUS
 */

#ifndef INC_TRAFFIC_LED_PROCESS_H_
#define INC_TRAFFIC_LED_PROCESS_H_


void init_traffic_time(void);
extern void init_traffic_process(void);
extern void traffic_process(void);
extern void auto_mode_process(void);

void blink_led_red(void);
void blink_led_yellow(void);
void blink_led_green(void);

void increase_led_counter(void);
void decrease_led_counter(void);

#endif /* INC_TRAFFIC_LED_PROCESS_H_ */
