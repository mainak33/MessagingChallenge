#include "derivedMessage.h"

 //Constructor Class (Field Initialization) 
derivedMessage::derivedMessage(){
    baseMessage();
    this->lights_camera_action = 0x00;
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
    if (this->payload) return ustring8_t((uint8_t*) this->name,8);
    else return ustring8_t((uint8_t*) "        ",8);
};
//Send Message
ustring8_t derivedMessage::sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint1_t &lightsin, const uint1_t  &camerain, const uint8_t &actionin, const uint8_t* namein) const{
    
    uint8_t payloadin[9];

    if (actionin > (uint8_t) 63){
        //TO DO: Warning Message since Action must be 6 bits or less ()
    }

    payloadin[0] = lightsin << 7 | camerain << 6 | (actionin  &  (uint8_t) 63);
    memcpy(payloadin+1,namein,8);
    
    printf("---Sending Derived Message---\n");
    printf("Lights %d\n",(unsigned) lightsin);
    printf("Camera %d\n",(unsigned) camerain);
    printf("Action %d\n",(unsigned) actionin);
    printf("LCA : %u\n", (unsigned int) payloadin[0]);

    return baseMessage::sendMessage(message_IDin,sender_IDin,receiver_IDin,72,payloadin);
    
}

//Receive Message
void derivedMessage::receiveMessage(ustring8_t net_messagein){
    baseMessage::receiveMessage(net_messagein);
    this->lights_camera_action = this->payload[0];
    this->name = this->payload+1;

    printf("LCA    : %u\n", (unsigned) this->lights_camera_action);
    printf("Lights : %d\n",(unsigned) this->get_lights());
    printf("Camera : %d\n",(unsigned) this->get_camera());
    printf("Action : %d\n",(unsigned) this->get_action());
    ustring8_t nameout = this->get_name();
    printf("Name: ");
    for (uint32_t kk=0; kk < 8; ++kk){
        printf("%c", (uint8_t) nameout[kk]);
    }
    printf("\n");
}  


