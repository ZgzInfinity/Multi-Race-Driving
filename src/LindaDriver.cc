/*
 * --------------------------------------------------
 * -- Authors ---------------------------------------
 * -- aeri ------------------------------------------
 * -- ZgzInfinity -----------------------------------
 * --------------------------------------------------
 */


/*
 * Module Linda driver implementation file
 */

#include <iomanip>
#include <iostream>
#include <sstream>

#include "../include/LindaDriver.h"

using namespace std;


const int DEFAULT_BUFLEN = 512;


/**
 * Returns the number of components separated by a comma in the string
 * @param s is a string that represents a tuple with all its components
 *        separated by a comma
 */
int tamanyo(string s)
{
    // Creation of a string flux
    stringstream ss(s);

    // Number of the elements of the tuple
    int dimension = 1;

    // Iterate all the elements of the tuple
    for(unsigned int i = 0; i < s.size(); i++){
        // Check if the current character is a comma
	    if(ss.get() == ',')
		{
		    // Increment the dimension
		    ++dimension;
		}
	}
    return dimension;
}




/**
 * Returns 0 if the initialization of winSock has been correct.
 * Otherwise returns 0 and shows in the screen the error
 * @return
 */
int LD::initWinSock(){
    // Initialize WinSock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(iResult != 0)
	{
	    // Problem initializing winSock
	    cerr << "WSAStartup failed with error: " << iResult << endl;
	    return -1;
	}
	else {
        return 0;
	}
}



/**
 * Returns 0 if the port and the IP address for the socket connection
 * have been solved correctly. Otherwise returns 0 and shows in the
 * screen the error
 * @param ip is the IP address of the Linda server
 * @param port is the port for the socket connection
 * @return
 */
int LD::solvingAdressingPort(const string ip, const string port){
    // Resolve the server address and port
    iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
    if(iResult != 0)
	{
	    // Error while solving address and port for the connection
	    cerr << "getaddrinfo failed with error:" << iResult << endl;
	    WSACleanup();
	    return -1;
	}
	else {
        return 0;
	}
}



/**
 * Returns 0 if the connection to a server using its IP address
 * has been established. Otherwise returns 0
 * @return
 */
int LD::connectToServer(){
    // Attempt to connect to an address until one succeeds
    for(ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
	    // Create a SOCKET for connecting to server
	    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	    if(ConnectSocket == INVALID_SOCKET)
		{
		    cerr << "socket failed with error: " << WSAGetLastError() << endl;
		    WSACleanup();
		    return -1;
		}

	    // Connect to server.
	    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	    if(iResult == SOCKET_ERROR)
		{
		    closesocket(ConnectSocket);
		    ConnectSocket = INVALID_SOCKET;
		    continue;
		}
	    break;
	}
	// Connection established correctly
	return 0;
}



/**
 * Returns 0 if the connection is running.
 * Otherwise returns 0
 */
int LD::checkConnection(){
    // Check if the connection is running or not
    if(ConnectSocket == INVALID_SOCKET)
	{
	    cout << "Unable to connect to server!" << endl;
	    WSACleanup();
	    return -1;
	}
	else {
        return 0;
	}
}


/**
 * Returns 0 if the information has been sent correctly to the
 * server. Otherwise returns -1;
 * @param message is the content to be sent to the server
 */
int LD::sending(const string message){
    // Send an initial buffer
    iResult = send(ConnectSocket, message.c_str(), (int)message.size(), 0);
    if(iResult == SOCKET_ERROR)
	{
	    cerr << "Send failed with error: " << WSAGetLastError() << endl;
	    closesocket(ConnectSocket);
	    WSACleanup();
	    return -1;
	}
	else {
        return 0;
	}
}



/**
 * Receive the information from the server
 * @param recvbuf is the buffer where the information received form the
 *        server has been stored
 * @param recvbuflen is the maximum amount of bytes to receive
 * @param error stores a possible error while the information is being received
 */
