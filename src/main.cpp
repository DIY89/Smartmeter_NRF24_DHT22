#include <main.h>



void init_smart_meter(){
  // Initialize Serial Connection
  Serial.begin(9600);

  // Initialize DHT22 Sensor
  dht22.begin();

  init_nrf();
}

void read_dht_data(){
  dht_data.temperature = dht22.readTemperature();
  dht_data.humidity = dht22.readHumidity();
}

void read_batterie_voltage(){
  battery_voltage = analogRead(ANALOG_PIN);
}

// Send data of DHT22 Sensor, SmartMeter Data and Current Power Voltage
void send_data(){

}

int main(){
  init_smart_meter();

  while(true){
    read_dht_data();
    read_sml_data();
    read_batterie_voltage();

    send_data();

    // Wait a few seconds between measurements.
    delay(2000);
  }
}