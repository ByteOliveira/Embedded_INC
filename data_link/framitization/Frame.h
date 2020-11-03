//
// Created by jaoliveira on 10/29/2020.
//

#ifndef INTERNODECOM_FRAME_H
#define INTERNODECOM_FRAME_H

#include <cstdio>
#include <cstdint>

#define PHYSICAL_BUFFER 200
#define MAX_FRAME_SIZE (PHYSICAL_BUFFER-8)
#define HEADER_SIZE (uint8_t) 8

class Frame {

public:

    typedef enum type{
        DATA,
        SEQUENCE,
        DATA_SEQUENCE,
        ACK,
        ACK_SEQUENCE,
        NACK,
        NACK_SEQUENCE,
        INVALID
    } type_t;

    struct __attribute__ ((__packed__)) sequence_s{
        uint16_t total_parts;
    };

    struct __attribute__ ((__packed__)) data_sequence_s {
        uint16_t sequence_index;
        uint8_t payload_size;
        uint8_t payload[MAX_FRAME_SIZE];
    };

    struct __attribute__ ((__packed__)) data_s {
        uint8_t payload_size;
        uint8_t payload[MAX_FRAME_SIZE];
    };

    struct __attribute__ ((__packed__)) ack_sequence_s{
        uint16_t sequence_index;
    };

    static Frame createACK(uint16_t messageID);
    static Frame createSequenceACK(uint16_t messageID,uint16_t part_index);
    static Frame createNACK(uint16_t messageID);
    static Frame createSequenceNACK(uint16_t messageID,uint16_t part_index);
    static Frame createStartSequence(uint16_t number_of_parts, uint16_t * messageID);
    static Frame createSequenceFrame(uint16_t messageID, uint16_t part_index, uint8_t * buffer, uint8_t size);
    static Frame createSingleMessage(uint8_t * buffer, uint8_t size, uint16_t * messageID);

    /**
     * Will create a Frame with the header information only, size will be the consummed size;
     * @return new Frame only with the header
     */
    static Frame createFromReceivedHeader(uint8_t * buffer, size_t * size);
    /**
     * Return the header size;
     * @return header size;
     */
    static const uint8_t getHeaderSize();

    /**
     * Will send how much is missing to read at each time if return 0 means packet is completed
     * @return
     */
    size_t nextReceiveSize();

    /**
     * add received Payload data to the frame
     * @param buffer
     * @param size
     * @return used bytes
     */
    size_t addReceivedData(uint8_t * buffer, uint8_t size);



private:

    Frame();

    union payload_u{
        data_s data;
        sequence_s sequence;
        data_sequence_s data_sequence;
        ack_sequence_s ack_sequence;
    };

    struct __attribute__ ((__packed__)) header_s  {
        uint16_t channel;
        type_t type;
        uint16_t message_id;
    };

    static const uint8_t headerSize = HEADER_SIZE;

    uint16_t missingReceive;

    /**
     * HEADER
     */
    header_s header;
    /**
     * PAYLOAD
     */
    payload_u payload;
    /**
     * CONTROL
     */
    uint16_t crc;

    uint16_t generateMessageID();


};


#endif //INTERNODECOM_FRAME_H
