#include <main.h>

// Allocate the JSON document
//
// Inside the brackets, 200 is the RAM allocated to this document.
// Don't forget to change this value to match your requirement.
// Use https://arduinojson.org/v6/assistant to compute the capacity.
StaticJsonDocument<200> msg;
JsonArray sensors = msg.createNestedArray("sensors");
JsonObject sensor1 = sensors.createNestedObject();
JsonObject sensor2 = sensors.createNestedObject();
JsonObject sensor3 = sensors.createNestedObject();

void generate_json_msg(){
  // JSON-Array "sensors"
  //JsonArray sensors = msg.createNestedArray("sensors");
  //JsonArray sensors = doc.createNestedArray("sensors");

  // Sensor 1 (DHT22)
  //JsonObject sensor1 = sensors.createNestedObject();
  sensor1["type"] = "dht22";
  sensor1["temperature"] = "18.5"; //dht_data.temperature;
  sensor1["humidity"] = "50.5"; // dht_data.humidity;

  // Sensor 2 (Batterie)
  //JsonObject sensor2 = sensors.createNestedObject();
  sensor2["type"] = "battery";
  sensor2["voltage"] = "3.7"; //battery_voltage;

  // Sensor 3 (Smart Meter)
  //JsonObject sensor3 = sensors.createNestedObject();
  sensor3["type"] = "smartmeter";
  sensor3["current_pow"] = "130"; //T1cur;
}

void setup(){
  // Initialize Serial Connection
  Serial.begin(9600);
  //Serial.println("Init");
  //printf_begin();
  radioForArduinoJson.init();  
 
  init_dht_data();
  init_sml_data();
  init_battery_data();
  generate_json_msg();

  //init_nrf_test_data();
}

void convertToCharArray(double value, char *result){
  int k;
  char aux[10];

  itoa(value*100, aux, 10);
  int n = strlen(aux);
  k = 0;
  for(int i=0;i<n;i++){
    if(i == n-1 - 1){
      result[k++] = '.';
    }
    result[k++] = aux[i];
  }
  result[k++] = '\0';
}

void loop(){
  //int cnt = 0;
  //char msg_str[] = "hallo world";
  //char msg_str[2];
  
  
  //doc["var1"] = 50;
  //doc["var2"] = 500;

  /*
  RF24Adapter radioForArduinoJson(radio_test); // Not sending 
  serializeJson(doc, radioForArduinoJson); // I get nothing like this : {}
  serializeJson(doc, Serial);
  */
  //serializeJson(msg, radioForArduinoJson);

  char usedBytes[2] = "";
  //char json_data_msg[400];
  //itoa(msg.memoryUsage(),usedBytes,10); // Erhalten Sie die genutzte Länge in Bytes
  itoa(sizeof(measureJson(msg)),usedBytes,10); // Erhalten Sie die genutzte Länge in Bytes
  Serial.print("Genutzte Länge (Bytes): ");
  //Serial.println(measureMsgPack(msg));
  
  char c_dht_temperature[10]; 
  char c_dht_humidity[10]; 
  char c_battery_voltage[10]; 

  while(true){
    read_dht_data();
    //Serial.print("Temperatur: ");
    //Serial.print(dht_data.temperature);
    //Serial.print(" | Humidity: ");
    //Serial.println(dht_data.humidity);
    convertToCharArray(dht_data.temperature, c_dht_temperature);
    convertToCharArray(dht_data.humidity, c_dht_humidity);
    sensor1["temperature"] = c_dht_temperature;
    sensor1["humidity"] = c_dht_humidity;

    read_battery_voltage();
    convertToCharArray(battery_voltage, c_battery_voltage);
    //Serial.print("Battery Voltage: ");
    //Serial.println(c_battery_voltage);
    sensor2["voltage"] = c_battery_voltage;
    
    read_sml_data();
    sensor3["current_pow"] = "120"; //T1cur;
    
    /*
    // Send data of DHT22 Sensor, SmartMeter Data and Current Power Voltage
    send_msg(&msg, sizeof(msg));
    
    //itoa(cnt,msg_str,10);

    //Serial.println(msg_str);
    //send_test_msg(&msg_str, sizeof(msg_str));
    // Wait a few seconds between measurements.
    //cnt++;
    */

    // Sends json msg object via radioForArduinoJson (RF24Adapter) object
    //Serial.println("Sending");
    //serializeJson(msg, radioForArduinoJson);
    //serializeJson(msg, json_data_msg,sizeof(json_data_msg));
    //delay(1000);
    //radio.write(&usedBytes, sizeof(usedBytes));

#if defined(DEBUG)
    // Serialisieren und ausgeben
    serializeJson(msg, Serial);
    Serial.println("");
    //Serial.println(json_data_msg);

#endif
    delay(20000);
  }
}


