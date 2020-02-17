#include <stdio.h>
#include <stdlib.h>
#include "order.h"
#include "hardware.h"


void test(){
	hardware_command_floor_indicator_on(2);
	while(1) {
		hardware_command_movement(HARDWARE_MOVEMENT_UP);
	}
}
