/**
 * @file: testHarness.h
 * @author: Mainak Mitra
 * 
 * @brief testHarness class used for testing baseMessage and derivedMessage
 */

# include"derivedMessage.h"
//# include <iostream>


class testDefine{
    private:
       baseMessage send_msg;
       baseMessage recv_msg;
    public:
        bool degug_flag;

        explicit testDefine(baseMessage &send_msgin,baseMessage &recv_msgin){
            this->send_msg = std::move(send_msgin);
            this->recv_msg = std::move(recv_msgin);
            this->degug_flag = false;
        }
        
        
        test_generic_message((const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint32_t payload_lengthin, const ustring8_t payloadin)const {
            send_msg->Send()
        }
        print_last_received_msg(){
            printf("---Base Received Message---\n");
            printf("Message  ID: %u\n", (unsigned) this->base_msg->get_message_ID());
            printf("Sender   ID: %u\n", this->base_msg->get_sender_ID());
            printf("Receiver ID: %u\n", this->base_msg->get_receiver_ID());
            printf("Payload length: %lu\n", (unsigned long) this->base_msg->payload_length);
            printf("Received Message: ");
            uint32_t payload_length_bytes2 = nbits_to_nbytes(this->base_msg->payload_length);
            for (uint32_t kk=0; kk < payload_length_bytes2; ++kk){
                printf("%c", (uint8_t) this->base_msg->payload[kk]);
            }
            printf("\n");
        };


};