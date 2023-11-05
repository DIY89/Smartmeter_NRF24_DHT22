#include <battery_data.h>

double battery_voltage = 0;

void init_battery_data(){
 //Initialize analog input
}

void read_battery_voltage(){
  int analog_value = 0;

  analog_value = analogRead(ANALOG_PIN);

  battery_voltage = analog_value * (5.1 / 1020.0);
}
