#ifndef __BT_H
#define __BT_H

#include "chassis.hpp"
#include "SoftwareSerial.h"

class BT {
    public:
        BT(int rx_pin, int tx_pin);
        void init();
    private:
        int _rx_pin, _tx_pin;
};

void bt_setup();
void bt_loop();

#endif  // __BT_H
