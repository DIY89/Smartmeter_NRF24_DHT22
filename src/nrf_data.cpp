#include "nrf_data.h"

void init_nrf(){

    // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }
  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  radio.setPayloadSize(sizeof(payload));  // float datatype occupies 4 bytes

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[radioNumber]);  // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[!radioNumber]);  // using pipe 1
}

bool send_data(const void *data, uint8_t data_size){
  unsigned long start_timer = micros();                // start the timer
  bool report = radio.write(data, data_size);  // transmit & save the report
  unsigned long end_timer = micros();                  // end the timer

  if (report) {
    Serial.print(F("Transmission successful! "));  // payload was delivered
    Serial.print(F("Time to transmit = "));
    Serial.print(end_timer - start_timer);  // print the timer result
    Serial.print(F(" us. Sent: "));
    Serial.println(payload);  // print payload sent
    payload += 0.01;          // increment float payload
  } else {
    Serial.println(F("Transmission failed or timed out"));  // payload was not delivered
  }

  // to make this example readable in the serial monitor
  delay(1000);  // slow transmissions down by 1 second
  //If successful
  return report;
}