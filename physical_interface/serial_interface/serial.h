//
// Created by jaoliveira on 10/27/2020.
//

#ifndef INTERNODECOM_SERIAL_H
#define INTERNODECOM_SERIAL_H

#include <physical_interface/Physical.h>
#include <serial/serial.h>

#define PORT "dev/null"
#define BAUD 9600

class Serial : public Physical {

private:
    serial::Serial _serial;

    bool ph_start() override;
    uint8_t ph_transmit(uint8_t *buffer, size_t size) override;
    uint8_t ph_receive(uint8_t *buffer) override;
    bool ph_shutdown() override;

};


#endif //INTERNODECOM_SERIAL_H
