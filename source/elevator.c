#include <stdio.h>
#include <stdlib.h>
#include "elevator.h"
#include "hardware.h"
#include "doors.h"

void flushState(struct elevatorState *state){
    // for (int i = 0; i < sizeOf(); i++;) {}
    state->orderUp[0] = false;
    state->orderUp[1] = false;
    state->orderUp[2] = false;
    state->orderUp[3] = false;
    state->orderDown[0] = false;
    state->orderDown[1] = false;
    state->orderDown[2] = false;
    state->orderDown[3] = false;
    state->orderInside[0] = false;
    state->orderInside[1] = false;
    state->orderInside[2] = false;
    state->orderInside[3] = false;
    state->movementState = MOVEMENT_IDLE;
}

void initializeElevator(struct elevatorState *state){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    state->movementState = MOVEMENT_DOWN;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            
            state->lastVisitedFloor = i;
            //printf("REEEEEEEEEEEEEEEEEEEEEEE%d\n",state->lastVisitedFloor);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            state->movementState = MOVEMENT_IDLE;
            state->targetFloor = i;

            // state->nextFloor = i;
            //openDoors(state);
            break;
		}
	}
}