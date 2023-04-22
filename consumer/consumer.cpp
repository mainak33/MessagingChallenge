#include <messages/printMessage.h>
#include <iostream>

int main(){

    //Example use of classes
    //NOTE: negative numbers may be implicitly converted to uint types. It is upto the API user to ensure that correct arguments are entered
    std::cout << "--- Example usage of baseMessage Class ---"  << std::endl;
    baseMessage msga,msgb;
    uint16_t message_ID        = (uint16_t) 300; // Must be in range [0 , 2^16-1= 65535]. Otherwise implicit conversion may happen
    uint8_t ID_a               = (uint8_t) 44;   // Must be in range [0 , 2^8-1= 63]. Otherwise implicit conversion may happen
    uint8_t ID_b               = (uint8_t) 6;    // Must be in range [0 , 2^8-1= 63]. Otherwise implicit conversion may happen
    uint32_t payloada2b_length = (uint32_t)40;   // Must be 32 bit unsigned integer.
    ustring8_t payload_a2b = ustring8_t((uint8_t *)"abcdefg"); // Number of characters in payload must be longer than ceil(payloada2b_length/8). Any characters after this are ignored 
    //(eg. Here only first 40 bits = 8 bytes of input payload "abcde" will be sent)

    ustring8_t net_msg_a2b = msga.sendMessage(message_ID, ID_a, ID_b, payloada2b_length, payload_a2b);//Generate message to be sent (Simulate a sending b a message)
    print_sent_baseMessage(net_msg_a2b);  //Debug print
    msgb.receiveMessage(net_msg_a2b);     //b receives message and populates its field accordingly (Simulate b receiving the message)
    print_last_received_baseMesaage(msgb);//Debug print
    std::cout << std::endl;
    
    std::cout << "--- Example usage of derivedMessage Class ---"  << std::endl;
    derivedMessage msgc,msgd;
    message_ID          = (uint16_t) 65535;// Must be in range [0 , 2^16-1= 65535]. Otherwise implicit conversion may happen
    uint8_t ID_c        = (uint8_t) 23; // Must be in range [0 , 2^8-1= 63]. Otherwise implicit conversion may happen
    uint8_t ID_d        = (uint8_t) 255;// Must be in range [0 , 2^8-1= 63]. Otherwise implicit conversion may happen
    uint8_t lights_c2d  = (uint8_t) 1;  // Must be 0 or 1 after conversion to uint8_t. exception is thrown
    uint8_t camera_c2d  = (uint8_t) 0;  // Must be 0 or 1 after conversion to uint8_t. Otherwise exception is thrown
    uint8_t action_c2d  = (uint8_t) 63; // Must be in range [0 , 2^6-1= 63] fter conversion to uint8_t. Otherwise exception is thrown
    ustring8_t name_c2d = ustring8_t((uint8_t *)"abcdefgh"); // Name must be exacly 8 characters (64 bytes) in length. Otherwise exception is thrown
   
    ustring8_t net_msg_c2d = msgc.sendMessage(message_ID, ID_c, ID_d,lights_c2d,camera_c2d,action_c2d,name_c2d);//Generate message to be sent (Simulate c sending d a message)
    print_sent_derivedMessage(net_msg_c2d);  //Debug print
    msgd.receiveMessage(net_msg_c2d);        //c receives message and populates its fields accordingly (Simulate c receiving the message)
    print_last_received_derivedMessage(msgd);//Debug print
    std::cout << std::endl;

    return 0;
}