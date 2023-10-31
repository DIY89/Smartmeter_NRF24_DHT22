#include "nrf_data.h"

#define DEBUG

// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);
RF24Adapter radioForArduinoJson(radio);

// RF24Adapter provides sending msg object byte by byte
RF24Adapter::RF24Adapter(RF24 &radio) : _radio(&radio){}

void RF24Adapter::init(){
// initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }
  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.setAutoAck(true);

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[radioNumber]);  // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[!radioNumber]);  // using pipe 1

#if defined(DEBUG)
  // Serialisieren und ausgeben
  printf_begin();
  //radio.printPrettyDetails();
#endif
}

int RF24Adapter::read() {
  char buf[1];
  _radio->read(buf, 1);
  return buf[0];
}

size_t RF24Adapter::readBytes(char *buffer, size_t length) {
  _radio->read(buffer, static_cast<uint8_t>(length));
  return length;
}

size_t RF24Adapter::write(uint8_t c) {
  return _radio->write(&c, 1) ? 1 : 0;
}

size_t RF24Adapter::write(const uint8_t *buffer, size_t length) {
  return _radio->write(buffer, static_cast<uint8_t>(length)) ? length : 0;
} 
