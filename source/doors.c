#include "doors.h"
#include "time.h"
#include "elevator.h"
#include "order.h"
#include "hardware.h"
#include <stdio.h>

time_t startTime; 

void openDoors(struct elevatorState* state){
    clock_t currentClock, startClock;
    int secondsToWait = 3;
    int time_left = 0;

    startClock = clock();
    time_left = secondsToWait;
    hardware_command_stop_light(0);
    hardware_command_door_open(1);
    while(time_left > 0){
        currentClock = clock();
        time_left = secondsToWait - ((currentClock - startClock)/(CLOCKS_PER_SEC));
        if(hardware_read_obstruction_signal()){
            startClock = clock();
        }
        if(hardware_read_stop_signal()){
            startClock = clock();
            clear_all_order_lights();
            flushState(state);
            hardware_command_stop_light(1);
        }
        else{
            hardware_command_stop_light(0);
            read_orders(state);
        }
    }
    hardware_command_door_open(0);
}

void openDoorsIfOrderedToCurrentFloor(struct elevatorState *state){
        short tracker = 0;
         for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
           
            if(hardware_read_order(f,HARDWARE_ORDER_UP) && (hardware_read_floor_sensor(f)) && state->movementState == MOVEMENT_IDLE){
                tracker = 1;
            }
            if(hardware_read_order(f,HARDWARE_ORDER_DOWN) && (hardware_read_floor_sensor(f)) && state->movementState == MOVEMENT_IDLE){
                tracker = 1;
            }
            if(hardware_read_order(f,HARDWARE_ORDER_INSIDE) && (hardware_read_floor_sensor(f)) && state->movementState == MOVEMENT_IDLE){
                tracker = 1;
            }
         }
        if (tracker == 1){
            openDoors(state);
        }
}
