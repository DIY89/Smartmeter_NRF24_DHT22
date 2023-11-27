#undef SIMPLE_RADIO_TEST 
//#define TEST 

//#undef FINAL_TEST
#define FINAL_TEST

#include "main.h"

#if defined(SIMPLE_RADIO_TEST)
#include <SPI.h>
#include <RF24.h>
#include "RF24Network.h"
#include "nRF24L01.h"
#include "printf.h"
#endif


// Allocate the JSON document
//
// Inside the brackets, 200 is the RAM allocated to this document.
// Don't forget to change this value to match your requirement.
// Use https://arduinojson.org/v6/assistant to compute the capacity.
/*
StaticJsonDocument<200> msg;
JsonArray sensors = msg.createNestedArray("sensors");
JsonObject sensor1 = sensors.createNestedObject();
JsonObject sensor2 = sensors.createNestedObject();
JsonObject sensor3 = sensors.createNestedObject();
*/

/*
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
*/

#if defined(FINAL_TEST)
  MessageSender battery(NODE_ID,I_BAT,S_BAT);
  MessageSender temperature(NODE_ID,I_DHT,S_TEMP);
  MessageSender humidity(NODE_ID,I_DHT,S_HUM);
  MessageSender pow_cur(NODE_ID,I_POW,S_POW_CUR);
  MessageSender pow_sum(NODE_ID,I_POW,S_POW_SUM);
#endif

#if defined(SIMPLE_RADIO_TEST)
  RF24 radio(9,10);
  static const uint8_t address[][6] = { "1Node", "2Node" };
#endif

void setup(){
  // Initialize Serial Connection
  Serial.begin(BAUDRATE);
  Serial.println("Init"); 
 
  
#if defined(FINAL_TEST)  
  Serial.println("Radio init");
	radioAdapter.init();
#endif
  init_dht_data();
  init_sml_data();
  init_battery_data();
  // generate_json_msg();

#if defined(SIMPLE_RADIO_TEST)  
  radio.begin();

  radio.setPayloadSize(32);
  radio.setPALevel(RF24_PA_LOW);

  //#radio.setAutoAck(true);
  //radio.enableAckPayload();
  radio.enableDynamicPayloads();

  radio.openWritingPipe(address[1]);  // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  //radio.openReadingPipe(1, address[!radioNumber]);  // using pipe 1

#if defined(DEBUG)
  // Serialisieren und ausgeben
  printf_begin();
  radio.printPrettyDetails();
#endif
#endif
}

void loop(){

  /*
  RF24Adapter radioForArduinoJson(radio_test); // Not sending 
  serializeJson(doc, radioForArduinoJson); // I get nothing like this : {}
  serializeJson(doc, Serial);

  //serializeJson(msg, radioForArduinoJson);

  //char usedBytes[2] = "";
  //char json_data_msg[400];
  //itoa(msg.memoryUsage(),usedBytes,10); // Erhalten Sie die genutzte Länge in Bytes
  //itoa(sizeof(measureJson(msg)),usedBytes,10); // Erhalten Sie die genutzte Länge in Bytes
  //Serial.print("Genutzte Länge (Bytes): ");
  //Serial.println(measureMsgPack(msg));
  

  char c_dht_temperature[10]; 
  char c_dht_humidity[10]; 
  char c_battery_voltage[10]; 
  */

  read_dht_data();

  temperature.store(dht_data.temperature);
  temperature.send();

  humidity.store(dht_data.humidity);
  humidity.send();

#ifdef DEBUG  
  Serial.print("Temperatur: ");
  Serial.print(dht_data.temperature);
  Serial.print(" | Humidity: ");
  Serial.println(dht_data.humidity);
#endif
    
  read_battery_voltage();
  
  if (battery_voltage_old != battery_voltage) {
#ifdef DEBUG      
    Serial.print("Battery voltage: ");
    Serial.println(battery_voltage);
#endif      
    battery.store(battery_voltage);
    battery.send();
  }
#if defined(SIMPLE_RADIO_TEST)
      //char test[6] = "Hallo";
      //char test[6] = {'H','a','l','l','o'};
      
      String msg;
      char test[20];
      /*
      test[0] = 'H';
      test[1] = 'a';
      test[2] = 'l';
      test[3] = 'l';
      test[4] = 'o';
      test[5] = '\0';
      */
     uint8_t node_id = 1;
     uint8_t sensor_id = 1;
     uint8_t sensor_type = 1;
     double val = 25.52;

      // Msg format ( i=1,s=2,d=2,v=25.25	)
      sprintf(test,"i=%d,s=%d,d=%d,v=", node_id, sensor_id, sensor_type);

      String value(val,2);
      Serial.print("MSG: ");
      msg = test + value;
      Serial.println(msg);

      strcpy(test,msg.c_str());

      Serial.println(test);
      
      if(radio.write(&test,sizeof(test))){
        Serial.println("send");
      }
#endif  

  //radioAdapter.send(&data,sizeof(data));	
  /*
  battery.store(battery_voltage);
  if(battery.send()){
    //Serial.println("sending");
  }
  battery_voltage_old = battery_voltage;
  */
  //}
  /*
  convertToCharArray(battery_voltage, c_battery_voltage);
  //Serial.print("Battery Voltage: ");
  //Serial.println(c_battery_voltage);
  sensor2["voltage"] = c_battery_voltage;
  */
  read_sml_data();
   

  if(T1cur != T1cur_old){
#if defined(DEBUG)      
  Serial.print("Current Power: ");
  Serial.println(T1cur);
#endif
  T1cur_old = T1cur;

  pow_sum.store(2000);
  pow_sum.send();
  }

    
    
    
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
    //serializeJson(msg, Serial);
    //Serial.println("loop");
    //Serial.println(json_data_msg);

#endif
    //delay(SLEEP_TIME);
  //}
}



