//
// Created by jaoliveira on 11/2/2020.
//

#ifndef INTERNODECOM_FRAMER_H
#define INTERNODECOM_FRAMER_H

#include <data_link/framitization/Frame.h>
#include <map>

class Framer {

    Framer() = default;
    static Framer _instance;
public:
    static Framer * getInstance(){
        return &_instance;
    }

private:
    std::map<uint16_t, size_t> sendMessagesMissingACK;
    std::map<uint16_t, size_t> receivedMessagesMissingFrames;

public:

    /**
     * This function will return if a data Sequence is required
     * @param payload
     * @param size
     * @return total number of frames required
     */
    size_t numberOfDataSequeceFrames(uint8_t * payload, size_t size);

    /**
     * Will return a array of frames for a the passed payload
     * @param frames Inititialized with the required size, can be obtained with numberOfDataSequeceFrames;
     * @param payload data to send
     * @param size size of the data to send
     * @return MessageID
     */
    uint16_t createDataSequenceFrame(Frame ** frames, uint8_t * payload, size_t size);

    /**
     * Will return a Frame for a single data packet
     * @param Frame
     * @param payload
     * @param size
     * @return MessageID
     */
    uint16_t createDataFrame(Frame * Frame, uint8_t * payload, size_t size);


    /**
     * Will make the required callbacks depending on the frame type;
     * @param frame
     * @return
     */
    void receivedFrame(Frame * frame);

};


#endif //INTERNODECOM_FRAMER_H
