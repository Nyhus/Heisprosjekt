#include <stdio.h>
#include <stdlib.h>
#include "elevator.h"


void flushState(struct elevatorState *state){
    // for (int i = 0; i < sizeOf(); i++;) {}
    state->orderUp[0] = 0;
    state->orderUp[1] = 0;
    state->orderUp[2] = 0;
    state->orderDown[0] = 0;
    state->orderDown[1] = 0;
    state->orderDown[2] = 0;
    state->orderInside[0] = 0;
    state->orderInside[1] = 0;
    state->orderInside[2] = 0;
    state->orderInside[3] = 0;
    state->stopButton = false;
    state->doorOpen = false;
    state->obstruction = false;
    state->movementState[0] = 0;
    state->movementState[1] = 0;
    state->movementState[2] = 0;
}
