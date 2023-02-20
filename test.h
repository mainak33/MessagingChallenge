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

  
        test::E_Error check_last_received_baseMesaage(const baseMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t payloadchk, bool skip_payload_check = false);

        test::E_Error check_last_received_derivedMesaage(const derivedMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t namechk);

        test::E_Error test_baseMessage(baseMessage &send_msg, baseMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t payloadchk);

        test::E_Error test_derivedMessage(derivedMessage &send_msg, derivedMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t namechk);

        void print_last_test_result(const test::E_Error & expected_error);
    
};

#endif //_TESTMESSAGE_