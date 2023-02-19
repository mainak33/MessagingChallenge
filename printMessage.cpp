/**
 * @file: printMessage.cpp
 * @author: Mainak Mitra
 * 
 * @brief implementation of printing functions 
 */

#include "printMessage.h"

void print_sent_baseMessage(const ustring8_t &net_msgin){
    printf("    --- Sent Message ---\n");
    uint16_t message_IDchk = ntohs(net_msgin[0] << 8 | net_msgin[1]);
    printf("    Message  ID: %u\n", (unsigned) message_IDchk);
    printf("    Sender   ID: %u\n", net_msgin[2]);
    printf("    Receiver ID: %u\n", net_msgin[3]);
    uint32_t payload_lengthchk = ntohl(net_msgin[4] << 24 | net_msgin[5] << 16 | net_msgin[6] << 8 | net_msgin[7]);
    printf("    Payload length: %lu\n", (unsigned long) payload_lengthchk);  
    printf("    Payload: ");
    for (uint32_t kk=8; kk < 8+ceil(payload_lengthchk/8); ++kk){
        printf("%c", (uint8_t) net_msgin[kk]);
    }
    printf("\n");
    return;
}

void print_sent_derivedMessage(const ustring8_t &net_msgin){
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

void print_last_received_baseMesaage(const baseMessage &msg){
    printf("    --- Received Message ---\n");
    printf("    Message  ID: %u\n", (unsigned) msg.get_message_ID());
    printf("    Sender   ID: %u\n", msg.get_sender_ID());
    printf("    Receiver ID: %u\n", msg.get_receiver_ID());
    printf("    Payload length: %lu\n", (unsigned long) msg.get_payload_length());
    printf("    Payload: ");
    ustring8_t payload_received =  msg.get_payload();
    for (uint32_t kk=0; kk < ceil(msg.get_payload_length()/8); ++kk){
        printf("%c", (uint8_t)payload_received[kk]);
    }
    printf("\n");
    return;
}

void print_last_received_derivedMessage_payload(const derivedMessage &msg){
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

void print_last_received_derivedMessage(const derivedMessage &msg){
    print_last_received_baseMesaage(msg);
    print_last_received_derivedMessage_payload(msg);
    return;
}