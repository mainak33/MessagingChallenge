# include"derivedMessage.h"

int main(){
    baseMessage msga,msgb;
    //msga.createMessage(1,234,255,40,(uint8_t *)"abcde");
    ustring8_t str = msga.sendMessage(300,154,6,40,(uint8_t *)"abcde");
    msgb.receiveMessage(str);
    //msgb.receiveMessage(str);
    derivedMessage msgc,msgd;
    str = msgc.sendMessage(1000,253,255,1,0,55,(uint8_t *)"abcdefgh");
    msgc.receiveMessage(str);
    
    return 0;
}