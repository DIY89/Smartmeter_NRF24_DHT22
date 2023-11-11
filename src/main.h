#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "sml_data.h"
#include "nrf_data.h"
#include "dht_data.h"
#include "battery_data.h"
#include "message.h"

uint32_t SLEEP_TIME = 5000;  // sleep time between reads (seconds * 1000 milliseconds)

#define BAUDRATE 9600

#ifndef DEBUG 
// set DEBUG to "true" to print out debug msg
//#undef DEBUG
#define DEBUG true
#endif 


#endif