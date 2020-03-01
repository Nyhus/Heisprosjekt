#include <stdio.h>
#include <stdlib.h>
#include "order.h"
#include "hardware.h"
#include "elevator.h"
#include "queue.h"

void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

void read_orders(struct elevatorState *state){
    if(state->lastVisitedFloor != -1 && !hardware_read_stop_signal()){
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

void clear_order(struct elevatorState *state, int floorToUpdate){
    hardware_command_order_light(floorToUpdate, HARDWARE_ORDER_DOWN, 0);
    hardware_command_order_light(floorToUpdate, HARDWARE_ORDER_UP, 0);
    hardware_command_order_light(floorToUpdate, HARDWARE_ORDER_INSIDE, 0);
    state->orderInside[floorToUpdate] = false;
    state->orderDown[floorToUpdate] = false;
    state->orderUp[floorToUpdate] = false;
}
