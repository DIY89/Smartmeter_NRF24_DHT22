#include <main.h>

// Allocate the JSON document
//
// Inside the brackets, 200 is the RAM allocated to this document.
// Don't forget to change this value to match your requirement.
// Use https://arduinojson.org/v6/assistant to compute the capacity.

StaticJsonDocument<200> msg;

/*
StaticJsonDocument<300> doc;

#define CE_PIN 9
#define CSN_PIN 10

// Let these addresses be used for the pair
static const uint8_t address[][6] = { "1Node", "2Node" };
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
static const bool radioNumber = 1;  // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
static const bool role = false;

// instantiate an object for the nRF24L01 transceiver
RF24 radio_test(CE_PIN, CSN_PIN);
*/

void setup(){
  // Initialize Serial Connection
  Serial.begin(9600);

  // Initialize DHT22 Sensor
  /*
  init_dht_data();
  init_nrf_data();
  init_sml_data();
  init_battery_data();
*/
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
    serializeJson(msg, radioForArduinoJson); // I get nothing like this : {}
#if defined(DEBUG)
      // Serialisieren und ausgeben
      serializeJson(msg, Serial);
#endif
    delay(2000);

    //cnt++;
  }
  
}
