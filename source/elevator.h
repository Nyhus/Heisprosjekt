/**
 * @file
 * @brief Module for updating and keeping track of elevator state.
 *
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>
#include "hardware.h"

/** 
 * @brief Keeps track of states. 
 */
struct elevatorState {
    bool orderUp[3];
    bool orderDown[3];
    bool orderInside[4];
    unsigned short lastVisitedFloor;
    bool stopButton;
    bool doorOpen;
    bool obstruction;
    bool movementState[3];
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