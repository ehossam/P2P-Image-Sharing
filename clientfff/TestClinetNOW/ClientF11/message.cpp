#include "message.h"

#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>
#include <QFileDialog>
#include <string>
#include <iostream>

#include "gui.h"
#include "peer.h"
#include "image.h"

int Message::RPCIdCounter = 0;
UDPSocket Message::mySocket = UDPSocket();
vector<Message> Message::pendingRequests;

Message::Message(MessageType _messageType, string _message, int _RPCId)
{
    messageType = _messageType;
    message = _message;
    RPCId = _RPCId;
}

bool Message::sendToServer()
{
    return mySocket.sendMessage(message, DEFAULT_SERVER_ADDRESS, DEFAULT_SERVER_PORT);
}

bool Message::sendToPeer(string ip, int port)
{
    return mySocket.sendMessage(message, ip, port);
}


void Message::sendRegisterMessage(string username, string password, bool flag)
{
    int id = ++RPCIdCounter;

    QJsonObject json;
    json["messageType"] = MessageType::Request;
    json["RPCId"] = id;
    json["username"] = QString::fromStdString(username);
    json["password"] = QString::fromStdString(password);
    if(flag == 1)
    {
        json["operationType"] = ServerOperationType::Login;
        QJsonDocument marshallDocument(json);
        string loginMessage = marshallDocument.toJson().toBase64().toStdString();

        Message m(MessageType::Request, loginMessage, id);

        m.sendToServer();

        pendingRequests.push_back(m);

        Peer::myUsername = username;
        Peer::myPassword = password;
    }
    else if (flag == 0)
    {
        flag = -1;
        json["operationType"] = ServerOperationType::Register;
        QJsonDocument marshallDocument(json);
        string registerMessage = marshallDocument.toJson().toBase64().toStdString();

        Message m(MessageType::Request, registerMessage, id);

        m.sendToServer();

        pendingRequests.push_back(m);

    }

}

/*
void Message::sendLoginMessage(string username, string password)
{
    int id = ++RPCIdCounter;

    QJsonObject json;
    json["messageType"] = MessageType::Request;
    json["operationType"] = ServerOperationType::Login;
    json["RPCId"] = id;
    json["username"] = QString::fromStdString(username);
    json["password"] = QString::fromStdString(password);

    QJsonDocument marshallDocument(json);
    string loginMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Request, loginMessage, id);

    cout << m.sendToServer();

    pendingRequests.push_back(m);

    Peer::myUsername = username;
    Peer::myPassword = password;
}
*/

void Message::sendUpdateStatusMessage(string username, string password)
{
    int id = ++RPCIdCounter;

    QJsonObject json;
    json["messageType"] = MessageType::Request;
    json["operationType"] = ServerOperationType::UpdateStatus;
    json["RPCId"] = id;
    json["username"] = QString::fromStdString(username);
    json["password"] = QString::fromStdString(password);

    QJsonDocument marshallDocument(json);
    string updateStatusMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Request, updateStatusMessage, id);

    m.sendToServer();

    pendingRequests.push_back(m);
}


void Message::sendRequestAllowedImagesMessage(string myUsername, string peerIP, int peerPort)
{
    int id = ++RPCIdCounter;

    QJsonObject json;
    json["messageType"] = MessageType::Request;
    json["operationType"] = PeerOperationType::RequestAllowedImages;
    json["RPCId"] = id;
    json["username"] = QString::fromStdString(myUsername);

    QJsonDocument marshallDocument(json);
    string requestImagesMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Request, requestImagesMessage, id);

    m.sendToPeer(peerIP, peerPort);

    pendingRequests.push_back(m);
}

void Message::sendRequestImagesMessage(string myUsername, string peerIP, int peerPort)
{
    int id = ++RPCIdCounter;
    QJsonObject json;
    json["messageType"] = MessageType::Request;
    json["operationType"] = PeerOperationType::RequestAllImages;
    json["RPCId"] = id;
    json["username"] = QString::fromStdString(myUsername);

    QJsonDocument marshallDocument(json);
    string requestImagesMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Request, requestImagesMessage, id);

    m.sendToPeer(peerIP, peerPort);

    pendingRequests.push_back(m);
}


void Message::sendViewImageMessage(string myUsername, int imageID, string peerIP, int peerPort)
{
    int id = ++RPCIdCounter;

    QJsonObject json;
    json["messageType"] = MessageType::Request;
    json["operationType"] = PeerOperationType::ViewImage;
    json["RPCId"] = id;
    json["username"] = QString::fromStdString(myUsername);
    json["imageID"] = imageID;

    QJsonDocument marshallDocument(json);
    string viewImageMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Request, viewImageMessage, id);

    m.sendToPeer(peerIP, peerPort);

    pendingRequests.push_back(m);
}


