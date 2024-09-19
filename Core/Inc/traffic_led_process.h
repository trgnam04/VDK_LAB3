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

void increase_led_counter(uint16_t* modifed_led);


#endif /* INC_TRAFFIC_LED_PROCESS_H_ */
