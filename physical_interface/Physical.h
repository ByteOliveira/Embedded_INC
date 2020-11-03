//
// Created by jaoliveira on 10/26/2020.
//

#ifndef INTERNODECOM_PHYSICAL_H
#define INTERNODECOM_PHYSICAL_H


#include <cstdint>
#include <list>

#define PHYSICAL_MAX_PACKET_SIZE 200

class Physical {

    static Physical instance;

    std::list<uint8_t> ringBuffer; //change to proper ringbuffer
    uint8_t rx_buffer[PHYSICAL_MAX_PACKET_SIZE]{0};

protected:
    Physical() = default;

public:


    static Physical * getInstance();
    /**
     * @brief logic to start the physical medium
     * @return true if was started
     */
    virtual bool start();
    /**
     * @brief logic to stop the physical medium
     * @return true if was stopped
     */
    virtual bool shutdown();
    /**
     * @brief used to add data to the send queue
     * @param buffer
     * @param size
     */
    virtual void transmit(uint8_t * buffer, size_t size);
    /**
     * @brief function to run the cycle tasks of the physical medium
     */
    virtual void main();

private:
    /**
     * @brief transmittion logic function
     */
    virtual void transmit();
    /**
     * @brief receiving logic funtion
     */
    virtual void receive();


public:
    /**
     * @brief physical medium transmittion
     * @param buffer
     * @param size
     * @return number of bytes transmitted
     */
    virtual uint8_t ph_transmit(uint8_t * buffer, size_t size);
    /**
     * @brief physical medium receiving
     * @param buffer
     * @return return number of bytes to received
     */
    virtual uint8_t ph_receive(uint8_t * buffer);
    /**
     * @brief starts to physical medium
     * @return
     */
    virtual bool ph_start();
    /**
     * @brief stops to physical medium
     * @return
     */
    virtual bool ph_shutdown();
    /**
     * @brief returns if the physical medium still has data to transmit
     * @return
     */
    virtual bool ph_dataToTransmit();
    /**
     * @brief return if there are
     * @return
     */
    virtual bool ph_dataToReceive();


};

/**
 * @brief physical interface external usage
 */
namespace ph {

    /**
     * @brief function to be implemented by the clients
     * @param buffer
     * @param size
     */
    extern void received(Physical * Physical,uint8_t * buffer, size_t size);
    /**
     * @brief function to add data to send queue
     * @param buffer
     * @param size
     */
    extern void transmit(Physical * Physical,uint8_t * buffer, size_t size);
}


#endif //INTERNODECOM_PHYSICAL_H