void Message::sendRequestViewsMessage(string myUsername, int imageID, int views, string peerIP, int peerPort)
{
    int id = ++RPCIdCounter;

    QJsonObject json;
    json["messageType"] = MessageType::Request;
    json["operationType"] = PeerOperationType::RequestViews;
    json["RPCId"] = id;
    json["username"] = QString::fromStdString(myUsername);
    json["imageID"] = imageID;
    json["views"] = views;

    QJsonDocument marshallDocument(json);
    string requestViewImageMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Request, requestViewImageMessage, id);

    m.sendToPeer(peerIP, peerPort);

    pendingRequests.push_back(m);
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
            PeerOperationType operationType;
            if(json.contains("operationType") && json["operationType"].isDouble())
            {
                operationType = static_cast<PeerOperationType>(json["operationType"].toInt());

                switch(operationType)
                {
                case RequestAllowedImages:
                {
                    prepareRequestAllowedImagesMessage(json, ip, port);
                    break;
                }
                case ViewImage:
                {
                    prepareViewImageMessage(json, ip, port);
                    break;
                }
                case RequestAllImages:
                {
                    prepareRequestImagesMessage(json, ip, port);
                    break;
                }
                case RequestViews:
                {
                    prepareRequestViewsMessage(json, ip, port);
                    break;
                }
                default:
                    break;
                }

            }
        }
        else if(type == MessageType::Reply)
        {
            //reply from server
            if(port == DEFAULT_SERVER_GET_PORT)
            {

                ServerOperationType operationType;
                if(json.contains("operationType") && json["operationType"].isDouble())
                {
                    operationType = static_cast<ServerOperationType>(json["operationType"].toInt());

                    switch(operationType)
                    {
                    case Register:
                    {

                        handleRegisterReply(json, ip, port);
                        break;
                    }
                    case Login:
                    {

                        handleLoginReply(json, ip, port);
                        break;
                    }
                    case UpdateStatus:
                    {
                        handleUpdateStatusReply(json, ip, port);
                        break;
                    }
                    default:
                        break;
                    }
                }
            }//reply from peer
            else
            {

                PeerOperationType operationType;
                if(json.contains("operationType") && json["operationType"].isDouble())
                {
                    operationType = static_cast<PeerOperationType>(json["operationType"].toInt());

                    switch(operationType)
                    {
                    case RequestAllowedImages:
                    {
                        handleAllowedImagesReply(json, ip, port);
                        break;
                    }
                    case ViewImage:
                    {
                        handleViewImageReply(json, ip, port);
                        break;
                    }
                    case RequestAllImages:
                    {
                        handleRequestImagesReply(json, ip, port);
                        break;
                    }
                    default:
                        break;
                    }

                }
            }
        }
    }
}

bool Message::isRequestPending(int rpcid)
{
    for(int i = 0; i < pendingRequests.size(); i++)
    {
        if(pendingRequests.at(i).RPCId == rpcid)
        {
            return true;
        }
    }
    return false;
}

void Message::deletePendingRequest(int rpcid)
{
    int foundIndex = -1;
    for(int i = 0; i < pendingRequests.size(); i++)
    {
        if(pendingRequests.at(i).RPCId == rpcid)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex != -1)
    {
        pendingRequests.erase(pendingRequests.begin() + foundIndex);
    }
}


void Message::prepareRequestAllowedImagesMessage(const QJsonObject &json, string ip, int port)
{
    QString username;
    int rpcid = -1;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(username.size() <= 0 || rpcid == -1)
        return;

    QJsonObject jsonToSend;
    jsonToSend["messageType"] = MessageType::Reply;
    jsonToSend["operationType"] = PeerOperationType::RequestAllowedImages;
    jsonToSend["RPCId"] = rpcid;
    jsonToSend["owner"] = QString::fromStdString(Peer::myUsername);

    QJsonArray imageArray;
    for(int i = 0; i < Image::myImages.size(); i++)
    {
        Image *image = &Image::myImages.at(i);
        if(image->canUserViewImage(username.toStdString()))
        {
            QJsonObject imageObject;
            imageObject["imageID"] = image->imageID;
            imageObject["owner"] = QString::fromStdString(Peer::myUsername);
            imageObject["imageName"] = QString::fromStdString(image->imageName);
            imageObject["views"] = image->getUserViewQuota(username.toStdString());

            imageArray.append(imageObject);
                image->viewimageflag=1;
        }
        else
        {
         image->viewimageflag=0;
        }

    }
    jsonToSend["images"] = imageArray;


    QJsonDocument marshallDocument(jsonToSend);
    string allowedImagesMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Reply, allowedImagesMessage, rpcid);

    m.sendToPeer(ip, port);
}

