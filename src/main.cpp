#include <main.h>

// Allocate the JSON document
//
// Inside the brackets, 200 is the RAM allocated to this document.
// Don't forget to change this value to match your requirement.
// Use https://arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<200> msg;

void init_smart_meter(){
  // Initialize Serial Connection
  Serial.begin(9600);

  // Initialize DHT22 Sensor
  init_dht_data();
  init_nrf_data();
  init_sml_data();
  init_battery_data();

}

void generate_json_msg(){
  msg["type"] = "DHT22";
  msg["temperature"] = dht_data.temperature;
  msg["humidity"] = dht_data.humidity;

  msg["type"] = "Voltage";
  msg["voltage"] = battery_voltage;

  msg["type"] = "Smartmeter";
  //msg["current_pow"] = current_pow;
}

int main(){
  init_smart_meter();

  while(true){
    read_dht_data();
    read_sml_data();
    read_battery_voltage();

    generate_json_msg();

    // Send data of DHT22 Sensor, SmartMeter Data and Current Power Voltage
    send_msg(&msg, sizeof(msg));

    // Wait a few seconds between measurements.
    delay(2000);
  }
}