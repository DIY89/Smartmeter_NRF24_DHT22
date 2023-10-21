#include <battery_data.h>

void init_battery_data(){
 //Initialize analog input
}

void read_battery_voltage(float battery_voltage){
  battery_voltage = analogRead(ANALOG_PIN);
}
