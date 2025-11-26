#include "pico/stdlib.h"
#include <stdio.h>

typedef enum{
    LOW_TEMPERATURE,
    MEDIUM_TEMPERATURE,
    HIGH_TEMPERATURE
} temperature_state_t;

temperature_state_t state = LOW_TEMPERATURE;
