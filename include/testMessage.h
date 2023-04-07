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

 /**
* Function to generate a random string of given length
* @param length length of string to be generated
* @return random string
*/
ustring8_t generate_random_ustring8_t(std::size_t length);

/*! testMessage class declaration*/
class testMessage{
    public:

        /*! enum class to describe type of error or which field the error is associated with during tests*/
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

        /**
        * Public method to return string associated with entries in enum class E_Error
        * @param ein object of enum class E_Error
        * @return string associated with ein that describes that error type or which field the error was in
        */ 
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
       
        /**
        * Method to reset the class before performing a test
        * @param test_IDin Test ID
        */
        void reset(const unsigned int &test_IDin);

        /**
        * Method to check if fields of last received baseMessage matched the expected values
        * @param msg basemessage object to be checked
        * @param message_IDchk expected message_ID
        * @param sender_IDchk expected sender_ID
        * @param receiver_IDchk expected receiver_ID
        * @param payload_lengthchk expected payload_length
        * @param payloadchk expected payload
        * @param skip_payload_check skip checking payload if true
        * @return error type
        */
        testMessage::E_Error check_last_received_baseMesaage(const baseMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t &payloadchk, bool skip_payload_check = false);


        /**
        * Method to check if fields of last received derivedMessage matched the expected values
        * @param msg derivedMessage object to be checked
        * @param message_IDchk expected message_ID
        * @param sender_IDchk expected sender_ID
        * @param receiver_IDchk expected receiver_ID
        * @param lightschk expected lights
        * @param camerachk expected camera
        * @param actionchk expected action
        * @param namechk expected name
        * @return error type
        */
        testMessage::E_Error check_last_received_derivedMesaage(const derivedMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk);

        /**
        * Method to test sending and receiving a baseMessage 
        * @param send_msg baseMessage object used to send message
        * @param recv_msg baseMessage object used to receive message
        * @param message_IDchk expected message_ID
        * @param sender_IDchk expected sender_ID
        * @param receiver_IDchk expected receiver_ID
        * @param payload_lengthchk expected payload_length
        * @param payloadchk expected payload
        * @param skip_payload_check skip checking payload if true
        * @return error type
        */
        testMessage::E_Error test_send_recv_baseMessage(baseMessage &send_msg, baseMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t &payload_lengthchk, const ustring8_t &payloadchk);

        /**
        * Method to test sending and receiving a derivedMessage
        * @param send_msg derivedMessage object used to send message
        * @param recv_msg derivedMessage object used to receive message
        * @param message_IDchk expected message_ID
        * @param sender_IDchk expected sender_ID
        * @param receiver_IDchk expected receiver_ID
        * @param lightschk expected lights
        * @param camerachk expected camera
        * @param actionchk expected action
        * @param namechk expected name
        * @return error type
        */
        testMessage::E_Error test_send_recv_derivedMessage(derivedMessage &send_msg, derivedMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk);

        /**
        * Method to print whether the last test that was run passed or failed
        * @param expected_error error expected during that test (is usually none)
        * @return true if test passed, false otherwise
        */
        bool print_last_test_result(const testMessage::E_Error & expected_error);


    public:
        bool debug_flag;      //!< Debug flag to restrict or allow prints
        unsigned int test_ID; //!< Flag for identifying current test 

        /**
        * Constructor
        * @param test_IDin Starting test ID
        * @param debug_flagin Debug flag to restrict or allow prints
        * @return Class Object
        */
        explicit testMessage(const unsigned int &test_IDin, bool debug_flagin = false);
       
        /**
        * Method to Run Tests (output report to stdout)
        * @param is_verbose set to true to see sent/received messages (Tests with multiple messages will still suppress prints)
        */
        void run_tests(bool is_verbose);
 
};

#endif //_TESTMESSAGE_