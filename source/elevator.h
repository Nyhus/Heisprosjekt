/**
 * @file
 * @brief Module for updating and keeping track of elevator state.
 *
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>
#include "hardware.h"

typedef enum {
    MOVEMENT_UP,
    MOVEMENT_IDLE,
    MOVEMENT_DOWN
} movementDirection;

/** 
 * @brief Keeps track of states. 
 */
struct elevatorState {
    bool orderUp[3];
    bool orderDown[3];
    bool orderInside[4];
    unsigned short lastVisitedFloor;
    unsigned short nextFloor;
    unsigned short targetFloor;
    bool stopButton;
    bool doorOpen;
    unsigned long long doorOpenTime;
    bool obstruction;
    // bool movementState[3]; // IDLING (nothing to do; 1) -- Movement UP and DOWN (moving; 1)  
    movementDirection movementState;
};


/**
 * @brief Sets everything to zero and false.

 * @param @p state Pointer to elevator state.
*/
void flushState(struct elevatorState *state);

/**
 * @brief Initializes the elevator to a valid position, will only be called before use of elevator.

 * @param @p state Pointer to elevator state.
*/
void initializeElevator(struct elevatorState *state);



#endif