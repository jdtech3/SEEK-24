#ifndef __BT_H
#define __BT_H


class BT {
    public:
        BT(int rx_pin, int tx_pin);
        void init();
    private:
        int _rx_pin, _tx_pin;
};

#endif  // __BT_H
