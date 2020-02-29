#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "hardware.h"
#include "order.h"
#include "elevator.h"
#include "doors.h"
#include "queue.h"

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
        clear_all_order_lights();
	}
    printf("lastVisitedFloor before while:%d------\n",eleState->lastVisitedFloor);

    while(1){
        if(hardware_read_stop_signal()){
            printf("STOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOPPPPP");
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            clear_all_order_lights();
            flushState(eleState);
            eleState->targetFloor = -1;
            hardware_command_stop_light(1);
            for (int f = 0; f < 4; f++){ 
                if(hardware_read_floor_sensor(f) && hardware_read_stop_signal()){ 
                    openDoors(eleState); 
                    }
            }
        }else{
            hardware_command_stop_light(0);
        }
        if(hardware_read_order(3, HARDWARE_ORDER_INSIDE) && hardware_read_order(0, HARDWARE_ORDER_INSIDE)){ // Innside-knapp 4 terminerer programmet
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }

        /* For-loop for updating last visited floor */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
                eleState->lastVisitedFloor = f;
            }
        }

        if(hardware_read_floor_sensor(eleState->targetFloor)){
            clear_order(eleState,eleState->lastVisitedFloor);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            // OPENDOORS      
            if(eleState->movementState!=MOVEMENT_IDLE){ printf("99999999999999999999999999999999999\n");
                openDoors(eleState);
            }
            updateTargetFloor(eleState);
            updateNextFloor(eleState);
            clear_order(eleState,eleState->lastVisitedFloor);
		}
        if(eleState->targetFloor > eleState->lastVisitedFloor && !hardware_read_stop_signal()){
            eleState->movementState = MOVEMENT_UP;
            hardware_command_movement(HARDWARE_MOVEMENT_UP);
		}else if(eleState->targetFloor < eleState->lastVisitedFloor && !hardware_read_stop_signal() && eleState->targetFloor != -1){
            eleState->movementState = MOVEMENT_DOWN;
            hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
		}else if(eleState->targetFloor == eleState->lastVisitedFloor && !hardware_read_floor_sensor(eleState->lastVisitedFloor)){           
            if(eleState->lastVisitedFloor < eleState->nextFloor){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                eleState->movementState = MOVEMENT_DOWN;
            }
            if(eleState->lastVisitedFloor > eleState->nextFloor){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
                eleState->movementState = MOVEMENT_UP;
            }    
		}else {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);  
        }
        printf("movementDireeeeeeeeeeeeeeeeeeeeeeeeeeeeeeection = %d\n",eleState->movementState);
        printf("targetFloor %d\n",eleState->targetFloor);
        printf("nextFloor %d\n",eleState->nextFloor);printf("lastVisitedFloor %d\n",eleState->lastVisitedFloor);printf("nextFloor %d\n",eleState->nextFloor);printf("nextFloor %d\n",eleState->nextFloor);printf("nextFloor %d\n",eleState->nextFloor);printf("nextFloor %d\n",eleState->nextFloor);printf("nextFloor %d\n",eleState->nextFloor);
                
        read_orders(eleState);
        updateTargetFloor(eleState);
        updateNextFloor(eleState);
        // closeDoors(eleState);
        if(hardware_read_obstruction_signal()){
            eleState->obstruction = true;
        }else{
            eleState->obstruction = false;
        }
        int tracker = 0;
        int tracker1 = 0;
        // SETTER IDLE HVIS INGEN BESTILLINGER
         for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            
            /* Internal orders */
            if(eleState->orderUp[f]){
                tracker = 1;
            }
            /* Orders going up */
            if(eleState->orderDown[f]){
                tracker = 1;
            }
            /* Orders going down */
            if(eleState->orderInside[f]){
                tracker = 1;
            }
            if(hardware_read_order(f,HARDWARE_ORDER_UP) && (hardware_read_floor_sensor(f)) && eleState->movementState == MOVEMENT_IDLE){
                tracker1 = 1;
            }
            if(hardware_read_order(f,HARDWARE_ORDER_DOWN) && (hardware_read_floor_sensor(f)) && eleState->movementState == MOVEMENT_IDLE){
                tracker1 = 1;
            }
            if(hardware_read_order(f,HARDWARE_ORDER_INSIDE) && (hardware_read_floor_sensor(f)) && eleState->movementState == MOVEMENT_IDLE){
                tracker1 = 1;
            }
         }
        if (tracker == 0){
            eleState->movementState = MOVEMENT_IDLE;
            printf("MOVEMENT STATE SET TO IDLE\n");
        }
        if (tracker1 == 1){
            openDoors(eleState);
            printf("OPENING DOOOOOOORS\n");
        }
    }
    return 0;
}