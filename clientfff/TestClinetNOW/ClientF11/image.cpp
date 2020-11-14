#include "image.h"
#include "peer.h"
#include "steg.h"

#include <QDir>
#include <QDirIterator>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QJsonArray>
#include <iostream>
#include <string>
int Image::imageIDCounter = 0;
vector<Image> Image::myImages;
vector<RemoteImage> Image::otherImages;
vector<RemoteImage> Image::selectedPeerRemoteImages;
vector<ViewsRequest> Image::pendingViewsRequests;

Image::Image(string _imageName)
{
    imageID = ++imageIDCounter;
    imageName = _imageName;
}


bool Image::isUserAdded(string username)
{
    for(int i = 0; i < userViewsPairs.size(); i++)
    {
        if(userViewsPairs.at(i).username == username)
        {
            return true;
        }
    }

    return false;
}


bool Image::canUserViewImage(string username)
{
    for(int i = 0; i < userViewsPairs.size(); i++)
    {
        if(userViewsPairs.at(i).username == username && userViewsPairs.at(i).viewQuota > 0)
        {
            return true;
        }
    }

    return false;
}


int Image::getUserViewQuota(string username)
{
    for(int i = 0; i < userViewsPairs.size(); i++)
    {
        if(userViewsPairs.at(i).username == username)
        {
            return userViewsPairs.at(i).viewQuota;
        }
    }
    return -1;
}


void Image::addUser(string username, int views)
{
    if(isUserAdded(username))
        return;


    userViewsPairs.push_back(UserViewsPair(username, views));

    saveAttributes();
}


void Image::updateUserViewCount(string username, int views)
{
    for(int i = 0; i < userViewsPairs.size(); i++)
    {
        if(userViewsPairs.at(i).username == username)
        {
            if(views == -1)
            {
                int tempViewQuota = userViewsPairs.at(i).viewQuota - 1;
                if(tempViewQuota < 0)
                    userViewsPairs.at(i).viewQuota = 0;
                 else
                    userViewsPairs.at(i).viewQuota = tempViewQuota;
            }
            else
            {
                userViewsPairs.at(i).viewQuota = views;
            }

            saveAttributes();

            break;
        }
    }
}


void Image::removeUser(string username)
{
    int foundIndex = -1;
    for(int i = 0; i < userViewsPairs.size(); i++)
    {
        if(userViewsPairs.at(i).username == username)
        {
            foundIndex = i;
        }
    }

    if(foundIndex != -1)
    {
        userViewsPairs.erase(userViewsPairs.begin() + foundIndex);

        saveAttributes();
    }
}


void Image::loadMyImages(string username)
{
    QString absolutePath = QDir(QString::fromStdString(username) + "-images").absolutePath();
    //cout << absolutePath.toStdString();
    if(!QDir(absolutePath).exists())
    {
        QDir().mkdir(absolutePath);
    }

    myImages.clear();
    imageIDCounter = 0;

    QDirIterator it(absolutePath, QStringList() << "*.jpg", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QFileInfo imageFileInfo(it.next());
        string name = imageFileInfo.fileName().toStdString();

        QFile* imageFile = new QFile(imageFileInfo.absoluteFilePath());
        imageFile->open(QIODevice::ReadOnly);

        Image img(name);
        img.imageBytes = imageFile->readAll();
        img.imagePixmap = QPixmap(imageFileInfo.absoluteFilePath());

        img.loadAttributes();

        myImages.push_back(img);
    }
}


void Image::uploadImage(QString filepath)
{
    QFileInfo imageFileInfo(filepath);

    QString newPath = QDir(QString::fromStdString(Peer::myUsername) + "-images").absolutePath();
    newPath += "/" + imageFileInfo.fileName();

    QFile::copy(filepath, newPath);
}


void Image::downloadImage( QString imageByteArray, QString imageName, QString usernames)
{

    cout<<"DOWNLOADDINGGGGGGGG"<<endl;
    QByteArray imageBytes = QByteArray::fromStdString(imageByteArray.toStdString());
    imageBytes = QByteArray::fromBase64(imageBytes);
    QPixmap pic;

    pic.loadFromData(imageBytes,"JPG");

    QString newPath = QDir(usernames + "-images").absolutePath();
    QString tempPath= newPath;
    tempPath+= "/";
       newPath += "/"+ imageName+(".jpg");

    QFile file(newPath);
    file.open(QIODevice::WriteOnly);

    QDataStream out(&file);
    pic.save(&file, "JPG");
    out<<pic;
   // cout<<imageByteArray.toStdString()<<endl;
    string command_steg;
     //command_steg =    "steghide embed -ef" + imageName.toStdString() + "-cf default.jpg -p 0 -f";

     command_steg = "steghide embed -ef ";
     command_steg += newPath.toStdString();
     command_steg+= " -cf " + tempPath.toStdString()+"default.jpg ";
     command_steg+="-sf "+tempPath.toStdString()+"newImage.jpg -p 0 -f";
     cout<<command_steg<<endl;
     system((char*)(command_steg.c_str()));
}

