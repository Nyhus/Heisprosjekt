#include <stdio.h>
#include <stdlib.h>
#include "elevator.h"
#include "hardware.h"
#include "doors.h"

void flushState(struct elevatorState *state){
    state->orderUp[0] = 0;
    state->orderUp[1] = 0;
    state->orderUp[2] = 0;
    state->orderUp[3] = 0;
    state->orderDown[0] = 0;
    state->orderDown[1] = 0;
    state->orderDown[2] = 0;
    state->orderDown[3] = 0;
    state->orderInside[0] = 0;
    state->orderInside[1] = 0;
    state->orderInside[2] = 0;
    state->orderInside[3] = 0;
    state->movementState = MOVEMENT_IDLE;
}

void initializeElevator(struct elevatorState *state){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    state->movementState = MOVEMENT_DOWN;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            state->lastVisitedFloor = i;
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            state->movementState = MOVEMENT_IDLE;
            state->targetFloor = i;
            break;
		}
	}
}
