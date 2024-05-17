/*Servos.c, created by Max Meyers 5/17/24.
I remembered that services are only supposed to be the state machines, so a service for each individual moving part is unnecessary.*/

#include "BOARD.h"
#include "PWM.h"

#define CLOSED_SIGNAL 0
#define OPEN_SIGNAL 1023
#define LEFT_DOOR 0
#define RIGHT_DOOR 1

