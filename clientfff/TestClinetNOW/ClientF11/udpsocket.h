#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <netdb.h>
#include <iostream>
#include <pthread.h>

using namespace std;

class UDPSocket
{
public:
    int sock;
    sockaddr_in myAddr;
    int myPort;
    pthread_t listenerThread;
public:
    UDPSocket();
    UDPSocket(int port);
    bool initializeSocket();
    bool sendMessage(string message, string destAddress, int destPort);
    static void* listener(void* socket);
    ~UDPSocket();
};

#endif // UDPSOCKET_H
