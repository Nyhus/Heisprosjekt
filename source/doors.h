 /**
 * @file
 * @brief Module for controlling elevator doors.
 *
 */
#ifndef DOORS_H
#define DOORS_H
#include "elevator.h"

/**
 * @brief Sets door light ON and starts timer */ 
void openDoors(struct elevatorState* liftState);
/**
 * @brief Checks timer and sets door lights OFF */ 
void closeDoors();

void timer(struct elevatorState* liftState);

#endif