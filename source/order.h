/**
 * @file
 * @brief Module for elevator orders.
 */
#ifndef ORDER_H
#define ORDER_H
#include "hardware.h"
#include "elevator.h"


/**
 * @brief Clears the order lights; inside elevator and on all floors.
 */
void clear_all_order_lights();

/**
 * @brief Updates state with all new orders.
 * @param @p state Pointer to the elevator state.
 */
void read_orders(struct elevatorState *state);

/**
 * @brief Clears order when the elevator arrives at floor.
 * @param @p state Pointer to the elevator state.
 * @param floorToUpdate Floor to remove order for.
 */
void clear_order(struct elevatorState *state, int floorToUpdate);

#endif
