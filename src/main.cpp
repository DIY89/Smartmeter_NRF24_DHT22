#include <main.h>


void init_smart_meter(){
  // Initialize Serial Connection
  Serial.begin(9600);

  // Initialize DHT22 Sensor
  init_dht_data();
  init_nrf_data();
  init_sml_data();
  init_battery_data();

}

void send_data(){

}

int main(){
  init_smart_meter();

  while(true){
    read_dht_data();
    read_sml_data();
    //read_battery_voltage();

    // Send data of DHT22 Sensor, SmartMeter Data and Current Power Voltage
    send_data();

    // Wait a few seconds between measurements.
    delay(2000);
  }
}