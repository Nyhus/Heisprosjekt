 /**
 * @file
 * @brief Module for controlling elevator doors.
 *
 */
#ifndef DOORS_H
#define DOORS_H
#include "elevator.h"

/**
 * @brief Opens doors while making sure orders are still handled. Will close the doors after 3 seconds. 
 * @param @p state Pointer to elevator state.
 *
 * @warning Pressing the stop button or releasing the obstruction switch will restart the timer to 3 seconds.
*/
void d_openDoors(struct elevatorState* state);

/** 
 * @brief Checks for orders to a floor the elevator is idling in and opens doors if idle.
 * @param @p state Pointer to elevator state.
 */
void d_openDoorsIfOrderedToCurrentFloor(struct elevatorState *state);

#endif
