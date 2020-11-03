//
// Created by jaoliveira on 10/27/2020.
//

#include <physical_interface/loopback/loopback.h>

Loopback Loopback::instance = Loopback();

bool Loopback::ph_start(){
    return true;
}

uint8_t Loopback::ph_transmit(uint8_t * buffer, size_t size) {
    for(size_t i=0;i<size;i++){
        tx_buffer.insert(tx_buffer.end(),buffer[i]);
    }
}

uint8_t Loopback::ph_receive(uint8_t *buffer) {
    buffer = tx_buffer.data();
    return tx_buffer.size();
}

bool Loopback::ph_shutdown() {
    return true;
}

Loopback *Loopback::getInstance() {
    return &Loopback::instance;
}

Loopback::Loopback() {

}

