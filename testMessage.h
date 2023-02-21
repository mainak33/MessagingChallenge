/**
 * @file: testMessage.h
 * @author: Mainak Mitra
 * 
 * @brief testMessage Class used for testing baseMessage and derivedMessage
 */

#ifndef _TESTMESSAGE_

#define _TESTMESSAGE_


#include "derivedMessage.h"
#include "printMessage.h"
#include <assert.h>
#include <iostream>
#include <random>

ustring8_t generate_random_ustring8_t(std::size_t length);

class testMessage{
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

       std::string errorstring(const testMessage::E_Error &ein){
            if  (ein == testMessage::E_Error::invalid        ) return "invalid";
            if  (ein == testMessage::E_Error::none           ) return "None";
            if  (ein == testMessage::E_Error::message_ID     ) return "message_ID";
            if  (ein == testMessage::E_Error::sender_ID      ) return "sender_ID"; 
            if  (ein == testMessage::E_Error::receiver_ID    ) return "receiver_ID";
            if  (ein == testMessage::E_Error::payload_length ) return "payload length";
            if  (ein == testMessage::E_Error::payload        ) return "payload";  
            if  (ein == testMessage::E_Error::lights         ) return "lights";
            if  (ein == testMessage::E_Error::camera         ) return "camera";
            if  (ein == testMessage::E_Error::action         ) return "action"; 
            if  (ein == testMessage::E_Error::name           ) return "name"; 
            if  (ein == testMessage::E_Error::exception      ) return "exception";
            return ""; 
       };
    
    private:
       testMessage::E_Error error; //!< Internal multivariate error flag 
       
    public:
        bool debug_flag;      //!< Debug flag to restrict or allow prints
        unsigned int test_ID; //!< Internal flag for identifying current test 

        explicit testMessage(const unsigned int &test_IDin, bool debug_flagin = false);

        void reset(const unsigned int &test_IDin);

        testMessage::E_Error check_last_received_baseMesaage(const baseMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t &payloadchk, bool skip_payload_check = false);

        testMessage::E_Error check_last_received_derivedMesaage(const derivedMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk);

        testMessage::E_Error test_send_recv_baseMessage(baseMessage &send_msg, baseMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t &payload_lengthchk, const ustring8_t &payloadchk);

        testMessage::E_Error test_send_recv_derivedMessage(derivedMessage &send_msg, derivedMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk);

        bool print_last_test_result(const testMessage::E_Error & expected_error);

        void run_tests(bool is_verbose);
        
       
    
};

#endif //_TESTMESSAGE_