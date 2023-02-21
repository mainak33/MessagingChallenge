/**
 * @file: baseMessage.cpp
 * @author: Mainak Mitra
 * 
 * @brief baseMessage class members implementation
 */

#include "baseMessage.h"
#include <stdexcept>

//Constructor        
baseMessage::baseMessage(){
    message_ID = htons(0x00);     // Default 0 
    sender_ID = 0x00;             // Default 0 
    receiver_ID = 0x00;           // Default 0 
    payload_length = htonl(0x00); // Default 0
    //NOTE: htons and htonl are not required above but used in case defaults are changed in future
}

//Access Methods
uint16_t baseMessage::get_message_ID() const{
    return ntohs(this->message_ID); //Convert to host system byte ordering before returning
}

uint8_t baseMessage::get_sender_ID() const{
    return this->sender_ID;
}

uint8_t baseMessage::get_receiver_ID() const{
    return this->receiver_ID;
}

uint32_t baseMessage::get_payload_length() const{
    return ntohl(this->payload_length); //Convert to host system byte ordering before returning
}

ustring8_t baseMessage::get_payload() const{
    return this->payload;
};

//Send Message
ustring8_t baseMessage::sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint32_t payload_lengthin, const ustring8_t payloadin)const{
    
    uint32_t payload_length_bytes = nbits_to_nbytes(payload_lengthin);
    
    //Initialize message
    ustring8_t net_message;
    
    //Throw exception if payload length is longer than max_size of payload string
    if (payload_length_bytes+8 > (uint32_t) net_message.max_size()){
        throw std::invalid_argument("Invalid payload length. The payload length cannot be accomodated within the maximum size of message possible.");
        return net_message;
    }

    //Throw exception if payload length is longer than payload
    if (payload_length_bytes > (uint32_t) payloadin.size()){
        throw std::invalid_argument("Invalid payload length. The payload length is longer than the payload provided.");
        return net_message;
    }

    net_message.resize(8+payload_length_bytes);
    
    //Store messageID, senderID, receiver_ID in message
    uint16_t message_IDnet = htons(message_IDin);
    net_message[0] = (uint8_t) ((message_IDnet >> 8) & 0xFF);
    net_message[1] = (uint8_t)  (message_IDnet & 0xFF);
    
    net_message[2] = (uint8_t) sender_IDin;
    net_message[3] = (uint8_t) receiver_IDin;
    
    //Store payload length in message
    uint32_t payload_lengthnet = htonl(payload_lengthin);
    net_message[4] = (uint8_t) (payload_lengthnet >> 24) & 0xFF;
    net_message[5] = (uint8_t) (payload_lengthnet >> 16) & 0xFF;
    net_message[6] = (uint8_t) (payload_lengthnet >> 8) & 0xFF;
    net_message[7] = (uint8_t) (payload_lengthnet & 0xFF);
    
    //Store payload in message
    net_message.replace(8,payload_length_bytes,payloadin);

    return net_message;
};

//Receive Message and Update members (fields)
void baseMessage::receiveMessage(const ustring8_t &net_messagein){
    this->message_ID = net_messagein[0] << 8 | net_messagein[1]; //Store in Network Byte Order
    this->sender_ID = net_messagein[2];
    this->receiver_ID = net_messagein[3];
    this->payload_length = net_messagein[4] << 24 | net_messagein[5] << 16 | net_messagein[6] << 8 | net_messagein[7]; //Store in Network Byte Order
    if(payload_length > 0){
        uint32_t payload_length_bytes = nbits_to_nbytes(this->payload_length);
        this->payload.resize(payload_length_bytes);
        this->payload.replace(0,payload_length_bytes, net_messagein,8,payload_length_bytes);
    }
    
    return;
}
