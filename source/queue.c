include <math.h>
include "elevator.h"

int nextTargetDirectionUp(struct elevatorState *state){
    int highestOrderDown = -1;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i, HARDWARE_ORDER_DOWN) && i > highestOrderDown && i > state->lastVisitedFloor){
                highestOrderDown = i;
        }
	}
    int lowestOrderUp = 4;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i, HARDWARE_ORDER_UP) && i < lowestOrderUp && i > state->lastVisitedFloor){
                lowestOrderUp = i;
        }
	}
    int lowestOrderInside = 4;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i, HARDWARE_ORDER_INSIDE) && i < lowestOrderInside && i > state->lastVisitedFloor){
                lowestOrderInside = i;
        }
	}
    if(lowestOrderInside == 4 && lowestOrderUp == 4){
        return highestOrderDown;
	}else if(lowestOrderInside == 4 && lowestOrderUp != 4){
        return lowestOrderUp;
	}else if(lowestOrderInside != 4 && lowestOrderUp == 4){
        return lowestOrderInside;
	}else{
        return fmin(lowestOrderInside,lowestOrderUp);
	}
}

int nextTargetDirectionDown(struct elevatorState *state){
    int highestOrderDown = -1;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i, HARDWARE_ORDER_DOWN) && i > highestOrderDown && i < state->lastVisitedFloor){
                highestOrderDown = i;
        }
	}
    int lowestOrderUp = 4;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i, HARDWARE_ORDER_UP) && i < lowestOrderUp && i < state->lastVisitedFloor){
                lowestOrderUp = i;
        }
	}
    int highestOrderInside = -1;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_order(i, HARDWARE_ORDER_INSIDE) && i > lowestOrderInside && i < state->lastVisitedFloor){
                highestOrderInside = i;
        }
	}
    if(highestOrderInside == -1  && highestOrderDown == -1){
        if(lowestOrderUp == 4){
            return -1;  
		}else{
            return lowestOrderUp;
		}
	}else if(highestOrderInside == -1 && highestOrderDown != -1){
        return highestOrderDown;
	}else if(highestOrderInside != -1 && highestOrderDown == -1){
        return highestOrderInside;
	}else{
        return fmax(highestOrderDown,highestOrderInside);
	}
}

int nextTargetNoDirection(struct elevatorState *state){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            
            if(hardware_read_order(i, HARDWARE_ORDER_INSIDE)){
                return i;
            }

            if(hardware_read_order(i, HARDWARE_ORDER_UP)){
                return i;
            }

            if(hardware_read_order(i, HARDWARE_ORDER_DOWN)){
                return i;
            }
    }
}

void updateTargetFloor(struct elevatorState *state){
	switch(state->movementState){
        case MOVEMENT_UP :
            if(nextTargetDirectionUp(state) == -1){
                state->movementState = MOVEMENT_DOWN;
			}else{
                state->targetFloor = nextTargetDirectionUp(state);
			}
        case MOVEMENT_DOWN :
            if(nextTargetDirectionDown(state) == -1){
                state->movementState = MOVEMENT_UP;
			}else{
                state->targetFloor = nextTargetDirectionDown(state);     
			}
        case MOVEMENT_IDLE :
            state->targetFloor = nextTargetNoDirection(state);
	}
}


void updateNextFloor(struct elevatorState *state){
    if(state->movementState == MOVEMENT_UP){
        state->nextFloor = state->lastVisitedFloor + 1;
	}else if(state->movementState == MOVEMENT_DOWN){
        state->nextFloor = state->lastVisitedFloor - 1;
	}
}