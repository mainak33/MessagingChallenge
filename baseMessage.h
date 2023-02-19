#ifdef _WIN32
#include <winsock.h>
#else
#include <arpa/inet.h>
#endif

#include <stdint.h>
#include <string>

typedef std::basic_string<uint8_t> ustring8_t; //std::u8string only available since C++20; uint8_t is equivalent to unsigned char

class baseMessage{
    protected:
        uint16_t message_ID; //in Network
        uint8_t  sender_ID;
        uint8_t  receiver_ID;
        uint32_t payload_length; //Payload length in bits
        uint8_t* payload;
        uint32_t nbits_to_nbytes(const uint32_t &nbits) const{
            uint32_t nbytes = nbits/8;
            if (nbits%8) nbytes++;
            return nbytes;
        }

    public:
        //Constructor Class (Field Initialization) 
        baseMessage();

        //Access Methods
        uint16_t get_message_ID() const;
        uint8_t get_sender_ID() const;
        uint8_t get_receiver_ID() const;
        uint32_t get_payload_length() const;       
        
        //Send Message
        virtual ustring8_t sendMessage(const uint16_t &message_IDin, const uint8_t &sender_IDin, const uint8_t &receiver_IDin, const uint32_t payload_lengthin, const uint8_t* payloadin)const;
        
        //Receive Message and Update members
        virtual void receiveMessage(const ustring8_t &net_messagein);     
        
        //Destructor 
        ~baseMessage();

};