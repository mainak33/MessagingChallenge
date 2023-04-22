/**
 * @file: printMessage.cpp
 * @author: Mainak Mitra
 * 
 * @brief implementation of printing functions 
 */

#include <messages/printMessage.h>
#include <messages/messagesVersion.h>
#include <iostream>
#include <string>

//Get the version of the messages library 
std::string messages::get_version(){
    return std::to_string(messages_VERSION_MAJOR) +  "." + std::to_string(messages_VERSION_MINOR);
}

//Print the version of the messages library 
void messages::print_version(){
    std::cout << " The version of the messages library is : " << messages::get_version() << std::endl;
}

void messages::print_sent_baseMessage(const ustring8_t &net_msgin, bool print_long_payload){
    printf("    --- Sent Message ---\n");
    uint16_t message_IDchk = ntohs(net_msgin[0] << 8 | net_msgin[1]);
    printf("    Message  ID: %u\n", (unsigned) message_IDchk);
    printf("    Sender   ID: %u\n", net_msgin[2]);
    printf("    Receiver ID: %u\n", net_msgin[3]);
    uint32_t payload_lengthchk = ntohl(net_msgin[4] << 24 | net_msgin[5] << 16 | net_msgin[6] << 8 | net_msgin[7]);
    printf("    Payload length: %lu\n", (unsigned long) payload_lengthchk);  
    printf("    Payload: ");
    uint32_t print_length = ceil((double)payload_lengthchk/8);
    if (!print_long_payload) print_length = ((print_length < (uint32_t)100) ? print_length : 100);
    for (uint32_t kk=8; kk < 8+print_length; ++kk){
        printf("%c", (uint8_t) net_msgin[kk]);
    }
    if (!print_long_payload && print_length==100 && ceil((double)payload_lengthchk/8) > 100) printf("...");
    printf("\n");
    return;
}

void messages::print_sent_derivedMessage(const ustring8_t &net_msgin){
    print_sent_baseMessage(net_msgin);
    printf("        Payload Details:\n");
    printf("            Lights : %d\n",(unsigned) ((net_msgin[8] & (uint8_t)128) >> 7) );
    printf("            Camera : %d\n",(unsigned) ((net_msgin[8] & (uint8_t)64)  >> 6) );
    printf("            Action : %d\n",(unsigned)  (net_msgin[8] & (uint8_t)63)        );
    printf("            Name   : ");
    for (uint32_t kk=0; kk < 8; ++kk){
        printf("%c", (uint8_t) net_msgin[9+kk]);
    }
    printf("\n");
    return;
}

void messages::print_last_received_baseMesaage(const baseMessage &msg, bool print_long_payload){
    printf("    --- Received Message ---\n");
    printf("    Message  ID: %u\n", (unsigned) msg.get_message_ID());
    printf("    Sender   ID: %u\n", msg.get_sender_ID());
    printf("    Receiver ID: %u\n", msg.get_receiver_ID());
    printf("    Payload length: %lu\n", (unsigned long) msg.get_payload_length());
    printf("    Payload: ");
    ustring8_t payload_received =  msg.get_payload();
    uint32_t print_length = ceil((double)msg.get_payload_length()/8);
    if (!print_long_payload) print_length = ((print_length < (uint32_t)100) ? print_length : 100);
    for (uint32_t kk=0; kk < print_length; ++kk){
        printf("%c", (uint8_t)payload_received[kk]);
    }
    if (!print_long_payload && print_length==100 && ceil((double)msg.get_payload_length()/8) > 100) printf("...");
    printf("\n");
    return;
}

void messages::print_last_received_derivedMessage_payload(const derivedMessage &msg){
    printf("    Payload Details:\n");
    printf("        Lights : %d\n",(unsigned) msg.get_lights());
    printf("        Camera : %d\n",(unsigned) msg.get_camera());
    printf("        Action : %d\n",(unsigned) msg.get_action());
    ustring8_t namechk = msg.get_name();
    printf("        Name   : ");
    for (uint32_t kk=0; kk < 8; ++kk){
        printf("%c", (uint8_t) namechk[kk]);
    }
    printf("\n");
    return;
}

void messages::print_last_received_derivedMessage(const derivedMessage &msg){
    messages::print_last_received_baseMesaage(msg);
    messages::print_last_received_derivedMessage_payload(msg);
    return;
}