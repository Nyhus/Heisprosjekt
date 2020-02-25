 /**
 * @file
 * @brief Module for controlling elevator doors.
 *
 */
#ifndef DOORS_H
#define DOORS_H

/**
 * @brief Sets door light ON and starts timer */ 
void openDoors();
/**
 * @brief Checks timer and sets door lights OFF */ 
void closeDoors();

#endif