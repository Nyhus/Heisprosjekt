#include "hardware.h"

#define BOTTOM_FLOOR 0
#define TOP_FLOOR 3

int nextFloorToStopAt(elevatorState *state){
  switch(state->elevatorDirection) {
    case(MOVEMENT_UP) :
      short currFloor = eleState->lastVisitedFloor;
      array[4] floorsWithOrder;
      for (short i = currFloor; i < 4; i++){ floorsWithOrder[i] = state->orderUp[i] | state->orderInside[i]; };
      for (short i = 3; i == currFloor; i--){ if (floorsWithOrder[i] < orderDown[i]){ floorsWithOrder[i] = 1; break; } };
      for (short i = currFloor; i < 4; i++){ if (floorsWithOrder[i] == 1){return i } };
      return -1;

    case(MOVEMENT_DOWN) :
      short currFloor = eleState->lastVisitedFloor;
      array[4] floorsWithOrder;
      for (short i = currFloor; i == BOTTOM_FLOOR; i--){ floorsWithOrder[i] = orderDown[i] | state->orderInside[i]; };
      for (short i = BOTTOM_FLOOR; i == currFloor; i++){ if (floorsWithOrder[i] < state->orderUp[i]){ floorsWithOrder[i] = 1; break; } };
      for (short i = currFloor; i == BOTTOM_FLOOR; i--){ if (floorsWithOrder[i] == 1){return i;} };
      return -1;

    case(IDLE) :
      for (i = 0; i < 4; i++){ if (state->orderUp[i] | orderDown[i] | state->orderInside[i] == 1) { return i;} };
      return -1
  }
}
