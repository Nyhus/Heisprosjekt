#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "hardware.h"
#include "order.h"
#include "elevator.h"
#include "doors.h"
#include "queue.h"

static void clear_all_order_lights(){
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

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
	printf("Start! \n");
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    printf("=== Program start ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    struct elevatorState state = {.lastVisitedFloor = -1};
    struct elevatorState *eleState;
    eleState = &state;
    
    while(eleState->lastVisitedFloor == -1){
        initializeElevator(eleState);
	}
    printf("lastVisitedFloor before while:%d------\n",eleState->lastVisitedFloor);

    while(1){
        // printf("X\n");
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            clear_all_order_lights();
            hardware_command_stop_light(1);
        }else{
            hardware_command_stop_light(0);
        }
        if(hardware_read_order(3, HARDWARE_ORDER_INSIDE)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
        /*if(hardware_read_floor_sensor(0)){
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
        }
        if(hardware_read_floor_sensor(HARDWARE_NUMBER_OF_FLOORS - 1)){
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        }*/


        /* For-loop for updating last visited floor */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
                eleState->lastVisitedFloor = f;
            }
        }
        if(eleState->lastVisitedFloor == eleState->targetFloor){
            clear_order(eleState,eleState->lastVisitedFloor);
            printf("lastVisited == target, %d\n",eleState->movementState);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            updateTargetFloor(eleState);
            printf("targetFloor updated\n");
            printf("%d\n",eleState->targetFloor);
            // updateNextFloor(eleState);
		}
        if(eleState->targetFloor > eleState->lastVisitedFloor){
            printf("targetFloor larger than lastVisited\n");
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
		}else if(eleState->targetFloor < eleState->lastVisitedFloor){
            // printf("targetFloor smaller than lastVisited\n");
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
		}else{
            printf("targetFloor == lastVisitedFloor");
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);  
		}

        read_orders(eleState);
        // closeDoors(eleState);
        if(hardware_read_obstruction_signal()){
            eleState->obstruction = true;
        }else{
            eleState->obstruction = false;
        }
    }
    return 0;
}