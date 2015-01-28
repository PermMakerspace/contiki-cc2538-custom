#include "contiki.h"
#include "dev/serial-line.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include <stdio.h>
#include <string.h> /* for strcpy */

#define HSTR "hello"
static uint16_t user_timer = 0;

PROCESS(test_serial, "serial line test process");
AUTOSTART_PROCESSES(&test_serial);

PROCESS_THREAD(test_serial, event, data){
	PROCESS_BEGIN();
	while(1){
		PROCESS_YIELD();
		if(event == serial_line_event_message){
			if(!strcmp((char *)data, HSTR)){
				printf("Hello yourself!\n");
			}else{
				printf("Received: %s\n", (char *)data);
			}
		}else if(event == sensors_event){
			if(data == &button_left_sensor){
				user_timer++;
				printf("timer = %d\n", user_timer);
				printf("Don\'t touch me.\n");
			}
		}
	}
	PROCESS_END();
}
