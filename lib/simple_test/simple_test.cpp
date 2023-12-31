#include "simple_test.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio_test(CE_PIN, CSN_PIN);

void init_nrf_test_data(void){
  //printf_begin();

    // initialize the transceiver on the SPI bus
  if (!radio_test.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
  }else
    Serial.println(F("radio initialized"));
  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio_test.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit a float
  //radio_test.setPayloadSize(sizeof(payload));  // float datatype occupies 4 bytes
  radio_test.enableDynamicPayloads();

  // set the TX address of the RX node into the TX pipe
  radio_test.openWritingPipe(address[radioNumber]);  // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio_test.openReadingPipe(1, address[!radioNumber]);  // using pipe 1

  radio_test.printPrettyDetails();

  radio_test.stopListening();
}

void send_test_msg(const void *data, uint8_t data_size){
  unsigned long start_timer = micros();                // start the timer
  bool report = radio_test.write(data, data_size);  // transmit & save the report
  unsigned long end_timer = micros();                  // end the timer

  if (report) {
    Serial.print(F("Transmission successful! "));  // payload was delivered
    Serial.print(F("Time to transmit = "));
    Serial.print(end_timer - start_timer);  // print the timer result
    Serial.print(F(" us. Sent: "));
    //Serial.println(payload);  // print payload sent
    //payload += 0.01;          // increment float payload
  } else {
    Serial.println(F("Transmission failed or timed out"));  // payload was not delivered
  }

  // to make this example readable in the serial monitor
  delay(1000);  // slow transmissions down by 1 second
  //If successful
}