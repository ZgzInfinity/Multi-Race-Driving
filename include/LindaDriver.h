/*
 * --------------------------------------------------
 * -- Authors ---------------------------------------
 * -- aeri ------------------------------------------
 * -- ZgzInfinity -----------------------------------
 * --------------------------------------------------
 */


/*
 * Module Linda driver interface file
 */

#ifndef LINDADRIVER_H
#define LINDADRIVER_H

#define _WIN32_WINNT 0x501

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <cstring>
#include <iostream>
#include "Tuple.h"

using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")
#define WIN32_LEAN_AND_MEAN

class LD
{

   // Port of the connection
   int port;

   // IP direction
   string ip;

   // Socket used for the connection
   SOCKET ConnectSocket;

   // Structure to store the windows socket information
   WSADATA wsaData;

   // Structure to store the connection properties
   struct addrinfo *result = NULL, *ptr = NULL, hints;

   // Controller for sending and receiving data
   int iResult;


   /**
     * Returns 0 if the initialization of winSock has been correct.
     * Otherwise returns 0 and shows in the screen the error
     * @return
     */
    int initWinSock();



    /**
     * Returns 0 if the port and the IP address for the socket connection
     * have been solved correctly. Otherwise returns 0 and shows in the
     * screen the error
     * @return
     */
    int solvingAdressingPort(const string ip, const string port);


    /**
     * Returns 0 if the connection to a server using its IP address
     * has been established. Otherwise returns 0
     * @return
     */
    int connectToServer();



    /**
     * Returns 0 if the connection is running.
     * Otherwise returns 0
     */
    int checkConnection();



    /**
     * Returns 0 if the information has been sent correctly to the
     * server. Otherwise returns -1;
     * @param message is the content to be sent to the server
     */
    int sending(const string message);



    /**
     * Receive the information from the server
     * @param recvbuf is the buffer where the information received form the
     *        server has been stored
     * @param recvbuflen is the maximum amount of bytes to receive
     * @param error stores a possible error while the information is being received
     */
    void receiving(char recvbuf[], const int recvbuflen, int& error);


public:



   /**
    * Constructor the Linda driver
    * @param ip is the IP direction for establish a connection
    * @param port is the number port for the connection
    */
   LD(string ip, string port);



   /**
    * Make a PostNote operation if the Linda tuple space
    * @param t is the tuple to be inserted in the tuple space
    */
   void postNote(Tuple t);



   /**
    * Make a RemoveNote operation if the Linda tuple space
    * @param t is the tuple to be deleted in the tuple space
    */
   Tuple removeNote(Tuple t);



   /**
    * Make a ReadNote operation if the Linda tuple space
    * @param t is the tuple to be get if it exists in the tuple space
    */
   Tuple readNote(Tuple t);



   /**
    * Close the connection between the Linda driver and the Linda server
    */
   void stop();

};

#endif
