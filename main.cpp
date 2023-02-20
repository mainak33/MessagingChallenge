# include"testMessage.h"
# include"printMessage.h"


int main(){

    //Example use of classes
    //NOTE: negative numbers may be implicitly converted to uint types. It is upto the API user to ensure that correct arguments are entered
    std::cout << "--- Example usage of baseMessage Class ---"  << std::endl;
    baseMessage msga,msgb;
    ustring8_t payload_a2b = ustring8_t((uint8_t *)"abcde");
    ustring8_t net_msg_a2b = msga.sendMessage((uint16_t)300, (uint8_t)44, (uint8_t)6, (uint32_t)40, payload_a2b);
    print_sent_baseMessage(net_msg_a2b);
    msgb.receiveMessage(net_msg_a2b);
    print_last_received_baseMesaage(msgb);
    std::cout << std::endl;
    
    std::cout << "--- Example usage of derivedMessage Class ---"  << std::endl;
    derivedMessage msgc,msgd;
    ustring8_t payload_c2d = ustring8_t((uint8_t *)"abcdefgh");
    ustring8_t net_msg_c2d = msgc.sendMessage((uint16_t) 1000, (uint8_t) 253, (uint8_t) 255, 1,0,55,payload_c2d);
    print_sent_derivedMessage(net_msg_c2d);
    msgd.receiveMessage(net_msg_c2d);
    print_last_received_derivedMessage(msgd);
    std::cout << std::endl;

    //Starting Tests
    std::cout << "--- Testing Start ---"  << std::endl;
    
    //Testing baseMessage
    std::cout << "--- Testing baseMesssage Class ---"  << std::endl;
    testMessage::E_Error current_error;
    bool debug_flag = false;
    testMessage tester = testMessage(1,debug_flag);

    //Test 1: baseMessage with known inputs  (No errors expected)
    std::cout << " -- Test 1 : baseMessage send and receive with known inputs --"  << std::endl;
    tester.reset(1);
    tester.test_baseMessage(msga,msgb,300,154,6,40,(uint8_t *)"abcde");
    tester.print_last_test_result(testMessage::E_Error::none);

    //Test 2: baseMessage with 0 length  (No errors expected) 
    //NOTE: negative numbers may be implicitly converted to uint types. It is upto the API user to ensure that correct arguments are entered
    std::cout << " -- Test 2: baseMessage send and receive messsage with 0 length --"  << std::endl;
    tester.reset(2);
    tester.test_baseMessage(msga,msgb,51,66,222,0,(uint8_t *)"");
    tester.print_last_test_result(testMessage::E_Error::none);

    //Test 3: baseMessage with payload length longer than message (exception expected during send)    
    std::cout << " -- Test 3: baseMessage send and receive with payload length longer than message --"  << std::endl;
    tester.reset(3);
    tester.test_baseMessage(msga,msgb,51,66,222,64,(uint8_t *)"ab");
    tester.print_last_test_result(testMessage::E_Error::exception);

    //Test 4: baseMessage with really long message (No errors expected)
    std::cout << " -- Test 4 : baseMessage send and receive random long message(1E5 bytes) random --"  << std::endl;
    tester.reset(4);
    //tester.debug_flag=true;
    tester.test_baseMessage(msga,msgb,51,66,222,800000,generate_random_ustring8_t(100000));
    tester.print_last_test_result(testMessage::E_Error::none);
    //tester.debug_flag=false;

    //Test 5: baseMessage with payload length in fractional bytes  (No errors expected)
    std::cout << " -- Test 5 : with payload length in fractional bytes --"  << std::endl;
    tester.reset(5);
    tester.test_baseMessage(msga,msgb,51,66,222,1,generate_random_ustring8_t(14));
    tester.print_last_test_result(testMessage::E_Error::none);
    

    //Test 6: baseMessage with random inputs  (No errors expected)
    std::cout << " -- Test 6 : baseMessage send and receive short messages( <128 bytes) 100 times with random inputs --"  << std::endl;
    tester.reset(6);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution <uint8_t> distpow8 (0,std::pow(2,8)-1);   // uniform distribution in range [0, 2^8-1]
    std::uniform_int_distribution <uint16_t> distpow16(0,std::pow(2,16)-1); // uniform distribution in range [0, 2^16-1]
    std::uniform_int_distribution <uint32_t> distpow32(0,127);  // uniform distribution in range [0, 127]

    uint32_t payload_lengthin, payload_lengthin_bytes;
    ustring8_t payloadin; 
    
    for (uint32_t msgnum = 0; msgnum < 100 ; msgnum++){
        payload_lengthin = distpow32(rng);
        payload_lengthin_bytes = ceil((double) payload_lengthin/8);
        payloadin = generate_random_ustring8_t(payload_lengthin_bytes);
        current_error = tester.test_baseMessage(msga,msgb,(uint16_t) distpow16(rng), (uint8_t) distpow8(rng), (uint8_t) distpow8(rng),payload_lengthin,payloadin);
        if (current_error != testMessage::E_Error::none) break;
        //else std::cout << "Message " << (unsigned long) msgnum << "passed"<< std::endl;
    }
    tester.print_last_test_result(testMessage::E_Error::none);
    
    //Testing derivedMessage
    std::cout << "--- Testing derivedMessage Class ---"  << std::endl;
    
    //Test 7: derivedMessage with known inputs (No errors expected)
    std::cout << " -- Test 7 : derivedMessage with known inputs --"  << std::endl;
    tester.reset(7);
    tester.test_derivedMessage(msgc,msgd,1000,253,255,1,0,55,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::none);

    //Test 8: derivedMessage with incorrect lights 8 > 1 (exception expected)
    std::cout << " -- Test 8 : derivedMessage with incorrect action --"  << std::endl;
    tester.reset(8);
    tester.test_derivedMessage(msgc,msgc,1000,253,255,8,0,23,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::exception);

    //Test 9: derivedMessage with incorrect camera 5 > 1 (exception expected)
    std::cout << " -- Test 9 : derivedMessage with incorrect camera --"  << std::endl;
    tester.reset(9);
    tester.test_derivedMessage(msgc,msgc,1000,253,255,0,5,23,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::exception);

    //Test 10: derivedMessage with incorrect action 78 > 63 (exception expected)
    std::cout << " -- Test 10 : derivedMessage with incorrect action --"  << std::endl;
    tester.reset(10);
    tester.test_derivedMessage(msgc,msgc,1000,253,255,1,0,78,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::exception);

    std::cout << std::endl;
    std::cout << "--- Testing End ---"  << std::endl;
    
    return 0;
}