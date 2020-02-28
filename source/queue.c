#include <math.h>
#include "elevator.h"
#include "hardware.h"
#include <stdio.h>

int nextTargetDirectionUp(struct elevatorState *state){
    int highestOrderDown = -1;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(state->orderDown[i] && i > highestOrderDown && i > state->lastVisitedFloor){
                highestOrderDown = i;
        }
	}
    int lowestOrderUp = 4;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(state->orderUp[i] && i < lowestOrderUp && i > state->lastVisitedFloor){
                lowestOrderUp = i;
        }
	}
    int lowestOrderInside = 4;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(state->orderInside[i] && i < lowestOrderInside && i > state->lastVisitedFloor){
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
                if(lowestOrderInside < lowestOrderUp){
                        return lowestOrderInside;
                }else{
                        return lowestOrderUp;
                }
	}
}

int nextTargetDirectionDown(struct elevatorState *state){
    int highestOrderDown = -1;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(state->orderDown[i] && i > highestOrderDown && i < state->lastVisitedFloor){
                highestOrderDown = i;
        }
	}
    int lowestOrderUp = 4;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(state->orderUp[i] && i < lowestOrderUp && i < state->lastVisitedFloor){
                lowestOrderUp = i;
        }
	}
    int highestOrderInside = -1;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(state->orderInside[i] && i > highestOrderInside && i < state->lastVisitedFloor){
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
                if(highestOrderDown > highestOrderInside){
                        return highestOrderDown;
                }else{
                        return highestOrderInside;
                }
        }
}

int nextTargetNoDirection(struct elevatorState *state){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            
            if(state->orderDown[i] == true){
                    printf("1111111111111111111111111111111111111111111           %d\n",i);
                return i;
            }

            if(state->orderUp[i] == true){
                    printf("2222222222222222222222222222222222222222222222           %d\n",i);
                return i;
            }

            if(state->orderInside[i] == true){
                    printf("33333333333333333333333333333333333333333333333           %d\n",i);
                return i;
            }
    }
        return state->lastVisitedFloor;
}

void updateTargetFloor(struct elevatorState *state){
	switch(state->movementState){
        case MOVEMENT_UP :
                //printf("UP\n");
            if(nextTargetDirectionUp(state) == -1){
                state->movementState = MOVEMENT_DOWN;
			}else{
                state->targetFloor = nextTargetDirectionUp(state);
			}
                return;
        case MOVEMENT_DOWN :
                //printf("DOWN\n");
            if(nextTargetDirectionDown(state) == -1){
                state->movementState = MOVEMENT_UP;
			}else{
                state->targetFloor = nextTargetDirectionDown(state);     
			}
                return;
        case MOVEMENT_IDLE :
                //printf("IDLE\n");
            state->targetFloor = nextTargetNoDirection(state);
                return;
	}
}


void updateNextFloor(struct elevatorState *state){
    if(state->movementState == MOVEMENT_UP){
        state->nextFloor = state->lastVisitedFloor + 1;
        }else if(state->movementState == MOVEMENT_DOWN){
        state->nextFloor = state->lastVisitedFloor - 1;
	}
}