Image* Image::getImageByID(int id)
{
    for(int i = 0; i < myImages.size(); i++)
    {
        if(myImages.at(i).imageID == id)
        {
            return &myImages.at(i);
        }
    }

    return NULL;
}


void Image::saveAttributes()
{
    QByteArray attributesJSON = transformAttributesToJSON();

    QString path = QDir(QString::fromStdString(Peer::myUsername) + "-images").absolutePath();
    path += "/" + QString::fromStdString(imageName);

    Steg::embedStringIntoImage(path.toStdString(), QString(attributesJSON).toStdString(), Peer::myPassword);
}


void Image::loadAttributes()
{
    QString path = QDir(QString::fromStdString(Peer::myUsername) + "-images").absolutePath();
    path += "/" + QString::fromStdString(imageName);

    string attributesText = Steg::restoreStringFromImage(path.toStdString(), Peer::myPassword);

    if(attributesText.size() > 0)
        getAttributesFromJSON(QByteArray::fromStdString(attributesText));
}


QByteArray Image::transformAttributesToJSON()
{
    QJsonObject json;
    json["username"] = QString::fromStdString(Peer::myUsername);
    json["password"] = QString::fromStdString(Peer::myPassword);


    QJsonArray userViewPairArray;
    for(int i = 0; i < userViewsPairs.size(); i++)
    {
        QJsonObject userViewObject;
        userViewObject["username"] = QString::fromStdString(userViewsPairs.at(i).username);
        userViewObject["views"] = userViewsPairs.at(i).viewQuota;

        userViewPairArray.append(userViewObject);

    }
    json["userViewsPairs"] = userViewPairArray;


    QJsonDocument doc(json);

    return doc.toJson().toBase64();
}


void Image::getAttributesFromJSON(QByteArray attributes)
{
    attributes = QByteArray::fromBase64(attributes);

    QJsonDocument doc(QJsonDocument::fromJson(attributes));
    QJsonObject json = doc.object();

    QString username, password;

    if(json.contains("username") && json["username"].isString())
        username = json["username"].toString();

    if(json.contains("password") && json["password"].isString())
        password = json["password"].toString();

    if(username.toStdString() != Peer::myUsername && password.toStdString() != Peer::myPassword)
        return;

    if (json.contains("userViewsPairs") && json["userViewsPairs"].isArray())
    {
        QJsonArray userViewPairArray = json["userViewsPairs"].toArray();
        userViewsPairs.clear();

        for (int userViewIndex = 0; userViewIndex < userViewPairArray.size(); ++userViewIndex)
        {
            QJsonObject userViewObject = userViewPairArray[userViewIndex].toObject();

            string username;
            int views;

            if(userViewObject.contains("username") && userViewObject["username"].isString())
                username = userViewObject["username"].toString().toStdString();

            if(userViewObject.contains("views") && userViewObject["views"].isDouble())
                views = userViewObject["views"].toInt();

            userViewsPairs.push_back(UserViewsPair(username, views));
        }
    }
}


void Image::deleteImagesByOwner(string owner)
{
    if(otherImages.empty() == false)
    {
        for(int i = otherImages.size() - 1; i >= 0; i--)
        {
            if(otherImages.at(i).owner == owner)
            {
                otherImages.erase( otherImages.begin() + i );
            }
        }
    }
}


RemoteImage* Image::getRemoteImage(string imageName, string owner)
{
    for(int i = 0; i < otherImages.size(); i++)
    {
        if(otherImages.at(i).imageName == imageName && otherImages.at(i).owner == owner)
        {
            return &otherImages.at(i);
        }
    }

    return NULL;
}

void Image::deleteRequestIfAlreadyExists(int imageID, string username)
{
    for(int i = pendingViewsRequests.size() - 1; i >= 0; i--)
    {
        if(pendingViewsRequests.at(i).imageID == imageID
                &&pendingViewsRequests.at(i).username == username)
        {
            pendingViewsRequests.erase( pendingViewsRequests.begin() + i );
        }
    }
}
