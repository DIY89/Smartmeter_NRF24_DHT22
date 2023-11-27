#ifndef SML_DATA_H
#define SML_DATA_H

#include <sml.h>
#include <Arduino.h>

#define MAX_BUF_SIZE 400
#define MAX_STR_MANUF 5

extern double T1Wh;
extern double SumWh; 
extern double T1cur;
extern double T1cur_old;

extern char floatBuffer[20];

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