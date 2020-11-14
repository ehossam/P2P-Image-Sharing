#include "udpsocket.h"
#include "message.h"

#define BUFFER_SIZE 1000000
int  waittime = 3; // initially client will wait 3 seconds to receive echo from the server
struct timeval timeout={waittime,0};
int counterrrr=0;
bool tried=false;

UDPSocket::UDPSocket()
{

}

UDPSocket::UDPSocket(int port)
{
    myPort = port;
    initializeSocket();
}

bool UDPSocket::initializeSocket()
{
    memset(&myAddr, 0, sizeof(myAddr));

    myAddr.sin_family = AF_INET;
    myAddr.sin_addr.s_addr = INADDR_ANY;
    myAddr.sin_port = htons(myPort);

    if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        cout << "Failed to create socket." << endl;
        return false;
    }

    if(bind(sock, (struct sockaddr*) &myAddr, sizeof(myAddr)) < 0)
    {
        cout << "Failed to bind socket." << endl;
        return false;
    }

    if(pthread_create(&listenerThread, NULL, UDPSocket::listener, (void*)&sock) < 0)
    {
        cout << "Failed to create thread" << endl;
        return false;
    }

    return true;
}


bool UDPSocket::sendMessage(string message, string destAddress, int destPort)
{
    sockaddr_in destAddr;
    if (destAddress == DEFAULT_SERVER_ADDRESS)
{        tried= true;
    }
    memset(&destAddr, 0, sizeof(destAddr));
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(destPort);
    inet_pton(AF_INET, destAddress.c_str(), &destAddr.sin_addr.s_addr);
    cout << "Updates"<<endl;
    ssize_t count = sendto(sock, message.c_str(), message.size(), 0, (struct sockaddr*)&destAddr, sizeof(destAddr));

    if(count != message.size())
    {

        cout << "Message: '" << message << "' has failed to send." << endl;
        cout << message.size() << endl;
        return false;
    }
    return true;
}


void* UDPSocket::listener(void* args)
{
    //Get the socket descriptor
    int sock = *(int*)args;
    int status = 0;

    char buffer[BUFFER_SIZE];
    struct sockaddr_in srcAddress;
    socklen_t srcAddressLength = sizeof(srcAddress);
    ssize_t count;

    while(true)
    {

    setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(struct timeval));

    if((count = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&srcAddress, &srcAddressLength)) <0){
           counterrrr++;
           if(tried){
           if(counterrrr <= 10){
            cerr << "TTL Exceeded. Trying againn \n";
            // waittime += 2; // Failed to receive reply, increment waiting time
        }
           else{
               cerr << "Timeout Error !!\n";
               counterrrr=0;
               tried=false;
           }
           }
        }
        if(count == sizeof(buffer))
        {
            waittime = 3; // Received echo reply, so reset waiting time to 0
            cout << "Datagram too large for buffer." << endl;
            continue;
        }
        else if(count > 0)
        {
            waittime = 3; // Received echo reply, so reset waiting time to 0
            string ip(inet_ntoa(srcAddress.sin_addr));
            int port = ntohs(srcAddress.sin_port);
            string message(buffer, count);
            Message::processReceivedMessage(message, ip, port);
        }
    }

    return 0;
}

UDPSocket::~UDPSocket()
{
    close(sock);
}


