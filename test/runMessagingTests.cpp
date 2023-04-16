# include "testMessage.h"
# include "printMessage.h"

// #include <gtest/gtest.h>

int main(){

   //Run Tests
    testMessage tester = testMessage(1,false); //Creating object of class used for testing
    
    bool verbose_tests = true;// Set to true to see sent/received messages (Tests with multiple messages will still suppress prints)
    tester.run_tests(verbose_tests); //Run test set (see: testMessage::run_tests in testMessage.cpp. Output is sent to stdout)

    return 0;
}

// TEST(tests,baseMessage_send_and_receive){
//     testMessage tester = testMessage(1,false); //Creating object of class used for testing
//     baseMessage msga, msgb;
//     tester.test_send_recv_baseMessage(msga,msgb,10,154,6,40,(uint8_t *)"abcde");
//     //testMessage::E_Error this_success = tester.print_last_test_result(testMessage::E_Error::none);    
//     EXPECT_EQ(tester.error,testMessage::E_Error::none);
// }


    