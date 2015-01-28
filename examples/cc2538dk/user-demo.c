#include "contiki.h"
#include <stdio.h>
#include "dev/leds.h"
#include "dev/uart.h"

PROCESS(user_demo, "user demo process");
PROCESS(blink, "stupid blink process");
AUTOSTART_PROCESSES(&user_demo, &blink);
PROCESS_THREAD(user_demo, events, data){
	static struct etimer timer;
	PROCESS_BEGIN();
	etimer_set(&timer, CLOCK_SECOND);
	while(1){
		PROCESS_WAIT_EVENT();
		if(events == PROCESS_EVENT_TIMER){
			printf("event: %s data: %s\n", events, data);
			etimer_set(&timer, CLOCK_SECOND);
		}
	}
	PROCESS_END();
}
PROCESS_THREAD(blink, events, data){
	static struct etimer timer;
	PROCESS_BEGIN();
	etimer_set(&timer, CLOCK_SECOND);
	while(1){
		PROCESS_WAIT_EVENT();
		if(events == PROCESS_EVENT_TIMER){
			leds_toggle(LEDS_RED);
			etimer_set(&timer, CLOCK_SECOND);
		}
	}
	PROCESS_END();
}
