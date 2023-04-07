# Messaging Challenge
The code herein is intended to solve the following programming challenge problem statement involving creation and simulated transmission of messages with variable payloads over a network.

## Problem Statement

Assumptions:
- All messages are sent and received as a stream of binary data, with each byte containing 8 bits of message content.  Bits are sent/received from MSB to LSB. 
- All message fields are in Network Byte Order.  The code should be agnostic to endianness.
- Please submit your header and source files only, plus the execution result print-out.  Please do not submit your executable, project files, etc.

1.	A hypothetical protocol used to communicate with UAVs has the following common fields:
    Bits	    Field
    16	        Message ID
    8	        Sender ID
    8	        Receiver ID
    32	        Payload Length
    Variable	Payload

    Implement a C++ class that can be used as the base class to develop specific messages later.  This class should have the following features:
    - Initialization of common fields.
    - Access method for each and every common field.
    - A virtual Send function that returns a string containing the message to be sent.
    - A virtual Receive function that accepts a string containing the message received, and populates the values of the common fields.

2.	Implement a C++ class using the base class above to process a message with the following payload:
    Bits	Field
    1	    Lights
    1	    Camera
    6	    Action
    64	    Name

    This class should have the following features:
    - Inherits the base class in Problem #1.
    - Initialization of all payload fields.
    - Access method for each and every payload field.
    - A Send function that returns a string containing the message to be sent.
    - A Receive function that accepts a string containing the message received, and populate the values of the payload fields.

3.	Write a unit test framework to verify your implementation above.  Use your engineering judgment on the scope of your test cases.  
    A text print-out should be produced for the result of each test case.

## Building the Source Code:

Code compiled and built on Win10 with :
g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0
and 
cmake version 3.26.3
  
To build and run:
```
$ cmake -S . -B build -G "MinGW Makefiles"
$ cd build
$ mingw32-make
```

NOTE: A build on a unix system will need to link to <arpa/inet.h>. The CMakeTests.txt must be modified to install the library which contains this header file and defines htons and ntohs methods.

## Example of Expected Output 

NOTE: Some tests use randomly generated values and will be different every run.

After building the source with cmake, run the executable to see example usage of the messages library classes and run tests:
```
$ cd build/apps
$ ./messagingchallenge.exe
```

--- Example usage of baseMessage Class ---
    --- Sent Message ---
    Message  ID: 300
    Sender   ID: 44
    Receiver ID: 6
    Payload length: 40
    Payload: abcde
    --- Received Message ---
    Message  ID: 300
    Sender   ID: 44
    Receiver ID: 6
    Payload length: 40
    Payload: abcde

--- Example usage of derivedMessage Class ---
    --- Sent Message ---
    Message  ID: 65535
    Sender   ID: 23
    Receiver ID: 255
    Payload length: 72
    Payload: ┐abcdefgh
        Payload Details:
            Lights : 1
            Camera : 0
            Action : 63
            Name   : abcdefgh
    --- Received Message ---
    Message  ID: 65535
    Sender   ID: 23
    Receiver ID: 255
    Payload length: 72
    Payload: ┐abcdefgh
    Payload Details:
        Lights : 1
        Camera : 0
        Action : 63
        Name   : abcdefgh