void Message::prepareRequestImagesMessage(const QJsonObject &json, string ip, int port)
{
    QString username;
    int rpcid = -1;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(username.size() <= 0 || rpcid == -1)
        return;

    QJsonObject jsonToSend;
    jsonToSend["messageType"] = MessageType::Reply;
    jsonToSend["operationType"] = PeerOperationType::RequestAllImages;
    jsonToSend["RPCId"] = rpcid;
    jsonToSend["owner"] = QString::fromStdString(Peer::myUsername);

    QJsonArray imageArray;
    for(int i = 0; i < Image::myImages.size(); i++)
    {
        Image *image = &Image::myImages.at(i);
        QJsonObject imageObject;
        imageObject["imageID"] = image->imageID;
        imageObject["owner"] = QString::fromStdString(Peer::myUsername);
        imageObject["imageName"] = QString::fromStdString(image->imageName);
        imageObject["views"] = image->getUserViewQuota(username.toStdString());

        imageArray.append(imageObject);
    }
    jsonToSend["images"] = imageArray;


    QJsonDocument marshallDocument(jsonToSend);
    string allowedImagesMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Reply, allowedImagesMessage, rpcid);

    m.sendToPeer(ip, port);
}


void Message::prepareViewImageMessage(const QJsonObject &json, string ip, int port)
{
    QString username;
    int imageID;
    int rpcid = -1;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(json.contains("imageID") && json["imageID"].isDouble())
        imageID = json["imageID"].toInt();

    if(username.size() <= 0 || rpcid == -1)
        return;

    QJsonObject jsonToSend;
    jsonToSend["messageType"] = MessageType::Reply;
    jsonToSend["operationType"] = PeerOperationType::ViewImage;
    jsonToSend["RPCId"] = rpcid;

    Image* image = Image::getImageByID(imageID);

    if(!image)
    {
        return;
    }
/*
    if(!image->canUserViewImage(username.toStdString()))
    {
        return;
    }
*/

    jsonToSend["imageByteArray"] = QString::fromStdString(image->imageBytes.toBase64().toStdString());
    jsonToSend["username"]= QString::fromStdString(Peer::myUsername);
    jsonToSend["imageName"]=QString::number(imageID);

    QJsonDocument marshallDocument(jsonToSend);
    string viewImageMessage = marshallDocument.toJson().toBase64().toStdString();

    Message m(MessageType::Reply, viewImageMessage, rpcid);

    if(m.sendToPeer(ip, port))
    {
        image->updateUserViewCount(username.toStdString(), -1);
    }
}

void Message::prepareRequestViewsMessage(const QJsonObject &json, string ip, int port)
{
    QString username;
    int imageID, views;
    int rpcid = -1;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(json.contains("imageID") && json["imageID"].isDouble())
        imageID = json["imageID"].toInt();

    if(json.contains("views") && json["views"].isDouble())
        views = json["views"].toInt();

    if(username.size() <= 0 || rpcid == -1)
        return;


    Image::deleteRequestIfAlreadyExists(imageID, username.toStdString());

    ViewsRequest rq(imageID, username.toStdString(), views);
    Image::pendingViewsRequests.push_back(rq);
}



void Message::handleRegisterReply(const QJsonObject &json, string ip, int port)
{
    bool success = false;
    int rpcid = -1;

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(rpcid == -1)
        return;

    if(!isRequestPending(rpcid))
        return;


    if(json.contains("Success") && json["Success"].isBool())
        success = json["Success"].toBool();

    deletePendingRequest(rpcid);

    GUI::getInstance().viewRegisterResult(success);
}


void Message::handleLoginReply(const QJsonObject &json, string ip, int port)
{

    bool success = false;
    int rpcid = -1;

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(rpcid == -1)
        return;

    if(!isRequestPending(rpcid))
        return;


    if(json.contains("Success") && json["Success"].isBool())
        success = json["Success"].toBool();

    deletePendingRequest(rpcid);

    GUI::getInstance().viewLoginResult(success);
}

