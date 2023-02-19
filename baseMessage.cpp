#include "baseMessage.h"

//Constructor        
baseMessage::baseMessage(){
    message_ID = htons(0x00);
    sender_ID = 0x00;
    receiver_ID = 0x00;
    payload_length = htonl(0x00);
    payload = nullptr;
}

//Access Methods
uint16_t baseMessage::get_message_ID() const{
    return ntohs(this->message_ID);
}

uint8_t baseMessage::get_sender_ID() const{
    return this->sender_ID;
}

uint8_t baseMessage::get_receiver_ID() const{
    return this->receiver_ID;
}

uint32_t baseMessage::get_payload_length() const{
    return ntohl(this->payload_length);
}

//Send Message
ustring8_t baseMessage::sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint32_t payload_lengthin, const uint8_t* payloadin)const{
    
    uint32_t payload_length_bytes = nbits_to_nbytes(payload_lengthin);
    //Initialize message
    ustring8_t net_message;
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
    net_message[7] = (uint8_t) payload_lengthnet & 0xFF;
    
    //Store payload in message
    for (uint32_t kk=0; kk<payload_length_bytes; ++kk){
        net_message[8+kk]= (uint8_t) payloadin[kk];
    }

    //Debug Print
    printf("---Base Sending Message---\n");
    uint16_t message_IDout = ntohs(net_message[0] << 8 | net_message[1]);
    printf("Message  ID: %u\n", (unsigned) message_IDout);
    printf("Sender   ID: %u\n", net_message[2]);
    printf("Receiver ID: %u\n", net_message[3]);
    uint32_t payload_lengthout = ntohl(net_message[4] << 24 | net_message[5] << 16 | net_message[6] << 8 | net_message[7]);
    printf("Payload length: %lu\n", (unsigned long) payload_lengthout);
    
    printf("Message: ");
    for (uint32_t kk=8; kk < payload_length_bytes+8; ++kk){
        printf("%c", (uint8_t) net_message[kk]);
    }
    printf("\n");

    return net_message;
};

//Receive Message and Update members
void baseMessage::receiveMessage(const ustring8_t &net_messagein){
    this->message_ID = ntohs(net_messagein[0] << 8 | net_messagein[1]);
    this->sender_ID = net_messagein[2];
    this->receiver_ID = net_messagein[3];
    this->payload_length = ntohl(net_messagein[4] << 24 | net_messagein[5] << 16 | net_messagein[6] << 8 | net_messagein[7]);
    if(payload_length > 0){
        uint32_t payload_length_bytes = nbits_to_nbytes(this->payload_length);
        if(this->payload) {
            realloc(this->payload, payload_length_bytes);
        }else{
            this->payload = (uint8_t*) malloc(payload_length_bytes);
        } 
        const uint8_t* payload_startin = net_messagein.c_str()+8;
        memcpy(this->payload, payload_startin, payload_length_bytes);
    }else{
        if(this->payload) free(this->payload);
        this->payload = nullptr;
    }
    
    //Debug Print
    printf("---Base Received Message---\n");
    printf("Message  ID: %u\n", (unsigned) this->message_ID);
    printf("Sender   ID: %u\n", this->sender_ID );
    printf("Receiver ID: %u\n", this->receiver_ID);
    printf("Payload length: %lu\n", (unsigned long) this->payload_length);
    printf("Received Message: ");
    uint32_t payload_length_bytes2 = nbits_to_nbytes(this->payload_length);
    for (uint32_t kk=0; kk < payload_length_bytes2; ++kk){
        printf("%c", (uint8_t) this->payload[kk]);
    }
    printf("\n");
}

//Destructor 
baseMessage::~baseMessage(){
    if(payload) free(payload);
}

