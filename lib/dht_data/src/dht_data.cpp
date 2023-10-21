#include <dht_data.h>

DHT dht22(DHTPIN,DHTTYPE);
DHT_DATA dht_data; 

void read_dht_data(){
  dht_data.temperature = dht22.readTemperature();
  dht_data.humidity = dht22.readHumidity();
}

void init_dht_data(){
  dht22.begin();
}