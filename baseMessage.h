/**
 * @file: baseMessage.h
 * @author: Mainak Mitra
 * 
 * @brief baseMessage class used for sending, receiving and storing generic message details 
 */

#ifndef _BASEMESSAGE_

#define _BASEMESSAGE_

#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

#include <stdint.h>
#include <string>

typedef std::basic_string<uint8_t> ustring8_t; //!< std::u8string only available since C++20; uint8_t is equivalent to unsigned char


/*! baseMessage class declaration*/
class baseMessage{
    protected:
        uint16_t message_ID;     //!< Message ID stored in Network Byte Order (size: 16 bits)
        uint8_t  sender_ID;      //!< Sender ID stored in Network Byte Order (size: 8 bits)
        uint8_t  receiver_ID;    //!< Receiver ID stored in Network Byte Order (size: 8 bits)
        uint32_t payload_length; //!< Payload length (in bits) stored in Network Byte Order (size: 32 bits)
        ustring8_t payload;      //!< String containing the paylaoad (std::basic_string<uint8_t>) (maximum size: (payload_length/8) characters)
        
       /**
       * Member to obtain minimum number of integer bytes needed to represent given number of bits
       * @param nbits number of bits
       * @return Minimum number of bytes that are needed to represent the input number of bits (no fractional answer)
       */
        uint32_t nbits_to_nbytes(const uint32_t &nbits) const{
            uint32_t nbytes = nbits/8;
            if (nbits%8) nbytes++;
            return nbytes;
        }

    public:
        /**
         * Constructor for baseMessage which initializes members (fields)
        */
        baseMessage();

        //Access Methods
        /**
        * Member to obtain message_ID of last received message
        * @return message_ID
        */
        uint16_t get_message_ID() const;
        
        /**
        * Member to obtain sender_ID of last received message
        * @return sender_ID
        */
        uint8_t get_sender_ID() const;
        
        /**
        * Member to obtain receiver_ID of last received message
        * @return receiver_ID
        */
        uint8_t get_receiver_ID() const;

        /**
        * Member to obtain payload_length of last received message
        * @return payload_length
        */
        uint32_t get_payload_length() const;

        /**
        * Member to obtain payload of last received message
        * @return payload
        */
        ustring8_t get_payload() const;
        
        /**
        * Member to obtain string representing a message to be sent
        * @param message_IDin message_ID of sent message
        * @param sender_IDin sender_ID of message to be sent
        * @param receiver_IDin receiver_ID of message to be sent
        * @param payload_lengthin payload length of message to be sent
        * @param payloadin payload of message to be sent
        * @return string representing message to be sent (in network byte order)
        */
        virtual ustring8_t sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint32_t payload_lengthin, const ustring8_t payloadin)const;
        
        
        /**
        * Member to receive message (in network byte order) and update members (fields)
        * @param net_messageinstring representing received message (in network byte order) 
        */
        virtual void receiveMessage(const ustring8_t &net_messagein);     

};

#endif //_BASEMESSAGE_

