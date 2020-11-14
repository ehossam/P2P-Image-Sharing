#ifndef MESSAGE_H
#define MESSAGE_H

#include <QJsonObject>
#include <string>
#include "udpsocket.h"
#include "client.h"

using namespace std;


class Message
{
public:
    static UDPSocket mySocket;

    static int RPCIdCounter;

    enum MessageType{
        Request, Reply
    };

    enum ServerOperationType{
        Register,
        Login,
        UpdateStatus
    };

//variables
public:
    MessageType messageType;
    string message;
    int RPCId;

//functions
public:
    Message(MessageType _messageType, string _message, int _RPCId);


    //server messages functions
    void sendToClient(string ip, int port);

    static void processReceivedMessage(string message, string ip, int port);

    static void handleRegisterRequest(const QJsonObject &json, string ip, int port);
    static void handleLoginRequest(const QJsonObject &json, string ip, int port);
    static void handleUpdateStatusRequest(const QJsonObject& json, string ip, int port);
};

#endif // MESSAGE_H
