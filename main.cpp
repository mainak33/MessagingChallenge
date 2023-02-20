# include"testMessage.h"
# include"printMessage.h"


using namespace std;
int main(){

    //Example use of classes
    std::cout << "--- Example usage of baseMessage Class ---"  << std::endl;
    baseMessage msga,msgb;
    ustring8_t payload_a2b = ustring8_t((uint8_t *)"abcde");
    ustring8_t net_msg_a2b = msga.sendMessage(300,154,6,40,payload_a2b);
    print_sent_baseMessage(net_msg_a2b);
    msgb.receiveMessage(net_msg_a2b);
    print_last_received_baseMesaage(msgb);
    std::cout << std::endl;
    
    std::cout << "--- Example usage of derivedMessage Class ---"  << std::endl;
    derivedMessage msgc,msgd;
    ustring8_t payload_c2d = ustring8_t((uint8_t *)"abcdefgh");
    ustring8_t net_msg_c2d = msgc.sendMessage(1000,253,255,1,0,55,payload_c2d);
    print_sent_derivedMessage(net_msg_c2d);
    msgd.receiveMessage(net_msg_c2d);
    print_last_received_derivedMessage(msgd);
    std::cout << std::endl;

    //Starting Tests
    std::cout << "--- Testing Start---"  << std::endl;
    
    //Test 1: baseMessage with known inputs  (No errors expected)
    std::cout << " -- Test 1 : baseMessage with known inputs --"  << std::endl;
    testMessage tester = testMessage(1,false);
    tester.test_baseMessage(msga,msgb,300,154,6,40,(uint8_t *)"abcde");
    tester.print_last_test_result(testMessage::E_Error::none);
    
    //Test 2: derivedMessage with known inputs (No errors expected)
    std::cout << " -- Test 2 : derivedMessage with known inputs --"  << std::endl;
    tester.test_ID = 2;
    tester.test_derivedMessage(msgc,msgd,1000,253,255,1,0,55,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::none);

    //Test 3: derivedMessage with incorrect lights 8 > 1 (exception expected)
    std::cout << " -- Test 3 : derivedMessage with incorrect action --"  << std::endl;
    tester.test_ID =  3;
    tester.test_derivedMessage(msgc,msgc,1000,253,255,8,0,23,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::exception);

    //Test 4: derivedMessage with incorrect camera -1 < 0 (exception expected)
    std::cout << " -- Test 4 : derivedMessage with incorrect camera --"  << std::endl;
    tester.test_ID =  4;
    tester.test_derivedMessage(msgc,msgc,1000,253,255,0,-1,23,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::exception);

    //Test 5: derivedMessage with incorrect action 78 > 63 (exception expected)
    std::cout << " -- Test 5 : derivedMessage with incorrect action --"  << std::endl;
    tester.test_ID =  5;
    tester.test_derivedMessage(msgc,msgc,1000,253,255,1,0,78,ustring8_t((uint8_t *)"abcdefgh"));
    tester.print_last_test_result(testMessage::E_Error::exception);

    std::cout << std::endl;
    std::cout << "--- Testing End ---"  << std::endl;
    
    return 0;
}