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
 * @warning Pressing the stop button or releasing the obstruction switch will restart the timer to 3 seconds.
*/
void openDoors(struct elevatorState* liftState);

#endif
