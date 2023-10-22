#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <printf.h>
#include <sml_data.h>
#include <nrf_data.h>
#include <dht_data.h>
#include <battery_data.h>

#ifndef DEBUG 
// set DEBUG to "true" to print out debug msg
#undef DEBUG
//#define DEBUG
#endif 

#endif