void LD::receiving(char recvbuf[], const int recvbuflen, int& error){
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    if (iResult > 0){
        if (strcmp(recvbuf, "ACK") != 0){
            cout << recvbuf << endl;
        }
        error = 0;
    }
    else if (iResult == 0){
        cerr << "Connection closed" << endl;
        error = -1;
    }
    else {
        cerr << "Recv failed with error: " << WSAGetLastError() << endl;
        error = -1;
    }
}


/**
 * Constructor the Linda driver
 * @param ip is the IP direction for establish a connection
 * @param port is the number port for the connection
 */
LD::LD(string ip, string port)
{
    // Default value for the socket
    ConnectSocket = INVALID_SOCKET;

    // Initialize the winSock
    initWinSock();

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Solve IP address and port for the socket connection
    solvingAdressingPort(ip, port);

    // Try to connect to a sever
    connectToServer();

    // Store thr result
    freeaddrinfo(result);

    // Check the status of the connection
    checkConnection();
}



/**
 * Make a PostNote operation if the Linda tuple space
 * @param t is the tuple to be inserted in the tuple space
 */
void LD::postNote(Tuple t)
{
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int error;

    string message = "PN:" + t.to_string();

    // Send the tuple to be postnoted
    sending(message);

    // Receive until the peer closes the connection
    do
	{
	    // Empty and clear the buffer
	    memset(recvbuf, 0, DEFAULT_BUFLEN);

        // Receive the response of the server
        receiving(recvbuf, recvbuflen, error);

	    if(strcmp(recvbuf, "ACK") == 0)
		{
		    break;
		}
	}
    while(iResult > 0);

    // Empty and clear the buffer
    memset(recvbuf, 0, DEFAULT_BUFLEN);

    // Receive the response of the server
    receiving(recvbuf, recvbuflen, error);

    // Send the ACK
    const char *ackbuf = "ACK";
    sending(ackbuf);
};



/**
 * Make a RemoveNote operation if the Linda tuple space
 * @param t is the tuple to be deleted in the tuple space
 */
Tuple LD::removeNote(Tuple t)
{
    string message = "RN:" + t.to_string();
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int error;

    sending(message);

    // Receive until the peer closes the connection
    do
	{
	    // Empty and clear the buffer
	    memset(recvbuf, 0, DEFAULT_BUFLEN);

	    // Receive the response of the server
        receiving(recvbuf, recvbuflen, error);

	    if(strcmp(recvbuf, "ACK") == 0)
		{
		    break;
		}
	}
    while(iResult > 0);

    // Empty and clear the buffer
    memset(recvbuf, 0, DEFAULT_BUFLEN);

    // Receive the response of the server
    receiving(recvbuf, recvbuflen, error);

    // Send the ACK
    const char *ackbuf = "ACK";
    sending(ackbuf);
    Tuple r(tamanyo(recvbuf));
    r.from_string(recvbuf);
    return r;
};



/**
 * Make a ReadNote operation if the Linda tuple space
 * @param t is the tuple to be get if it exists in the tuple space
 */
Tuple LD::readNote(Tuple t)
{
    string message = "ReadN:" + t.to_string();
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int error;

    sending(message);

    // Receive until the peer closes the connection
    do
	{
	    // Empty and clear the buffer
	    memset(recvbuf, 0, DEFAULT_BUFLEN);

	    // Receive the response of the server
        receiving(recvbuf, recvbuflen, error);

	    if(strcmp(recvbuf, "ACK") == 0)
		{
		    break;
		}
	}
    while(iResult > 0);

    // Empty and clear the buffer
    memset(recvbuf, 0, DEFAULT_BUFLEN);

    // Receive the response of the server
    receiving(recvbuf, recvbuflen, error);

    // Send the ACK
    const char *ackbuf = "ACK";
    sending(ackbuf);
    Tuple r(tamanyo(recvbuf));
    r.from_string(recvbuf);
    return r;
};



/**
 * Close the connection between the Linda driver and the Linda server
 */
void LD::stop()
{
    const char *stopbuf = "END OF SERVICE";

    // Send the end of service
    sending(stopbuf);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
}
