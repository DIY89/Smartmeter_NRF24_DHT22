# Smartmeter_NRF24_DHT22

Reads following sensor data
 - DHT22 Temperature and Humidity
 - SML Smart Meter Power Data
 - Battery voltage


 //message
 i := NODE_ID
 s := SENSOR_ID
 dt:= DATA_TYPE (sensor_type)
 d := DATA

 //example (NODE_ID: 1; SENSOR_ID:2 (I_DHT); DATA:S_TEMP; DATA:Temperature)
 i=1,s=2,d=2,v=25.25

Telegram structure in JSON format (// old)
 {
  "sensor": {
    "type":"dht22",
    "temperature: "xx.xx",
    "humidity: "xx.xx"
  }
  "sensor":{
   "type": "battery",
   "voltage": xx.xx"
  }
  "sensor":{
   "type": "smartmeter",
   "current_pow": xx.xx"
  }
}
 