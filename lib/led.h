//-------| lib/led.h |-------//
#ifndef	LED_H
#define	LED_H 


#include <unistd.h> // usleep()


void init_led(short * address);
void led_down_shift();
void led_up_shift();
void led_blink_all();

#endif
