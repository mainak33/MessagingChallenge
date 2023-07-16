/**
 * @file: testMessage.h
 * @author: Mainak Mitra
 * 
 * @brief testMessage Class used for testing baseMessage and derivedMessage
 */

#pragma once

#include <messages/derivedMessage.h>
#include <messages/printMessage.h>
#include <assert.h>
#include <iostream>
#include <random>
#include <cmath>
#include <gtest/gtest.h>
 /**
* Function to generate a random string of given length
* @param length length of string to be generated
* @return random string
*/
ustring8_t generate_random_ustring8_t(std::size_t length);

/*! testMessage class declaration*/
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

        /*! enum class to describe type of error or which field the error is associated with during tests*/
        enum class E_Error;

        /**
        * Public method to return string associated with entries in enum class E_Error
        * @param ein object of enum class E_Error
        * @return string associated with ein that describes that error type or which field the error was in
        */ 
        std::string errorstring(const testMessage::E_Error &ein);
    
    
       testMessage::E_Error error; //!< Internal multivariate error flag 
    
    protected:  
        

       
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
        testMessage::E_Error check_last_received_baseMesaage(const messages::baseMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t &payloadchk, bool skip_payload_check = false);


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
        testMessage::E_Error check_last_received_derivedMesaage(const messages::derivedMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk);

        
        /**
        * Method to print whether the last test that was run passed or failed
        * @param expected_error error expected during that test (is usually none)
        * @return true if test passed, false otherwise
        */
        bool print_last_test_result(const testMessage::E_Error & expected_error);


    public:
       
        unsigned int test_ID; //!< Flag for identifying current test 
        bool debug_flag;      //!< Flag for local printout
        /**
        * Constructor
        * @return Class Object
        */
        testMessage();
        //explicit 
        testMessage(const unsigned int &test_IDin, bool debug_flagin = false);
       
        /**
        * Method to Run Tests (output report to stdout)
        * @param is_verbose set to true to see sent/received messages (Tests with multiple messages will still suppress prints)
        */
        void run_tests(bool is_verbose);

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
        testMessage::E_Error test_send_recv_baseMessage(messages::baseMessage &send_msg, messages::baseMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t &payload_lengthchk, const ustring8_t &payloadchk);

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
        testMessage::E_Error test_send_recv_derivedMessage(messages::derivedMessage &send_msg, messages::derivedMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk);

 
};

//Framework Class to test baseMessage with GTest
class testbaseMessage:  public testMessage, public ::testing::Test{
    protected:
        void SetUp() override {
            this->reset(++this->test_ID);
        };
        messages::baseMessage msga, msgb;
        
        //Create random number generators (used for tests later)
        std::random_device dev;
        std::mt19937 rng;
        std::uniform_int_distribution <uint8_t>  distpow1 ; //!< uniform distribution in range [0,2^1-1]
        std::uniform_int_distribution <uint8_t>  distpow6 ; //!< uniform distribution in range [0, 2^6-1]
        std::uniform_int_distribution <uint8_t>  distpow8 ; //!< uniform distribution in range [0, 2^8-1]
        std::uniform_int_distribution <uint16_t> distpow16; //!< uniform distribution in range [0, 2^16-1]
        std::uniform_int_distribution <uint32_t> distpow32; //!< uniform distribution in range [0, 127] 
    
        testbaseMessage(){
            rng = std::mt19937(dev());
            distpow1 =std::uniform_int_distribution <uint8_t> (0,1);   // uniform distribution in range [0,2^1-1]
            distpow6 =std::uniform_int_distribution <uint8_t> (0,std::pow(2,6)-1);   // uniform distribution in range [0, 2^6-1]
            distpow8 =std::uniform_int_distribution <uint8_t> (0,std::pow(2,8)-1);   // uniform distribution in range [0, 2^8-1]
            distpow16=std::uniform_int_distribution <uint16_t>(0,std::pow(2,16)-1); // uniform distribution in range [0, 2^16-1]
            distpow32=std::uniform_int_distribution <uint32_t>(0,127);  // uniform distribution in range [0, 127] 
        }
        
};

//Framework Class to test derivedMessage with GTest
class testderivedMessage:  public testMessage, public ::testing::Test{
    protected:
        void SetUp() override {
            this->reset(++this->test_ID);
        };
        
        messages::derivedMessage msgc, msgd;
  
        //Create random number generators (used for tests later)
        std::random_device dev;
        std::mt19937 rng;
        std::uniform_int_distribution <uint8_t>  distpow1 ; //!< uniform distribution in range [0,2^1-1]
        std::uniform_int_distribution <uint8_t>  distpow6 ; //!< uniform distribution in range [0, 2^6-1]
        std::uniform_int_distribution <uint8_t>  distpow8 ; //!< uniform distribution in range [0, 2^8-1]
        std::uniform_int_distribution <uint16_t> distpow16; //!< uniform distribution in range [0, 2^16-1]
        std::uniform_int_distribution <uint32_t> distpow32; //!< uniform distribution in range [0, 127] 
    
        testderivedMessage(){
            rng = std::mt19937(dev());
            distpow1 =std::uniform_int_distribution <uint8_t> (0,1);   // uniform distribution in range [0,2^1-1]
            distpow6 =std::uniform_int_distribution <uint8_t> (0,std::pow(2,6)-1);   // uniform distribution in range [0, 2^6-1]
            distpow8 =std::uniform_int_distribution <uint8_t> (0,std::pow(2,8)-1);   // uniform distribution in range [0, 2^8-1]
            distpow16=std::uniform_int_distribution <uint16_t>(0,std::pow(2,16)-1); // uniform distribution in range [0, 2^16-1]
            distpow32=std::uniform_int_distribution <uint32_t>(0,127);  // uniform distribution in range [0, 127] 
        }
        
};
