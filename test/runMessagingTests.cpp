# include "testMessage.h"
# include "printMessage.h"
# include <string>
# include <algorithm>
int main(int argc, char **argv) {
    int max_args = 1; //Maximum value of argc allowed
    int ret = 0;
    
    if (argc == 2){
        //Run tests with Google Tests framework
        std::string arg1(argv[1]);
        arg1.erase(std::remove_if(arg1.begin(), arg1.end(), isspace), arg1.end());
        if (arg1 == "--gtest"){
            ::testing::InitGoogleTest(&argc, argv);
            ret = RUN_ALL_TESTS();
        }else{
            std::cout << "Invalid argument " << arg1 << ". Valid arguments are --gtest" << std::endl;
        }
    }else if(argc > 2){
        std::cout << "Invalid number of arguments " << argc << " provided. Maximum number of arguments is " << max_args << ". Valid arguments are --gtest" << std::endl;
    }else{
        //Run Tests with native test framework (if argc == 1)
        testMessage tester = testMessage(1,false); //Creating object of class used for testing
        bool verbose_tests = true;// Set to true to see sent/received messages (Tests with multiple messages will still suppress prints)
        tester.run_tests(verbose_tests); //Run test set (see: testMessage::run_tests in testMessage.cpp. Output is sent to stdout)
        ret = 0;
    }
    return ret;
}
