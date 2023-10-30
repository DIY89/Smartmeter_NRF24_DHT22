#include <main.h>

// Allocate the JSON document
//
// Inside the brackets, 200 is the RAM allocated to this document.
// Don't forget to change this value to match your requirement.
// Use https://arduinojson.org/v6/assistant to compute the capacity.

StaticJsonDocument<200> msg;

void setup(){
  // Initialize Serial Connection
  Serial.begin(9600);
 
  init_dht_data();
  init_sml_data();
  init_battery_data();

  //init_nrf_test_data();
}


void generate_json_msg(){
  // JSON-Array "sensors"
  JsonArray sensors = msg.createNestedArray("sensors");
  //JsonArray sensors = doc.createNestedArray("sensors");

  // Sensor 1 (DHT22)
  JsonObject sensor1 = sensors.createNestedObject();
  sensor1["type"] = "dht22";
  sensor1["temperature"] = "18.5"; //dht_data.temperature;
  sensor1["humidity"] = "50.5"; // dht_data.humidity;

  // Sensor 2 (Batterie)
  JsonObject sensor2 = sensors.createNestedObject();
  sensor2["type"] = "battery";
  sensor2["voltage"] = "3.7"; //battery_voltage;

  // Sensor 3 (Smart Meter)
  JsonObject sensor3 = sensors.createNestedObject();
  sensor3["type"] = "smartmeter";
  sensor3["current_pow"] = "130"; //T1cur;

#if defined(DEBUG)
  // Serialisieren und ausgeben
  String jsonString;
  serializeJson(msg, jsonString);

  Serial.begin(9600);
  Serial.println(jsonString);
#endif
}


void loop(){
  //int cnt = 0;
  //char msg_str[] = "hallo world";
  //char msg_str[2];
  
  generate_json_msg();
  //doc["var1"] = 50;
  //doc["var2"] = 500;

  /*
  RF24Adapter radioForArduinoJson(radio_test); // Not sending 
  serializeJson(doc, radioForArduinoJson); // I get nothing like this : {}
  serializeJson(doc, Serial);
  */

  while(true){
    
    read_dht_data();
    read_sml_data();
    read_battery_voltage();

    generate_json_msg();
    /*
    // Send data of DHT22 Sensor, SmartMeter Data and Current Power Voltage
    send_msg(&msg, sizeof(msg));
    */
    //itoa(cnt,msg_str,10);

    //Serial.println(msg_str);
    //send_test_msg(&msg_str, sizeof(msg_str));
    // Wait a few seconds between measurements.
    //cnt++;

    // Sends json msg object via radioForArduinoJson (RF24Adapter) object
    serializeJson(msg, radioForArduinoJson); // I get nothing like this : {}
#if defined(DEBUG)
      // Serialisieren und ausgeben
      serializeJson(msg, Serial);
#endif
    delay(2000);
  }
}
