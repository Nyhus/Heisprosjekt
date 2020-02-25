#include "doors.h"
#include "time.h"
#include "elevator.h"

time_t startTime; 

void openDoors(){
    // Etasjekontroll
    startTime = time(NULL);
}

void closeDoors(struct elevatorState* liftState){
    if (time(NULL) - startTime > 3 && liftState->obstruction == false){
        
    }
}