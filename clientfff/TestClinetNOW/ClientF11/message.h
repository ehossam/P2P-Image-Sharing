#ifndef MESSAGE_H
#define MESSAGE_H

#include <QJsonObject>
#include <string>
#include <vector>
#include "udpsocket.h"

using namespace std;

//#define DEFAULT_SERVER_ADDRESS "10.7.57.222"
#define DEFAULT_SERVER_ADDRESS "127.0.0.1"
#define DEFAULT_SERVER_PORT 78966
#define DEFAULT_SERVER_GET_PORT 13430




class Message
{
public:
    static UDPSocket mySocket;
    static vector<Message> pendingRequests;

    static int RPCIdCounter;

    enum MessageType{
        Request, Reply
    };

    enum ServerOperationType{
        Register,
        Login,
        UpdateStatus
    };

    enum PeerOperationType{
        RequestAllowedImages,
        ViewImage,
        RequestAllImages,
        RequestViews
    };

//variables
public:
    MessageType messageType;
    string message;
    int RPCId;

//functions
public:
    Message(MessageType _messageType, string _message, int _RPCId);


    //peer messages functions
    bool sendToPeer(string ip, int port);
    static void sendRequestAllowedImagesMessage(string myUsername, string peerIP, int peerPort);
    static void sendViewImageMessage(string myUsername, int imageID, string peerIP, int peerPort);
    static void sendRequestImagesMessage(string myUsername, string peerIP, int peerPort);
    static void sendRequestViewsMessage(string myUsername, int imageID, int views, string peerIP, int peerPort);

    static void prepareRequestAllowedImagesMessage(const QJsonObject &json, string ip, int port);
    static void prepareViewImageMessage(const QJsonObject &json, string ip, int port);
    static void prepareRequestImagesMessage(const QJsonObject &json, string ip, int port);
    static void prepareRequestViewsMessage(const QJsonObject &json, string ip, int port);

    //server messages functions
    bool sendToServer();
    static void sendRegisterMessage(string username, string password, bool flag);
    static void sendLoginMessage(string username, string password);
    static void sendUpdateStatusMessage(string username, string password);

    static void deletePendingRequest(int rpcid);
    static bool isRequestPending(int rpcid);

    static void processReceivedMessage(string message, string ip, int port);

    static void handleRegisterReply(const QJsonObject &json, string ip, int port);
    static void handleLoginReply(const QJsonObject &json, string ip, int port);
    static void handleUpdateStatusReply(const QJsonObject &json, string ip, int port);
    static void handleAllowedImagesReply(const QJsonObject &json, string ip, int port);
  static void handleViewImageReply(const QJsonObject &json, string ip, int port);
    static void handleRequestImagesReply(const QJsonObject &json, string ip, int port);


};

#endif // MESSAGE_H
