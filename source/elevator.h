/**
 * @file
 * @brief Module for updating and keeping track of elevator state.
 *
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>

/** 
 * @brief Keeps track of states. 
 */
struct elevatorState {
    bool orderUp[3];
    bool orderDown[3];
    bool orderInside[4];
    bool stopButton;
    bool doorOpen;
    bool obstruction;
    bool movementState[3];
};


/**
 * @brief Sets everything to zero and false.
*/
void flushState(struct elevatorState *state);

#endif