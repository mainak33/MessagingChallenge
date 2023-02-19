#include "baseMessage.h"
typedef bool uint1_t;

class derivedMessage: public baseMessage{
    private:
        uint8_t lights_camera_action;
        uint8_t* name;
    
    public:
    
        //Constructor Class (Field Initialization) 
        derivedMessage();

        //Access Methods
        uint1_t get_lights() const;
        uint1_t get_camera() const;
        uint8_t get_action() const;
        ustring8_t get_name() const;
        //Send Message
        ustring8_t sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint1_t &lightsin, const uint1_t  &camerain, const uint8_t &actionin, const uint8_t* namein) const;
        
        //Receive Message
        void receiveMessage(ustring8_t net_messagein);
};