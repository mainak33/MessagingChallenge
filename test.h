/**
 * @file: test.h
 * @author: Mainak Mitra
 * 
 * @brief test Class used for testing baseMessage and derivedMessage
 */

#ifndef _TESTMESSAGE_

#define _TESTMESSAGE_


#include "derivedMessage.h"
#include "printMessage.h"
#include <assert.h>
#include <iostream>

class test{
    public:
        enum class E_Error{
            invalid        = -1,
            none           =  0, 
            message_ID     =  1,
            sender_ID      =  2, 
            receiver_ID    =  3,
            payload_length =  4,
            payload        =  5,  
            lights         =  6, 
            camera         =  7, 
            action         =  8, 
            name           =  9,
            exception      = 10,      
       };

       std::string errorstring(const test::E_Error &ein){
            if  (ein == test::E_Error::invalid        ) return "invalid";
            if  (ein == test::E_Error::none           ) return "None";
            if  (ein == test::E_Error::message_ID     ) return "message_ID";
            if  (ein == test::E_Error::sender_ID      ) return "sender_ID"; 
            if  (ein == test::E_Error::receiver_ID    ) return "receiver_ID";
            if  (ein == test::E_Error::payload_length ) return "payload length";
            if  (ein == test::E_Error::payload        ) return "payload";  
            if  (ein == test::E_Error::lights         ) return "lights";
            if  (ein == test::E_Error::camera         ) return "camera";
            if  (ein == test::E_Error::action         ) return "action"; 
            if  (ein == test::E_Error::name           ) return "name"; 
            if  (ein == test::E_Error::exception      ) return "exception";
            return ""; 
       };
    
    private:
       test::E_Error error;
       
    public:
        
        bool degug_flag;
        unsigned int test_ID;

        explicit test(const unsigned int &test_IDin, bool degug_flagin = false){
            this->test_ID = test_IDin;
            this->degug_flag = degug_flagin;
            this->error = test::E_Error::none;
        };

  
        test::E_Error check_last_received_baseMesaage(const baseMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t payloadchk, bool skip_payload_check = false){
            if (msg.get_message_ID()      != message_IDchk     ) return this->error = test::E_Error::message_ID ;
            if (msg.get_sender_ID()       != sender_IDchk      ) return this->error = test::E_Error::sender_ID  ;
            if (msg.get_receiver_ID()     != receiver_IDchk    ) return this->error = test::E_Error::receiver_ID;
            if (msg.get_payload_length()  != payload_lengthchk ) return this->error = test::E_Error::payload_length;
            if (!skip_payload_check && msg.get_payload().compare(payloadchk) != 0     ) return this->error = test::E_Error::payload;
            if (this->degug_flag ) print_last_received_baseMesaage(msg);
            return this->error;
        };

        test::E_Error check_last_received_derivedMesaage(const derivedMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t namechk){
            this->error = check_last_received_baseMesaage(msg, message_IDchk, sender_IDchk, receiver_IDchk, 72,ustring8_t(), true);
            if (msg.get_lights()  != lightschk       ) return this->error = test::E_Error::lights;
            if (msg.get_camera()  != camerachk       ) return this->error = test::E_Error::camera;
            if (msg.get_action()  != actionchk       ) return this->error = test::E_Error::action;
            if (msg.get_name().compare(namechk) != 0 ) return this->error = test::E_Error::name;
            if (this->degug_flag) print_last_received_derivedMessage_payload(msg);
            return this->error;
        };

        test::E_Error test_baseMessage(baseMessage &send_msg, baseMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t payloadchk){
            ustring8_t net_msg;
            if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Start" << std::endl; 
            try{
                net_msg = send_msg.sendMessage(message_IDchk, sender_IDchk, receiver_IDchk, payload_lengthchk, payloadchk);
            }catch(std::exception &e){
                std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during sending message :" << e.what() << std::endl;
                return this->error = test::E_Error::exception;
            }   
             
            if (this->degug_flag) print_sent_baseMessage(net_msg);    
            
            try{
                recv_msg.receiveMessage(net_msg);
            }catch(std::exception &e){
                if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during recieving message :" << e.what() << std::endl;
                return this->error = test::E_Error::exception;
            }   

            this->check_last_received_baseMesaage(recv_msg,message_IDchk, sender_IDchk, receiver_IDchk, payload_lengthchk, payloadchk);
            if (this->error != test::E_Error::none) {
                if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Incorrect Field :" << this->errorstring(this->error) << std::endl;
                return this->error;
            }

            if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "SUCCESSFUL." << std::endl;
            return this->error;
        }

        test::E_Error test_derivedMessage(derivedMessage &send_msg, derivedMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t namechk){
            ustring8_t net_msg;
            if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Start" << std::endl; 
            try{
                net_msg = send_msg.sendMessage(message_IDchk, sender_IDchk, receiver_IDchk, lightschk, camerachk, actionchk, namechk);
            }catch(std::exception &e){
                if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during sending message :" << e.what() << std::endl;
                return this->error = test::E_Error::exception;
            }   
             
            if (this->degug_flag) print_sent_baseMessage(net_msg);    
            
            try{
                recv_msg.receiveMessage(net_msg);
            }catch(std::exception &e){
                if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during recieving message :" << e.what() << std::endl;
                return this->error = test::E_Error::exception;
            }   

            this->check_last_received_derivedMesaage(recv_msg, message_IDchk, sender_IDchk, receiver_IDchk, lightschk, camerachk, actionchk, namechk);
            if (this->error != test::E_Error::none) {
                if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Result : " <<  "FAILURE. Reason: Incorrect Field :" << this->errorstring(this->error) << std::endl;
                return this->error;
            }

            if (this->degug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "SUCCESSFUL." << std::endl;
            return this->error;
        }

        void print_last_test_result(const test::E_Error & expected_error){
            if (this->error == expected_error) std::cout << "    Test " << this->test_ID << " : SUCCESS"  << std::endl;
            else std::cout << "    Test " << this->test_ID << " : FAILURE"  << std::endl;
            std::cout << std::endl;
            return;
        }
    
};

#endif //_TESTMESSAGE_