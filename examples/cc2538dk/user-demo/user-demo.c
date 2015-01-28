#include "contiki.h"
#include <stdio.h>
#include "leds.h"

PROCESS(user-demo, "user demo process");
PROCESS(blink, "stupid blink process");
AUTOSTART_PROCESSES(&user-demo, &blink);
PROCESS_THREAD(user-demo, events, data){
	PROCESS_BEGIN();
	while(1){
		printf("event: %s data: %s\n", events, data);
	}
	PROCESS_END();
}
PROCESS_THREAD(blink, events, data){
	static struct etimer timer;
	PROCESS_BEGIN();
	etimer_set(&timer, CLOCK_CONF_SECOND);
	while(1){
		PROCESS_WAIT_EVENT();
		if(events == PROCESS_EVENT_TIMER){
			leds_toggle(LEDS_RED);
		}
	}
	PROCESS_END();
}
