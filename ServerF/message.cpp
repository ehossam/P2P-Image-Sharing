#include "message.h"

#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>

int Message::RPCIdCounter = 0;
UDPSocket Message::mySocket = UDPSocket();

Message::Message(MessageType _messageType, string _message, int _RPCId)
{
    messageType = _messageType;
    message = _message;
    RPCId = _RPCId;
}

void Message::sendToClient(string ip, int port)
{
    mySocket.sendMessage(message, ip, port);
}


void Message::processReceivedMessage(string message, string ip, int port)
{

    QByteArray jsonByteArray = QByteArray::fromStdString(message);
    jsonByteArray = QByteArray::fromBase64(jsonByteArray);

    QJsonDocument unmarshalledDocument(QJsonDocument::fromJson(jsonByteArray));
    QJsonObject json = unmarshalledDocument.object();

    MessageType type;
    if(json.contains("messageType") && json["messageType"].isDouble())
    {
        type = static_cast<MessageType>(json["messageType"].toInt());

        if(type == MessageType::Request)
        {
            ServerOperationType operationType;
            if(json.contains("operationType") && json["operationType"].isDouble())
            {
                operationType = static_cast<ServerOperationType>(json["operationType"].toInt());

                switch(operationType)
                {
                case Register:
                {

                    handleRegisterRequest(json, ip, port);
                    break;
                }
                case Login:
                {
                    handleLoginRequest(json, ip, port);
                    break;
                }
                case UpdateStatus:
                {
                    handleUpdateStatusRequest(json, ip, port);
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
}


void Message::handleRegisterRequest(const QJsonObject &json, string ip, int port)
{

    QString username, password;
    int rpcid = -1;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("password") && json["password"].isString())
        password = json["password"].toString();

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    bool success = false;
    if(username.size() > 0 && password.size() > 0 && rpcid != -1)
    {
        success = Client::registerUser(username.toStdString(), password.toStdString());
        cout << "messgae received" << endl;
    }


    QJsonObject jsonToSend;
    jsonToSend["messageType"] = MessageType::Reply;
    jsonToSend["operationType"] = ServerOperationType::Register;
    jsonToSend["RPCId"] = rpcid;
    jsonToSend["Success"] = success;

    QJsonDocument marshallDocument(jsonToSend);
    string registerMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Reply, registerMessage, rpcid);

    m.sendToClient(ip, port);
}


void Message::handleLoginRequest(const QJsonObject &json, string ip, int port)
{
    cout << "Handling Login"<<endl;
    QString username, password;
    int rpcid = -1;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("password") && json["password"].isString())
        password = json["password"].toString();

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    bool success = false;
    if(username.size() > 0 && password.size() > 0 && rpcid != -1)
    {
        success = Client::loginUser(username.toStdString(), password.toStdString(), ip, port);
    }


    QJsonObject jsonToSend;
    jsonToSend["messageType"] = MessageType::Reply;
    jsonToSend["operationType"] = ServerOperationType::Login;
    jsonToSend["RPCId"] = rpcid;
    jsonToSend["Success"] = success;

    QJsonDocument marshallDocument(jsonToSend);
    string loginMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Reply, loginMessage, rpcid);

    m.sendToClient(ip, port);
}


void Message::handleUpdateStatusRequest(const QJsonObject &json, string ip, int port)
{
    QString username, password;
    int rpcid = -1;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("password") && json["password"].isString())
        password = json["password"].toString();

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    bool success = false;
    if(username.size() > 0 && password.size() > 0 && rpcid != -1)
    {
        // will auto check if already logged in then updates timeout
        success = Client::loginUser(username.toStdString(), password.toStdString(), ip, port);
    }

    QJsonObject jsonToSend;
    jsonToSend["messageType"] = MessageType::Reply;
    jsonToSend["operationType"] = ServerOperationType::UpdateStatus;
    jsonToSend["RPCId"] = rpcid;

    QJsonArray peerArray;
    for(int i = 0; i < Client::loggedInClients.size(); i++)
    {
        if(Client::loggedInClients.at(i).username != username.toStdString())
        {
            QJsonObject peerObject;
            peerObject["username"] = QString::fromStdString(Client::loggedInClients.at(i).username);
            peerObject["ip"] = QString::fromStdString(Client::loggedInClients.at(i).IPAddress);
            peerObject["port"] = Client::loggedInClients.at(i).port;

            peerArray.append(peerObject);
        }
    }
    jsonToSend["peers"] = peerArray;


    QJsonDocument marshallDocument(jsonToSend);
    string updateMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Reply, updateMessage, rpcid);

    m.sendToClient(ip, port);
}
