# include"testHarness.h"
# include <iostream>

using namespace std;
int main(){

    
    baseMessage msga,msgb;
    
    testDefine T1 = testDefine(msga,msgb,true);
    //msga.createMessage(1,234,255,40,(uint8_t *)"abcde");
    ustring8_t str = msga.sendMessage(300,154,6,40,(uint8_t *)"abcde");
    msgb.receiveMessage(str);
    cout <<  (unsigned) msgb.get_message_ID() << endl;
    testDefine::E_Error e = T1.check_last_received_baseMesaage(msgb,300,154,6,40,(uint8_t *)"abcde");
    
    if (e != testDefine::E_Error::none) std::cout << "Error :" << e << std::endl;

    //msgb.receiveMessage(str);
    derivedMessage msgc,msgd;
    str = msgc.sendMessage(1000,253,255,1,0,55,(uint8_t *)"abcdefgh");
    msgc.receiveMessage(str);
    
    try{ 
        str = msgc.sendMessage(1000,253,255,1,0,44,(uint8_t *)"abcdefgh");
    }catch(std::invalid_argument &e){
        std::cerr << e.what() << std::endl;
        return -1;
    }


    

    return 0;
}