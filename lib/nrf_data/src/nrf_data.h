#ifndef NRF_DATA_H
#define NRF_DATA_H

#include <RF24.h>
#include <RF24Network.h>
#include <nRF24L01.h>

#define CE_PIN 7
#define CSN_PIN 8

// Let these addresses be used for the pair
static const uint8_t address[][6] = { "1Node", "2Node" };
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
static const bool radioNumber = 1;  // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
static const bool role = false;  // true = TX role, false = RX role

// For this example, we'll be using a payload containing
// a single float number that will be incremented
// on every successful transmission
static float payload = 0.0;

void init_nrf_data(void);
bool send_msg(const void* buf,uint8_t len);

#endif