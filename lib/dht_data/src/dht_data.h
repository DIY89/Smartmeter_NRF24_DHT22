#ifndef DHT_DATA_H
#define DHT_DATA_H

#include <Adafruit_Sensor.h>
#include <DHT.h>

// DHT Sensor Config
#define DHTPIN 5
#define DHTTYPE DHT22

typedef struct{
 float temperature;
 float humidity;
}DHT_DATA;

extern DHT_DATA dht_data; 

void init_dht_data();
void read_dht_data();

#endif