//
// Created by jaoliveira on 10/26/2020.
//

#include <memory.h>
#include <vector>
#include <physical_interface/Physical.h>

Physical Physical::instance = Physical();

Physical * Physical::getInstance() {
    return &Physical::instance;
}

bool Physical::start() {
    return ph_start();
}

void Physical::transmit(uint8_t *buffer, size_t size) {
    for(int i = 0; i< size ; i++){
        ringBuffer.push_back(buffer[i]);
    }
}

void Physical::transmit() {
    uint8_t buffer[PHYSICAL_MAX_PACKET_SIZE];
    size_t transmition_size = std::min((size_t)PHYSICAL_MAX_PACKET_SIZE,ringBuffer.size());

    for(size_t i = 0;i<transmition_size;i++){
        buffer[i] = ringBuffer.front()+i;
    }

    size_t transmited = ph_transmit(buffer, transmition_size);
    if (transmited>0){
        for(size_t i = 0;i<transmited;i++){
            ringBuffer.pop_front();
        }
    } else{
        //some DEBUG message
    }
}

void Physical::receive() {
    size_t receive_size = ph_receive(rx_buffer);
    if(receive_size>0){
        ph::received(this,rx_buffer, receive_size);
    }
}

bool Physical::shutdown() {
    return ph_shutdown();
}

bool Physical::ph_dataToTransmit() {
    return !ringBuffer.empty();
}

bool Physical::ph_dataToReceive() {
    return true;
}

uint8_t Physical::ph_transmit(uint8_t *buffer, size_t size) {
    return 0;
}

uint8_t Physical::ph_receive(uint8_t *buffer) {
    return 0;
}

bool Physical::ph_start() {
    return true;
}

bool Physical::ph_shutdown() {
    return true;
}

void ph::transmit(Physical * physical, uint8_t *buffer, size_t size) {
    physical->transmit(buffer,size);
}

void Physical::main() {
    if(ph_dataToTransmit()){
        transmit();
    }
    if(ph_dataToReceive()){
        receive();
    }
}

