# Smartmeter_NRF24_DHT22

Reads following sensor data
 - DHT22 Temperature and Humidity
 - SML Smart Meter Power Data
 - Battery voltage


 Telegram structure in JSON format

 message
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
 