/**
 * @file: printMessage.h
 * @author: Mainak Mitra
 * 
 * @brief function declarations for printing message details 
 */

#ifndef _PRINTMESSAGE_

#define _PRINTMESSAGE_

#include "derivedMessage.h"
#include <cmath>

namespace messages{
    
    /**
    * Get the version of the messages library 
    */
    std::string get_version();

    /**
    * Print the version of the messages library 
    */
    void print_version();
 
    /**
    * Print sent baseMessage 
    * @param net_msgin message string in Network Byte Ordering
    */
    void print_sent_baseMessage(const ustring8_t &net_msgin, bool print_long_payload = false);

    /**
    * Print sent derivedMessage 
    * @param net_msgin message string in Network Byte Ordering
    */
    void print_sent_derivedMessage(const ustring8_t &net_msgin);

    /**
    * Print entire last received message of baseMesaage object
    * @param msg baseMessage object
    */
    void print_last_received_baseMesaage(const baseMessage &msg, bool print_long_payload = false);

    /**
    * Print payload of last received message of derivedMessage object
    * @param msg derivedMessage object
    */
    void print_last_received_derivedMessage_payload(const derivedMessage &msg);

    /**
    * Print entire last received message of derivedMessage object
    * @param msg derivedMessage object
    */
    void print_last_received_derivedMessage(const derivedMessage &msg);
}
#endif //_PRINTMESSAGE_