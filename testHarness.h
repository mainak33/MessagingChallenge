/**
 * @file: testHarness.h
 * @author: Mainak Mitra
 * 
 * @brief testHarness class used for testing baseMessage and derivedMessage
 */

#include "derivedMessage.h"
#include <assert.h>
#include <cmath>
//# include <iostream>


class testDefine{
    public:
        enum E_Error{
            none           = 0, 
            message_ID     = 1,
            sender_ID      = 2, 
            receiver_ID    = 3,
            payload_length = 4,
            payload        = 5,  
            lights         = 6, 
            camera         = 7, 
            action         = 8, 
            name           = 9 
       };
    private:
       baseMessage send_msg;
       baseMessage recv_msg;
       testDefine::E_Error error;
    public:
        
        bool degug_flag;

        explicit testDefine(baseMessage &send_msgin,baseMessage &recv_msgin, bool degug_flagin = false){
            this->send_msg = std::move(send_msgin);
            this->recv_msg = std::move(recv_msgin);
            this->degug_flag = degug_flagin;
            this->error = testDefine::E_Error::none;
        };
        
        
        // testDefine::E_Error test_generic_message(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint32_t payload_lengthin, const ustring8_t payloadin,
        // const uint16_t message_IDout, const uint32_t payload_lengthout, const ustring8_t payloadout){
        //     this->recv_msg.receiveMessage(this->send_msg.sendMessage(message_IDin, sender_IDin, receiver_IDin, payload_lengthin, payloadin));

        // };

        void print_sent_baseMessage(const ustring8_t &net_message){
            printf("--- Sent Message---\n");
            uint16_t message_IDout = ntohs(net_message[0] << 8 | net_message[1]);
            printf("Message  ID: %u\n", (unsigned) message_IDout);
            printf("Sender   ID: %u\n", net_message[2]);
            printf("Receiver ID: %u\n", net_message[3]);
            uint32_t payload_lengthout = ntohl(net_message[4] << 24 | net_message[5] << 16 | net_message[6] << 8 | net_message[7]);
            printf("Payload length: %lu\n", (unsigned long) payload_lengthout);  
            printf("Payload: ");
            for (uint32_t kk=8; kk < 8+ceil(payload_lengthout/8); ++kk){
                printf("%c", (uint8_t) net_message[kk]);
            }
            printf("\n");
            return;
        };

        void print_sent_derivedMessage(const ustring8_t &net_message){
            print_sent_baseMessage(net_message);
            printf("Payload Details:\n");
            printf("    LCA    : %u\n", (unsigned int) net_message[9]);
            printf("    Lights : %d\n",(unsigned) ((net_message[9] & (uint8_t)128) >> 7) );
            printf("    Camera : %d\n",(unsigned) ((net_message[9] & (uint8_t)64)  >> 6) );
            printf("    Action : %d\n",(unsigned)  (net_message[9] & (uint8_t)63)        );
            printf("    Name : ");
            for (uint32_t kk=0; kk < 8; ++kk){
                printf("%c", (uint8_t) net_message[10+kk]);
            }
            printf("\n");
            return;
        }


        void print_last_received_baseMesaage(const baseMessage &msg){
            printf("--- Received Message---\n");
            printf("Message  ID: %u\n", (unsigned) msg.get_message_ID());
            printf("Sender   ID: %u\n", msg.get_sender_ID());
            printf("Receiver ID: %u\n", msg.get_receiver_ID());
            printf("Payload length: %lu\n", (unsigned long) msg.get_payload_length());
            printf("Payload: ");
            ustring8_t payload_received =  msg.get_payload();
            for (uint32_t kk=0; kk < ceil(msg.get_payload_length()/8); ++kk){
                printf("%c", (uint8_t)payload_received[kk]);
            }
            printf("\n");
            return;
        };

        void print_last_received_derivedMessage_payload(const derivedMessage &msg){
            printf("Payload Details:\n");
            printf("Lights : %d\n",(unsigned) msg.get_lights());
            printf("Camera : %d\n",(unsigned) msg.get_camera());
            printf("Action : %d\n",(unsigned) msg.get_action());
            ustring8_t nameout = msg.get_name();
            printf("Name: ");
            for (uint32_t kk=0; kk < 8; ++kk){
                printf("%c", (uint8_t) nameout[kk]);
            }
            printf("\n");
            return;
        };

        testDefine::E_Error check_last_received_baseMesaage(const baseMessage &msg, const uint16_t &message_IDout, const uint8_t &sender_IDout, const uint8_t &receiver_IDout, const uint32_t payload_lengthout, const ustring8_t payloadout){
            if (msg.get_message_ID()      != message_IDout     ) return this->error = testDefine::E_Error::message_ID ;
            if (msg.get_sender_ID()       != sender_IDout      ) return this->error = testDefine::E_Error::sender_ID  ;
            if (msg.get_receiver_ID()     != receiver_IDout    ) return this->error = testDefine::E_Error::receiver_ID;
            if (msg.get_payload_length()  != payload_lengthout ) return this->error = testDefine::E_Error::payload_length;
            if (msg.get_payload().compare(payloadout) != 0     ) return this->error = testDefine::E_Error::payload;
            if (this->degug_flag ) this->print_last_received_baseMesaage(msg);
            return this->error;;
        };

        testDefine::E_Error check_last_received_derivedMesaage(const derivedMessage &msg, const uint16_t &message_IDout, const uint8_t &sender_IDout, const uint8_t &receiver_IDout, const ustring8_t payloadout,  const uint8_t &lightsout, const uint8_t  &cameraout, const uint8_t &actionout, const ustring8_t nameout){
            this->error = check_last_received_baseMesaage(msg, message_IDout, sender_IDout, receiver_IDout, 72, payloadout);
            
            if (this->error != testDefine::E_Error::none) return this->error;
            if (msg.get_lights()  != lightsout       ) return this->error = testDefine::E_Error::lights;
            if (msg.get_camera()  != cameraout       ) return this->error = testDefine::E_Error::camera;
            if (msg.get_action()  != actionout       ) return this->error = testDefine::E_Error::action;
            if (msg.get_name().compare(nameout) != 0 ) return this->error = testDefine::E_Error::name;
            if (this->degug_flag) this->print_last_received_derivedMessage_payload(msg);
            return this->error;
        };


};