--- Testing Start ---
--- Testing baseMesssage Class ---
 -- Test 1 :: baseMessage send and receive with known inputs --
    Test 1 Run Start
    --- Sent Message ---
    Message  ID: 10
    Sender   ID: 154
    Receiver ID: 6
    Payload length: 40
    Payload: abcde
    --- Received Message ---
    Message  ID: 10
    Sender   ID: 154
    Receiver ID: 6
    Payload length: 40
    Payload: abcde
    Test 1 Run Result :  SUCCESSFUL.
    Test 1 Run Expected Error : None
    Test 1 : PASSED

 -- Test 2 : baseMessage with mesaage_ID > 255 to test endian agnosticity --
    Test 2 Run Start
    --- Sent Message ---
    Message  ID: 300
    Sender   ID: 7
    Receiver ID: 28
    Payload length: 48
    Payload: afgdeg
    --- Received Message ---
    Message  ID: 300
    Sender   ID: 7
    Receiver ID: 28
    Payload length: 48
    Payload: afgdeg
    Test 2 Run Result :  SUCCESSFUL.
    Test 2 Run Expected Error : None
    Test 2 : PASSED

 -- Test 3 : baseMessage send and receive messsage with 0 length --
    Test 3 Run Start
    --- Sent Message ---
    Message  ID: 51
    Sender   ID: 66
    Receiver ID: 222
    Payload length: 0
    Payload:
    --- Received Message ---
    Message  ID: 51
    Sender   ID: 66
    Receiver ID: 222
    Payload length: 0
    Payload:
    Test 3 Run Result :  SUCCESSFUL.
    Test 3 Run Expected Error : None
    Test 3 : PASSED

 -- Test 4 : baseMessage with with payload input longer than specified length --
    Test 4 Run Start
    --- Sent Message ---
    Message  ID: 300
    Sender   ID: 7
    Receiver ID: 28
    Payload length: 48
    Payload: afgdeg
    --- Received Message ---
    Message  ID: 300
    Sender   ID: 7
    Receiver ID: 28
    Payload length: 48
    Payload: afgdeg
    Test 4 Run Result :  SUCCESSFUL.
    Test 4 Run Expected Error : None
    Test 4 : PASSED

 -- Test 5 : baseMessage send and receive with payload length longer than message --
    Test 5 Run Start
    Test 5 Run Result :  FAILURE. Reason: Exception occurred during sending message :Invalid payload length. The payload length is longer than the payload provided.
    Test 5 Run Expected Error : exception
    Test 5 : PASSED

 -- Test 6 : baseMessage send and receive random long message(1E5 bytes) random --
    Test 6 Run Start
    --- Sent Message ---
    Message  ID: 51
    Sender   ID: 66
    Receiver ID: 222
    Payload length: 800000
    Payload: YjLu0asVxyAfJWhmF4ZKKaE1Avx1emTK4L0PquHevZq0YHtj0hGSKDvsTiyslKhfAbU4elfpq8X0IUK6PgYchkZSJmzkayOBPR8p...
    --- Received Message ---
    Message  ID: 51
    Sender   ID: 66
    Receiver ID: 222
    Payload length: 800000
    Payload: YjLu0asVxyAfJWhmF4ZKKaE1Avx1emTK4L0PquHevZq0YHtj0hGSKDvsTiyslKhfAbU4elfpq8X0IUK6PgYchkZSJmzkayOBPR8p...
    Test 6 Run Result :  SUCCESSFUL.
    Test 6 Run Expected Error : None
    Test 6 : PASSED

 -- Test 7 : baseMessage with payload length in fractional bytes --
    Test 7 Run Start
    --- Sent Message ---
    Message  ID: 51
    Sender   ID: 66
    Receiver ID: 222
    Payload length: 1
    Payload: Y
    --- Received Message ---
    Message  ID: 51
    Sender   ID: 66
    Receiver ID: 222
    Payload length: 1
    Payload: Y
    Test 7 Run Result :  SUCCESSFUL.
    Test 7 Run Expected Error : None
    Test 7 : PASSED

 -- Test 8 : baseMessage send and receive short messages( <128 bytes) 100 times with random inputs --
    Test 8 : PASSED

--- Testing derivedMessage Class ---
 -- Test 9 : derivedMessage with known inputs --
    Test 9 Run Start
    --- Sent Message ---
    Message  ID: 1000
    Sender   ID: 253
    Receiver ID: 255
    Payload length: 72
    Payload: ╖abcdefgh
    --- Received Message ---
    Message  ID: 1000
    Sender   ID: 253
    Receiver ID: 255
    Payload length: 72
    Payload: ╖abcdefgh
    Payload Details:
        Lights : 1
        Camera : 0
        Action : 55
        Name   : abcdefgh
    Test 9 Run Result :  SUCCESSFUL.
    Test 9 Run Expected Error : None
    Test 9 : PASSED

 -- Test 10 : derivedMessage with incorrect action --
    Test 10 Run Start
    Test 10 Run Result :  FAILURE. Reason: Exception occurred during sending message :The lights to be sent in the message must be of size 1 byte (0 or 1 in decimal).
    Test 10 Run Expected Error : exception
    Test 10 : PASSED

 -- Test 11 : derivedMessage with incorrect camera --
    Test 11 Run Start
    Test 11 Run Result :  FAILURE. Reason: Exception occurred during sending message :The camera to be sent in the message must be of size 1 byte (0 or 1 in decimal).
    Test 11 Run Expected Error : exception
    Test 11 : PASSED

 -- Test 12 : derivedMessage with incorrect action --
    Test 12 Run Start
    Test 12 Run Result :  FAILURE. Reason: Exception occurred during sending message :The action to be sent in the message must be of size 6 bytes or less (less than 63 in decimal).
    Test 12 Run Expected Error : exception
    Test 12 : PASSED

 -- Test 13 : derivedMessage with incorrect name longer than 8 characters --
    Test 13 Run Start
    Test 13 Run Result :  FAILURE. Reason: Exception occurred during sending message :The action to be sent in the message must be of size 6 bytes or less (less than 63 in decimal).
    Test 13 Run Expected Error : exception
    Test 13 : PASSED

 -- Test 14 : derivedMessage with incorrect name longer than 8 characters --
    Test 14 Run Start
    Test 14 Run Result :  FAILURE. Reason: Exception occurred during sending message :The action to be sent in the message must be of size 6 bytes or less (less than 63 in decimal).
    Test 14 Run Expected Error : exception
    Test 14 : PASSED

 -- Test 15 : derivedMessage send and receive 100 times with random inputs --
    Test 15 : PASSED


TESTS SUMMARY : 15/15 tests passed ---

--- Testing End ---