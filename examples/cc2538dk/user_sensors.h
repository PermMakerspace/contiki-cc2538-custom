#include "dev/ioc.h"
#include "dev/gpio.h"

#define BUTTON_USER_PORT	GPIO_B_NUM
#define BUTTON_USER_PIN		1
#define BUTTON_USER_PORT_BASE	GPIO_PORT_TO_BASE(BUTTON_USER_PORT)
#define BUTTON_USER_PIN_MASK	GPIO_PIN_MASK(BUTTON_USER_PIN)

static int config_userbtn(int type, int value){
	config(BUTTON_USER_PORT_BASE, BUTTON_USER_PIN_MASK);
	ioc_set_over(BUTTON_USER_PORT, BUTTON_USER_PIN, IOC_OVERRIDE_PUE);
	
}
