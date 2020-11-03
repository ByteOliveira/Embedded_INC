//
// Created by jaoliveira on 10/28/2020.
//

#include <physical_interface/loopback/loopback.h>
#include <vector>
#include <iostream>

extern void ph::received(Physical * physical,uint8_t * buffer, size_t size){
    std::cout<<"data received"<<std::endl;
}

int main(){

    Loopback * serial = (Loopback *) Loopback::getInstance();

    std::vector<uint8_t> data = {1,2,3,4,5,6};

    std::cout<<serial->ph_dataToTransmit()<<std::endl;

    ph::transmit(serial ,data.data(),data.size());

    std::cout<<serial->ph_dataToTransmit()<<std::endl;

    serial->main();

    std::cout<<serial->ph_dataToTransmit()<<std::endl;


    return 0;
}