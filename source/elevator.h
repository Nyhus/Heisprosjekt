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
 * @brief Movement direction used in @c elevatorState.
 */
typedef enum {
    MOVEMENT_UP,
    MOVEMENT_IDLE,
    MOVEMENT_DOWN
} movementDirection;

/** 
 * @brief Keeps track of all states. 
 */
struct elevatorState {
    bool orderUp[4];
    bool orderDown[4];
    bool orderInside[4];
    short lastVisitedFloor;
    short nextFloor;
    short targetFloor;
    bool stopButton;
    bool doorOpen;
    unsigned long long doorOpenTime;
    bool obstruction;  
    movementDirection movementState;
};

/**
 * @brief Sets all orders to zero and movement state to idle.
 * @param @p state Pointer to elevator state.
*/
void flushState(struct elevatorState *state);

/**
 * @brief Initializes the elevator to a valid position, will only be called on program start.
 * @param @p state Pointer to elevator state.
*/
void initializeElevator(struct elevatorState *state);

#endif
