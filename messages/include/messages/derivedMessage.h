/**
 * @file: derivedMessage.h
 * @author: Mainak Mitra
 * 
 * @brief derivedMessage class used for sending, receiving and storing message with payload containing lights,camera, action and Name
 */

#ifndef _DERIVEDMESSAGE_
#define _DERIVEDMESSAGE_

#include "baseMessage.h"
typedef bool uint1_t; //!< Used to enforce 1 bit datatype

/*! derivedMessage class declaration*/
class derivedMessage: public baseMessage{
    private:
        uint8_t lights_camera_action; //!< Used to store lights, camera and action fields (MSB to LSB in that order)
        ustring8_t name; //!< Used to store Name field
    
    public:
    
        
        /**
        * Constructor for derivedMessage which initializes members (fields)
        */
        derivedMessage();

        //Access Methods
        /**
        * Member to obtain lights field in payload of last received message
        * @return lights
        */
        uint1_t get_lights() const;
        
        /**
        * Member to obtain camera field in payload of last received message
        * @return camera
        */
        uint1_t get_camera() const;

        /**
        * Member to obtain action field in payload of last received message
        * @return action
        */
        uint8_t get_action() const;

        /**
        * Member to obtain Name field in payload of last received message
        * @return Name
        */
        ustring8_t get_name() const;

        /**
        * Member to obtain string representing a message to be sent
        * @param message_IDin message_ID of sent message
        * @param sender_IDin sender_ID of message to be sent
        * @param receiver_IDin receiver_ID of message to be sent
        * @param lightsin lights field in payload of message to be sent
        * @param camerain camera field in payload of message to be sent
        * @param actionin action field in payload of message to be sent
        * @param name name field in payload of message to be sent
        * @return string representing message to be sent (in network byte order)
        * @note The lightsin, camerain and actionin input arguments are 8 bit type uint8_t. Internally exceptions enforce correct sizing. This is done to ensure user is careful in inputing the correct parameters
        */
        ustring8_t sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint8_t &lightsin, const uint8_t  &camerain, const uint8_t &actionin, const ustring8_t namein) const;
        
        /**
        * Member to receive message (in network byte order) and update members (fields)
        * @param net_messageinstring representing received message (in network byte order) 
        */
        void receiveMessage(ustring8_t net_messagein);
};

#endif //_DERIVEDMESSAGE_

