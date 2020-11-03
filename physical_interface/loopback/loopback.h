//
// Created by jaoliveira on 10/27/2020.
//

#ifndef INTERNODECOM_SERIAL_H
#define INTERNODECOM_SERIAL_H

#include <physical_interface/Physical.h>
#include <vector>


class Loopback : public Physical {
public:


    static Loopback * getInstance();

private:

    Loopback();
    static Loopback instance;

    std::vector<uint8_t> tx_buffer;


    bool ph_start() override;
    uint8_t ph_transmit(uint8_t *buffer, size_t size) override;
    uint8_t ph_receive(uint8_t *buffer) override;
    bool ph_shutdown() override;

};


#endif //INTERNODECOM_SERIAL_H