void Message::handleAllowedImagesReply(const QJsonObject &json, string ip, int port)
{
    int rpcid = -1;

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(rpcid == -1)
        return;

    if(!isRequestPending(rpcid))
        return;

    QString owner;

    if(json.contains("owner") && json["owner"].isString())
        owner = json["owner"].toString();

    if (json.contains("images") && json["images"].isArray())
    {
        QJsonArray imageArray = json["images"].toArray();

        bool deleted = false;

        if(imageArray.empty())
        {
            Image::deleteImagesByOwner(owner.toStdString());
        }

        for (int imageIndex = 0; imageIndex < imageArray.size(); ++imageIndex)
        {
            QJsonObject imageObject = imageArray[imageIndex].toObject();

            string imageName, owner;
            int imageID, views;

            if(imageObject.contains("imageName") && imageObject["imageName"].isString())
                imageName = imageObject["imageName"].toString().toStdString();

            if(imageObject.contains("owner") && imageObject["owner"].isString())
                owner = imageObject["owner"].toString().toStdString();

            if(imageObject.contains("imageID") && imageObject["imageID"].isDouble())
                imageID = imageObject["imageID"].toInt();

            if(imageObject.contains("views") && imageObject["views"].isDouble())
                views = imageObject["views"].toInt();

            if(!deleted)
            {
                Image::deleteImagesByOwner(owner);
                deleted = true;
            }

            RemoteImage ri(imageID, imageName, owner, views);
            Image::otherImages.push_back(ri);
        }
    }

    deletePendingRequest(rpcid);
}

void Message::handleRequestImagesReply(const QJsonObject &json, string ip, int port)
{
    int rpcid = -1;

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(rpcid == -1)
        return;

    if(!isRequestPending(rpcid))
        return;

    QString owner;

    if(json.contains("owner") && json["owner"].isString())
        owner = json["owner"].toString();

    if (json.contains("images") && json["images"].isArray())
    {
        QJsonArray imageArray = json["images"].toArray();

        Image::selectedPeerRemoteImages.clear();
        for (int imageIndex = 0; imageIndex < imageArray.size(); ++imageIndex)
        {
            QJsonObject imageObject = imageArray[imageIndex].toObject();

            string imageName, owner;
            int imageID, views;

            if(imageObject.contains("imageName") && imageObject["imageName"].isString())
                imageName = imageObject["imageName"].toString().toStdString();

            if(imageObject.contains("owner") && imageObject["owner"].isString())
                owner = imageObject["owner"].toString().toStdString();

            if(imageObject.contains("imageID") && imageObject["imageID"].isDouble())
                imageID = imageObject["imageID"].toInt();

            if(imageObject.contains("views") && imageObject["views"].isDouble())
                views = imageObject["views"].toInt();

            RemoteImage ri(imageID, imageName, owner, views);
            Image::selectedPeerRemoteImages.push_back(ri);
        }
    }

    deletePendingRequest(rpcid);
}


void Message::handleViewImageReply(const QJsonObject &json, string ip, int port)
{
    int rpcid = -1;

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(rpcid == -1)
        return;

    if(!isRequestPending(rpcid))
        return;


string usernames;

    if(json.contains("username") && json["username"].isString())
        usernames = json["username"].toString().toStdString();


    QString imageByteArray;
    string imageName;

    if(json.contains("imageByteArray") && json["imageByteArray"].isString())
        imageByteArray = json["imageByteArray"].toString();

    if(json.contains("imageName") && json["imageName"].isString())
        imageName = json["imageName"].toString().toStdString();

    Image::downloadImage(imageByteArray, QString::fromStdString(imageName), QString::fromStdString(usernames));

    Image::loadMyImages(usernames);

//    MainWindow::viewMyImages();

    GUI::getInstance().mainWindow->viewRemoteImage(imageByteArray);

    deletePendingRequest(rpcid);
}


void Message::handleUpdateStatusReply(const QJsonObject &json, string ip, int port)
{
    int rpcid = -1;

    if(json.contains("RPCId") && json["RPCId"].isDouble())
        rpcid = json["RPCId"].toInt();

    if(rpcid == -1)
        return;

    if(!isRequestPending(rpcid))
        return;


    if (json.contains("peers") && json["peers"].isArray())
    {
        QJsonArray peerArray = json["peers"].toArray();
        Peer::onlinePeers.clear();
        for (int peerIndex = 0; peerIndex < peerArray.size(); ++peerIndex)
        {
            QJsonObject peerObject = peerArray[peerIndex].toObject();

            string username, ip;
            int port;

            if(peerObject.contains("username") && peerObject["username"].isString())
                username = peerObject["username"].toString().toStdString();

            if(peerObject.contains("ip") && peerObject["ip"].isString())
                ip = peerObject["ip"].toString().toStdString();

            if(peerObject.contains("port") && peerObject["port"].isDouble())
                port = peerObject["port"].toInt();

            Peer::onlinePeers.push_back(Peer(username, ip, port));
        }
    }

    deletePendingRequest(rpcid);
}
