#include <stdio.h>
#include <stdlib.h>
#include "order.h"
#include "hardware.h"
#include "elevator.h"


void read_orders(struct elevatorState *state){
    if(state->lastVisitedFloor != 0){
        /* Lights are set and cleared like this: */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            /* Internal orders */
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
                state->orderInside[f] = true;
            }

            /* Orders going up */
            if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
                state->orderUp[f] = true;
            }

            /* Orders going down */
            if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
                state->orderDown[f] = true;
            }
        }
    }
}