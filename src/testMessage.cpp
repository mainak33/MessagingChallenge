/**
 * @file: testMessage.cpp
 * @author: Mainak Mitra
 * 
 * @brief derivedMessage class members implementation
 */

#include "testMessage.h"
#include <cmath>

//Function to generate a random string of given length
ustring8_t generate_random_ustring8_t(std::size_t length){
    const ustring8_t chars = ustring8_t((uint8_t *)"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);

    ustring8_t random_string;

    for (std::size_t kk = 0; kk < length; ++kk){
        random_string += chars[distribution(generator)];
    }

    return random_string;
}

//Constructor
testMessage::testMessage(const unsigned int &test_IDin, bool debug_flagin){
    this->test_ID = test_IDin;
    this->debug_flag = debug_flagin;
    this->error = testMessage::E_Error::none;
};

//Reset the testID and error
void testMessage::reset(const unsigned int &test_IDin){
    this->test_ID = test_IDin;
    this->error = testMessage::E_Error::none;
};

//Check if fields of last received baseMessage matches the expected values
testMessage::E_Error testMessage::check_last_received_baseMesaage(const baseMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t payload_lengthchk, const ustring8_t &payloadchk, bool skip_payload_check){
    if (msg.get_message_ID()      != message_IDchk     ) return this->error = testMessage::E_Error::message_ID ;
    if (msg.get_sender_ID()       != sender_IDchk      ) return this->error = testMessage::E_Error::sender_ID  ;
    if (msg.get_receiver_ID()     != receiver_IDchk    ) return this->error = testMessage::E_Error::receiver_ID;
    if (msg.get_payload_length()  != payload_lengthchk ) return this->error = testMessage::E_Error::payload_length;
    
    if (payload_lengthchk > 0 && !skip_payload_check) {
        const ustring8_t payloadmsg = msg.get_payload();
        if (payloadmsg.compare(payloadchk) !=0 ) return this->error = testMessage::E_Error::payload;
    }    
    if (this->debug_flag ) print_last_received_baseMesaage(msg);
    return this->error;
};

//Check if fields of last received derivedMessage matches the expected values
testMessage::E_Error testMessage::check_last_received_derivedMesaage(const derivedMessage &msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk){
    this->error = check_last_received_baseMesaage(msg, message_IDchk, sender_IDchk, receiver_IDchk, 72,ustring8_t(), true);
    if (msg.get_lights()  != lightschk       ) return this->error = testMessage::E_Error::lights;
    if (msg.get_camera()  != camerachk       ) return this->error = testMessage::E_Error::camera;
    if (msg.get_action()  != actionchk       ) return this->error = testMessage::E_Error::action;
    if (msg.get_name().compare(namechk) != 0 ) return this->error = testMessage::E_Error::name;
    if (this->debug_flag) print_last_received_derivedMessage_payload(msg);
    return this->error;
};

//Test sending and receiving a baseMessage
testMessage::E_Error testMessage::test_send_recv_baseMessage(baseMessage &send_msg, baseMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint32_t &payload_lengthchk, const ustring8_t &payloadchk){
    ustring8_t net_msg;
    if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Start" << std::endl; 
    try{
        net_msg = send_msg.sendMessage(message_IDchk, sender_IDchk, receiver_IDchk, payload_lengthchk, payloadchk);
    }catch(std::exception &e){
        if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during sending message :" << e.what() << std::endl;
        return this->error = testMessage::E_Error::exception;
    }   
     
    if (this->debug_flag) print_sent_baseMessage(net_msg);    
    
    try{
        recv_msg.receiveMessage(net_msg);
    }catch(std::exception &e){
        if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during recieving message :" << e.what() << std::endl;
        return this->error = testMessage::E_Error::exception;
    }   

    this->check_last_received_baseMesaage(recv_msg,message_IDchk, sender_IDchk, receiver_IDchk, payload_lengthchk, payloadchk);
    if (this->error != testMessage::E_Error::none) {
        if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Incorrect Field :" << this->errorstring(this->error) << std::endl;
        return this->error;
    }

    if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "SUCCESSFUL." << std::endl;
    return this->error;
}

//Test sending and receiving a derivedMessage
testMessage::E_Error testMessage::test_send_recv_derivedMessage(derivedMessage &send_msg, derivedMessage &recv_msg, const uint16_t &message_IDchk, const uint8_t &sender_IDchk, const uint8_t &receiver_IDchk, const uint8_t &lightschk, const uint8_t  &camerachk, const uint8_t &actionchk, const ustring8_t &namechk){
    ustring8_t net_msg;
    if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Start" << std::endl; 
    try{
        net_msg = send_msg.sendMessage(message_IDchk, sender_IDchk, receiver_IDchk, lightschk, camerachk, actionchk, namechk);
    }catch(std::exception &e){
        if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during sending message :" << e.what() << std::endl;
        return this->error = testMessage::E_Error::exception;
    }   
     
    if (this->debug_flag) print_sent_baseMessage(net_msg);    
    
    try{
        recv_msg.receiveMessage(net_msg);
    }catch(std::exception &e){
        if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "FAILURE. Reason: Exception occurred during receiving message :" << e.what() << std::endl;
        return this->error = testMessage::E_Error::exception;
    }   

    this->check_last_received_derivedMesaage(recv_msg, message_IDchk, sender_IDchk, receiver_IDchk, lightschk, camerachk, actionchk, namechk);
    if (this->error != testMessage::E_Error::none) {
        if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result : " <<  "FAILURE. Reason: Incorrect Field :" << this->errorstring(this->error) << std::endl;
        return this->error;
    }

    if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Result :  " <<  "SUCCESSFUL." << std::endl;
    return this->error;
}

//Print whether last test passed 
bool testMessage::print_last_test_result(const testMessage::E_Error & expected_error){
    bool success = false;
    if (this->debug_flag) std::cout << "    Test " << this->test_ID << " Run Expected Error : " << this->errorstring(expected_error) << std::endl;

    if (this->error == expected_error) {
        std::cout << "    Test " << this->test_ID << " : PASSED"  << std::endl;
        success = true;
    }else{ 
        std::cout << "    Test " << this->test_ID << " : FAILED"  << std::endl;
        success = false;
    }    
    std::cout << std::endl;
    return success;
}

//Run Tests
void testMessage::run_tests(bool is_verbose){
    //Set verbosity
    this->debug_flag = is_verbose;

    //Initialize some variables
    int n_success = 0;
    bool this_success;
    baseMessage msga, msgb;
    derivedMessage msgc, msgd;

    //Create random number generators (used for tests later)
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution <uint8_t> distpow1 (0,1);   // uniform distribution in range [0,2^1-1]
    std::uniform_int_distribution <uint8_t> distpow6 (0,std::pow(2,6)-1);   // uniform distribution in range [0, 2^6-1]
    std::uniform_int_distribution <uint8_t> distpow8 (0,std::pow(2,8)-1);   // uniform distribution in range [0, 2^8-1]
    std::uniform_int_distribution <uint16_t> distpow16(0,std::pow(2,16)-1); // uniform distribution in range [0, 2^16-1]
    std::uniform_int_distribution <uint32_t> distpow32(0,127);  // uniform distribution in range [0, 127]

    //Starting Tests
    std::cout << "--- Testing Start ---"  << std::endl;
    
    //Testing baseMessage
    std::cout << "--- Testing baseMesssage Class ---"  << std::endl;
    testMessage::E_Error current_error;

    //Test : baseMessage with known inputs  (No errors expected)
    this->reset(1);
    std::cout << " -- Test " << this->test_ID << " :: baseMessage send and receive with known inputs --"  << std::endl;
    this->test_send_recv_baseMessage(msga,msgb,10,154,6,40,(uint8_t *)"abcde");
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    if (this_success) n_success++;

    //Test : baseMessage with mesaage_ID > 255 to test endian agnosticity (No errors expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : baseMessage with mesaage_ID > 255 to test endian agnosticity --"  << std::endl;
    this->test_send_recv_baseMessage(msga,msgb,300,7,28,48,(uint8_t *)"afgdeg");
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    if (this_success) n_success++;

    //Test : baseMessage with 0 length  (No errors expected) 
    //NOTE: negative numbers may be implicitly converted to uint types. It is upto the API user to ensure that correct arguments are entered
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : baseMessage send and receive messsage with 0 length --"  << std::endl;
    this->test_send_recv_baseMessage(msga,msgb,51,66,222,0,(uint8_t *)"");
    this_success = this->print_last_test_result(testMessage::E_Error::none);\
    if (this_success) n_success++;

    //Test : baseMessage with payload input longer than specified length (No errors expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : baseMessage with with payload input longer than specified length --"  << std::endl;
    this->test_send_recv_baseMessage(msga,msgb,300,7,28,48,(uint8_t *)"afgdeghijkl");
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    if (this_success) n_success++;

    //Test : baseMessage with payload length longer than message (exception expected during send)    
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : baseMessage send and receive with payload length longer than message --"  << std::endl;
    this->test_send_recv_baseMessage(msga,msgb,51,66,222,64,(uint8_t *)"ab");
    this_success = this->print_last_test_result(testMessage::E_Error::exception);
    if (this_success) n_success++;

    //Test : baseMessage with really long message (No errors expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : baseMessage send and receive random long message(1E5 bytes) random --"  << std::endl;
    this->test_send_recv_baseMessage(msga,msgb,51,66,222,800000,generate_random_ustring8_t(100000));
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    if (this_success) n_success++;

    //Test : baseMessage with payload length in fractional bytes  (No errors expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : baseMessage with payload length in fractional bytes --"  << std::endl;
    this->test_send_recv_baseMessage(msga,msgb,51,66,222,1,generate_random_ustring8_t(14));
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    if (this_success) n_success++;

    //Test : baseMessage with random inputs  (No errors expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : baseMessage send and receive short messages( <128 bytes) 100 times with random inputs --"  << std::endl;
    uint32_t payload_lengthin, payload_lengthin_bytes;
    ustring8_t payloadin; 
    this->debug_flag = false;
    for (uint32_t msgnum = 0; msgnum < 100 ; msgnum++){
        payload_lengthin = distpow32(rng);
        payload_lengthin_bytes = ceil((double) payload_lengthin/8);
        payloadin = generate_random_ustring8_t(payload_lengthin_bytes);
        current_error = this->test_send_recv_baseMessage(msga,msgb,(uint16_t) distpow16(rng), (uint8_t) distpow8(rng), (uint8_t) distpow8(rng),payload_lengthin,payloadin);
        if (current_error != testMessage::E_Error::none) break;
    }
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    this->debug_flag = is_verbose;
    if (this_success) n_success++;

    //Testing derivedMessage
    std::cout << "--- Testing derivedMessage Class ---"  << std::endl;
    
    //Test : derivedMessage with known inputs (No errors expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : derivedMessage with known inputs --"  << std::endl;
    this->test_send_recv_derivedMessage(msgc,msgd,1000,253,255,1,0,55,ustring8_t((uint8_t *)"abcdefgh"));
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    if (this_success) n_success++;

    //Test : derivedMessage with incorrect lights 8 > 1 (exception expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : derivedMessage with incorrect action --"  << std::endl;
    this->test_send_recv_derivedMessage(msgc,msgd,1000,253,255,8,0,23,ustring8_t((uint8_t *)"abcdefgh"));
    this_success = this->print_last_test_result(testMessage::E_Error::exception);
    if (this_success) n_success++;

    //Test : derivedMessage with incorrect camera 5 > 1 (exception expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : derivedMessage with incorrect camera --"  << std::endl;
    this->test_send_recv_derivedMessage(msgc,msgd,1000,253,255,0,5,23,ustring8_t((uint8_t *)"abcdefgh"));
    this_success = this->print_last_test_result(testMessage::E_Error::exception);
    if (this_success) n_success++;

    //Test : derivedMessage with incorrect action 78 > 63 (exception expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : derivedMessage with incorrect action --"  << std::endl;
    this->test_send_recv_derivedMessage(msgc,msgd,1000,253,255,1,0,78,ustring8_t((uint8_t *)"abcdefgh"));
    this_success = this->print_last_test_result(testMessage::E_Error::exception);
    if (this_success) n_success++;


    //Test : derivedMessage with incorrect name longer than 8 characters (exception expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : derivedMessage with incorrect name longer than 8 characters --"  << std::endl;
    this->test_send_recv_derivedMessage(msgc,msgd,1000,253,255,1,0,78,ustring8_t((uint8_t *)"abcdefghi"));
    this_success = this->print_last_test_result(testMessage::E_Error::exception);
    if (this_success) n_success++;

    //Test : derivedMessage with incorrect name shorter than 8 characters (exception expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : derivedMessage with incorrect name longer than 8 characters --"  << std::endl;
    this->test_send_recv_derivedMessage(msgc,msgd,1000,253,255,1,0,78,ustring8_t((uint8_t *)"abcde"));
    this_success = this->print_last_test_result(testMessage::E_Error::exception);
    if (this_success) n_success++;

    //Test : derivedMessage with random inputs  (No errors expected)
    this->reset(++this->test_ID);
    std::cout << " -- Test " << this->test_ID << " : derivedMessage send and receive 100 times with random inputs --"  << std::endl;
    this->debug_flag = false;
    for (uint32_t msgnum = 0; msgnum < 100 ; msgnum++){
        current_error = this->test_send_recv_derivedMessage(msgc,msgd,(uint16_t) distpow16(rng), (uint8_t) distpow8(rng), (uint8_t) distpow8(rng),(uint1_t) distpow1(rng),(uint1_t) distpow1(rng), distpow6(rng),generate_random_ustring8_t(8));
        if (current_error != testMessage::E_Error::none) break;
        //else std::cout << "Message " << (unsigned long) msgnum << "passed"<< std::endl;
    }
    this_success = this->print_last_test_result(testMessage::E_Error::none);
    this->debug_flag = is_verbose;
    if (this_success) n_success++;

    std::cout << std::endl;
    
    std::cout << "TESTS SUMMARY : " << n_success << "/" << this->test_ID << " tests passed ---"  << std::endl;
    
    std::cout << std::endl;
    std::cout << "--- Testing End ---"  << std::endl;
}