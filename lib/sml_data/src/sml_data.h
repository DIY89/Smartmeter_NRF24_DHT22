#ifndef SML_DATA_H
#define SML_DATA_H

#include <sml.h>
#include <Arduino.h>

#define MAX_BUF_SIZE 400
#define MAX_STR_MANUF 5
// Continuously loops through a static message from RAM and outputs information
// to serial

extern double T1Wh;
extern double SumWh; 
extern double T1cur;

typedef struct {
  const unsigned char OBIS[6];
  void (*Handler)();
} OBISHandler;

void PowerT1();
void PowerSum();
void PowerCur();
void Manufacturer();
void init_sml_data();
void read_sml_data();

#endif