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
  // JSON-Array "sensors"
  JsonArray sensors = msg.createNestedArray("sensors");

  // Sensor 1 (DHT22)
  JsonObject sensor1 = sensors.createNestedObject();
  sensor1["type"] = "dht22";
  sensor1["temperature"] = 22.45;
  sensor1["humidity"] = 50.2;

  // Sensor 2 (Batterie)
  JsonObject sensor2 = sensors.createNestedObject();
  sensor2["type"] = "battery";
  sensor2["voltage"] = 3.7;

  // Sensor 3 (Smart Meter)
  JsonObject sensor3 = sensors.createNestedObject();
  sensor3["type"] = "smartmeter";
  sensor3["current_pow"] = 120.5;

#if defined(DEBUG)
  // Serialisieren und ausgeben
  String jsonString;
  serializeJson(msg, jsonString);

  Serial.begin(9600);
  Serial.println(jsonString);
#endif
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