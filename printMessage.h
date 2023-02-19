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

void print_sent_baseMessage(const ustring8_t &net_msgin);
void print_sent_derivedMessage(const ustring8_t &net_msgin);
void print_last_received_baseMesaage(const baseMessage &msg);
void print_last_received_derivedMessage_payload(const derivedMessage &msg);
void print_last_received_derivedMessage(const derivedMessage &msg);

#endif //_PRINTMESSAGE_