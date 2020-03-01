#include <math.h>
#include "elevator.h"
#include "hardware.h"
#include <stdio.h>

int q_nextTargetDirectionUp(struct elevatorState *state){
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

int q_nextTargetDirectionDown(struct elevatorState *state){
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

int q_nextTargetNoDirection(struct elevatorState *state){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            
            if(state->orderDown[i] == true){
               return i;
            }

            if(state->orderUp[i] == true){
                return i;
            }

            if(state->orderInside[i] == true){
                return i;
            }
    }
       return -1;
}

void q_updateTargetFloor(struct elevatorState *state){
	switch(state->movementState){
        case MOVEMENT_UP :
                if(q_nextTargetDirectionUp(state) == -1){
                        state->movementState = MOVEMENT_DOWN;
	        }else{
                        state->targetFloor = q_nextTargetDirectionUp(state);
		}
                return;
        case MOVEMENT_DOWN :
                if(q_nextTargetDirectionDown(state) == -1){
                        state->movementState = MOVEMENT_UP;
		}else{
                        state->targetFloor = q_nextTargetDirectionDown(state);     
		}
                return;
        case MOVEMENT_IDLE :
                state->targetFloor = q_nextTargetNoDirection(state);
                return;
	}
}

void q_updateNextFloor(struct elevatorState *state){
        switch(state->movementState){
                case(MOVEMENT_UP) :
                        for (int i = 0; i < 4; i++){ if(hardware_read_floor_sensor(i)){state->nextFloor = i + 1 ;}}
                        break;
                case(MOVEMENT_DOWN) :
                        for (int i = 0; i < 4; i++){ if(hardware_read_floor_sensor(i)){state->nextFloor = i - 1 ;}}
                        break;
                case(MOVEMENT_IDLE) :
                        break;
        }
}

void q_setIdleIfNoOrder(struct elevatorState *state){
        short tracker = 0; 
         for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(state->orderUp[f]){
                tracker = 1;
            }
            if(state->orderDown[f]){
                tracker = 1;
            }
            if(state->orderInside[f]){
                tracker = 1;
            }
         }
        if (tracker == 0){
            state->movementState = MOVEMENT_IDLE;
        }
}

