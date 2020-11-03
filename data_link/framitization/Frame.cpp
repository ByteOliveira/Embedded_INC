//
// Created by jaoliveira on 10/29/2020.
//

#include <cmath>
#include <cstring>
#include <limits>
#include "Frame.h"



static bool messagesIDs[std::numeric_limits<uint16_t>::max()]={};

Frame::Frame() {
    this->header.type = INVALID;
}

uint16_t Frame::generateMessageID() {
    //TODO: change to a correct UID generator - problem needs to be multi plataform
    for(uint32_t i=0;i<std::numeric_limits<uint16_t>::max();i++){
        if(!messagesIDs[i]){
            return i;
        }
    }
}

Frame Frame::createACK(uint16_t messageID) {
    Frame frame = Frame();
    frame.header.message_id = messageID;
    frame.header.type = ACK;
    return frame;
}

Frame Frame::createSequenceACK(uint16_t messageID, uint16_t part_index) {
    Frame frame = Frame();
    frame.header.message_id = messageID;
    frame.header.type = ACK_SEQUENCE;
    ack_sequence_s ackSeq = {};
    ackSeq.sequence_index = part_index;
    frame.payload.ack_sequence = ackSeq;
    return frame;
}

Frame Frame::createNACK(uint16_t messageID) {
    Frame frame = Frame();
    frame.header.message_id = messageID;
    frame.header.type = NACK;
    return frame;
}

Frame Frame::createSequenceNACK(uint16_t messageID, uint16_t part_index) {
    Frame frame = Frame();
    frame.header.message_id = messageID;
    frame.header.type = NACK_SEQUENCE;
    ack_sequence_s ackSeq = {};
    ackSeq.sequence_index = part_index;
    frame.payload.ack_sequence = ackSeq;
    return frame;
}

Frame Frame::createStartSequence(uint16_t number_of_parts, uint16_t *messageID) {
    Frame frame = Frame();
    frame.header.message_id = frame.generateMessageID();
    messageID = &frame.header.message_id;
    sequence_s seq = {};
    seq.total_parts = number_of_parts;
    frame.header.type= SEQUENCE;
    return frame;
}

Frame Frame::createSequenceFrame(uint16_t messageID, uint16_t part_index, uint8_t *buffer, uint8_t size) {
    Frame frame = Frame();
    if(size >= MAX_FRAME_SIZE){
        return frame;
    }
    frame.header.message_id = messageID;
    data_sequence_s dataSeq = {};
    dataSeq.sequence_index = part_index;
    memcpy(dataSeq.payload,buffer,size);
    dataSeq.payload_size=size;
    frame.payload.data_sequence=dataSeq;
    frame.header.type=DATA_SEQUENCE;
    return frame;
}

Frame Frame::createSingleMessage(uint8_t *buffer, uint8_t size, uint16_t * messageID) {
    Frame frame = Frame();
    if(size >= MAX_FRAME_SIZE){
        return frame;
    }
    frame.header.message_id = frame.generateMessageID();
    messageID = &frame.header.message_id;
    data_s data = {};
    memcpy(data.payload,buffer,size);
    data.payload_size = size;
    frame.header.type= DATA;
    return frame;
}

Frame Frame::createFromReceivedHeader(uint8_t *buffer, size_t *size) {
    Frame frame = Frame();
    frame.missingReceive=0;

    memcpy(&frame.header, buffer, HEADER_SIZE);
    *size = headerSize;

    switch (frame.header.type) {
        case DATA:
            frame.missingReceive = 1;
        case SEQUENCE:
            frame.missingReceive = 2;
        case DATA_SEQUENCE:
            frame.missingReceive = 3;
        case ACK:
            frame.missingReceive = 0;
        case ACK_SEQUENCE:
            frame.missingReceive = 2;
        case NACK:
            frame.missingReceive = 0;
        case NACK_SEQUENCE:
            frame.missingReceive = 2;
        case INVALID:
            frame.missingReceive = 0;
    }

    return frame;
}

const uint8_t Frame::getHeaderSize() {
    return HEADER_SIZE;
}

size_t Frame::nextReceiveSize() {
    return missingReceive;
}

size_t Frame::addReceivedData(uint8_t *buffer, uint8_t size) {
    static bool initialData = true;
    if (size == missingReceive && initialData){
        memcpy(&payload,buffer,size);
        initialData= false;
        if(header.type==DATA){
            missingReceive=payload.data.payload_size;
        } else if(header.type==DATA_SEQUENCE){
            missingReceive=payload.data_sequence.payload_size;
        }
    } else if(!initialData && size == missingReceive){
        if(header.type==DATA){
            memcpy(&payload.data.payload,buffer,size);
        } else if(header.type==DATA_SEQUENCE){
            memcpy(&payload.data_sequence.payload,buffer,size);
        }
    } else {
        return 0;
    }
    return size;
}
