#include "contiki.h"
#include "dev/serial-line.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include "cfs/cfs-coffee.h"
#include <stdio.h>
#include <string.h> /* for strcpy */

#define HSTR "hello"
#define MSG "ROW ROW FIGHT THE POWER"
#define FILENAME "test.dat"

static uint32_t user_timer;
static uint16_t freq;
/* static uint8_t count;
static struct rtimer rt;

void rt_callback(struct rtimer *t, void *ptr){
	printf("Counter = %u\n", freq);
	freq = 0;
	rtimer_set(&rt, RTIMER_NOW() + RTIMER_SECOND, 1, rt_callback, NULL);
}*/

PROCESS(test_serial, "serial line test process");
AUTOSTART_PROCESSES(&test_serial);

PROCESS_THREAD(test_serial, event, data){
	PROCESS_BEGIN();
	user_timer = 0;
	freq = 0;
	count = 0;
	char buf[30];
	int fd_write, fd_read, n;
	while(1){
		PROCESS_YIELD();
		if(event == serial_line_event_message){
			if(!strcmp((char *)data, HSTR)){
				printf("Hello yourself!\n");
			}else{
				printf("Received: %s\n", (char *)data);
			}
		}else if(event == sensors_event){
			if(data == &button_right_sensor){
				printf("Right button pressed\n");
				user_timer++;
				/* if(!timer_expired(&rt)){
					freq++;
				} */
			}else if(data == &button_left_sensor){
				printf("Left button pressed\n");
				/* all this doesn't work under cc2538 yet */
				/* count++;
				printf("count == %i\n", count);
				if(count == 2){
					printf("Attempt to write to %s\n", FILENAME);
					fd_write = cfs_open(FILENAME, CFS_WRITE);
					if(fd_write != -1){
						n = cfs_write(fd_write, MSG, sizeof(MSG));
						cfs_close(fd_write);
						printf("Write %i bytes successful\n", n);
					}else{
						printf("Write failed\n");
					}
				}else if(count == 4){
					count = 0;
					printf("Reading from %s file\n\n", FILENAME);
					fd_read = cfs_open(FILENAME, CFS_READ);
					if(fd_read != -1){
						cfs_read(fd_read, buf, sizeof(buf));
						printf("Read successful:\n%s\n", buf);
						cfs_close(fd_read);
					}else{
						printf("Read failed\n");
					}
				} */
				/* rtimer_set(&rt, RTIMER_NOW() + CLOCK_SECOND, 1, rt_callback, NULL); */
			}
		}
	}
	PROCESS_END();
}
