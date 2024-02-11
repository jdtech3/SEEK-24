#include <Arduino.h>
#include <SoftwareSerial.h>

#include "bt.hpp"

BT::BT(int rx_pin, int tx_pin) {
    _rx_pin = rx_pin;
    _tx_pin = tx_pin;
}

void BT::init() {
    
}
