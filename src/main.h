#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <RF24Network.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <printf.h>
#include "sml_data.h"
#include "nrf_data.h"

// DHT Sensor Config
#define DHTPIN 5
#define DHTTYPE DHT22

// Analog Pin for battery voltage
#define ANALOG_PIN A0

typedef struct{
 float temperature;
 float humidity;
}DHT_DATA;

DHT dht22(DHTPIN,DHTTYPE);
DHT_DATA dht_data; 

float battery_voltage = 0;