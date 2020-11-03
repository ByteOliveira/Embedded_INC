//
// Created by jaoliveira on 10/27/2020.
//

#include "serial.h"

bool Serial::ph_start(){
    _serial = serial::Serial(PORT, BAUD, serial::Timeout::simpleTimeout(1000));

    if(!_serial.isOpen()){
        _serial.open();
    }

    return _serial.isOpen();
}

uint8_t Serial::ph_transmit(uint8_t * buffer, size_t size) {
    size_t sended_size = _serial.write(buffer,size);
    return sended_size;
}

uint8_t Serial::ph_receive(uint8_t *buffer) {
    size_t readed_size = _serial.read(buffer,PHYSICAL_MAX_PACKET_SIZE);
    return readed_size;
}

bool Serial::ph_shutdown() {
    _serial.flushOutput();
    _serial.close();
    return !_serial.isOpen();
}

