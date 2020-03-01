/**
 * @file
 * @brief Module for elevator queue.
 */

#ifndef QUEUE_H
#define QUEUE_H
#include "elevator.h"

/** 
 * @brief Keeps target floor updated. 
 * @param @p state Pointer to elevator state.
 */
void updateTargetFloor(struct elevatorState *state);

/** 
 * @brief Keeps next floor updated.
 * @param @p state Pointer to elevator state.
 */
void updateNextFloor(struct elevatorState *state);


/** 
 * @brief Returns the next target floor when elevator is going up. If no target floor above elevator, returns -1.
 * @param @p state Pointer to elevator state.
 */
int nextTargetDirectionUp(struct elevatorState *state);

/** 
 * @brief Returns the next target floor when elevator is going down. If no target floor under elevator, returns -1.
 * @param @p state Pointer to elevator state.
 */
int nextTargetDirectionDown(struct elevatorState *state);

/** 
 * @brief Returns the next target floor when elevator stands still. Returns -1 for no orders.
 * @param @p state Pointer to elevator state.
 */
int nextTargetNoDirection(struct elevatorState *state);

/** 
 * @brief Updates state to idle if there are no orders.
 * @param @p state Pointer to elevator state.
 */
void setIdleIfNoOrder(struct elevatorState *state);


#endif
