/**
 * @file: derivedMessage.cpp
 * @author: Mainak Mitra
 * 
 * @brief derivedMessage class members implementation
 */

#include "derivedMessage.h"
#include <stdexcept>

//Constructor
derivedMessage::derivedMessage():baseMessage(){ 
    this->lights_camera_action = 0x00; // Default 0 (indicates no message received yet)
}

//Access Methods
uint1_t derivedMessage::get_lights() const{
    return (lights_camera_action & (uint8_t)128) >>7;
}

uint1_t derivedMessage::get_camera() const{
    return (lights_camera_action &  (uint8_t) 64) >> 6;
}

uint8_t derivedMessage::get_action() const{
    return (lights_camera_action & (uint8_t) 63);
}

ustring8_t derivedMessage::get_name() const{
    return this->name;
};

//Send Message
ustring8_t derivedMessage::sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint8_t &lightsin, const uint8_t  &camerain, const uint8_t &actionin, const ustring8_t namein) const{
    
    ustring8_t payloadin(9,' '); // Payload of message to be sent
    
    //Throw exceptions if lightsin, camerain or actionin are of the incorrect size
    if (lightsin > (uint8_t) 1){
        throw std::invalid_argument("The lights to be sent in the message must be of size 1 byte (0 or 1 in decimal)");
    }
    
    if (camerain > (uint8_t) 1){
        throw std::invalid_argument("The camera to be sent in the message must be of size 1 byte (0 or 1 in decimal)");
    }

    if (actionin > (uint8_t) 63){
        throw std::invalid_argument("The action to be sent in the message must be of size 6 bytes or less (less than 63 in decimal)");
    }

    // Construct payload to be sent
    payloadin[0] = lightsin << 7 | camerain << 6 | (actionin  &  (uint8_t) 63);
    payloadin.replace(1,8,namein);

    //Debug Print
    // printf("---Sending Derived Message---\n");
    // printf("Lights %d\n",(unsigned) lightsin);
    // printf("Camera %d\n",(unsigned) camerain);
    // printf("Action %d\n",(unsigned) actionin);
    // printf("LCA : %u\n", (unsigned int) payloadin[0]);

    //Use baseMessage class to construct messaage with payload
    return baseMessage::sendMessage(message_IDin,sender_IDin,receiver_IDin,(uint32_t)72,payloadin);
    
}

//Receive Message and Update members (fields)
void derivedMessage::receiveMessage(ustring8_t net_messagein){
    
    //Throw exception if message length is not  17 bytes (136 bits)
    if (net_messagein.size() != (uint8_t) 17){
        throw std::invalid_argument("Invalid message. A valid derived message must be 136 bits (17 bytes) in length");
    }

    //Use baseMessage class to receive messaage with payload
    baseMessage::receiveMessage(net_messagein);
    
    //Throw exception if payload length is not 72 bits (9 bytes)
    if (this->payload_length != ntohl((uint32_t) 72)){
        throw std::invalid_argument("Invalid payload. A valid payload of a derived message must be 72 bits (9 bytes) in length");
    }

    //Store payload fields in members
    this->lights_camera_action = this->payload[0];
    this->name.replace(0,8,this->payload,1,8);

    //Debug Print
    // printf("---received Derived Message---\n");
    // printf("LCA    : %u\n", (unsigned) this->lights_camera_action);
    // printf("Lights : %d\n",(unsigned) this->get_lights());
    // printf("Camera : %d\n",(unsigned) this->get_camera());
    // printf("Action : %d\n",(unsigned) this->get_action());
    // ustring8_t nameout = this->get_name();
    // printf("Name: ");
    // for (uint32_t kk=0; kk < 8; ++kk){
    //     printf("%c", (uint8_t) nameout[kk]);
    // }
    // printf("\n");
    
    return;
}  


