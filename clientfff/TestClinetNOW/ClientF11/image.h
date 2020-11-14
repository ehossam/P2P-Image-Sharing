#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QByteArray>
#include <QPixmap>
#include <string>
#include <vector>

using namespace std;

struct UserViewsPair
{
    string username;
    int viewQuota;

    UserViewsPair(string _username, int _viewQuota)
    {
        username = _username;
        viewQuota = _viewQuota;
    }
};

struct RemoteImage
{
    int imageID;
    string imageName;
    string owner;
    int viewCount;

    RemoteImage(int _imageID, string _imageName, string _owner, int _viewCount)
    {
        imageID = _imageID;
        imageName = _imageName;
        owner = _owner;
        viewCount = _viewCount;
    }
};

struct ViewsRequest
{
    int imageID;
    string username;
    int viewCount;

    ViewsRequest(int _imageID, string _username, int _viewCount)
    {
        imageID = _imageID;
        username = _username;
        viewCount = _viewCount;
    }
};

class Image
{
public:
    static int imageIDCounter;
    static vector<Image> myImages;
    static vector<RemoteImage> otherImages;
    static vector<RemoteImage> selectedPeerRemoteImages;
    static vector<ViewsRequest> pendingViewsRequests;
    int viewimageflag=0;
    vector<UserViewsPair> userViewsPairs;
    int imageID;
    string imageName;
    QByteArray imageBytes;
    QPixmap imagePixmap;

    Image(string _imageName);

    bool isUserAdded(string username);
    bool canUserViewImage(string username);
    int getUserViewQuota(string username);
    void addUser(string username, int views);
    void updateUserViewCount(string username, int views);
    void removeUser(string username);
    void saveAttributes();
    void loadAttributes();

    QByteArray transformAttributesToJSON();
    void getAttributesFromJSON(QByteArray attributes);

    static void loadMyImages(string username);
    static void uploadImage(QString filepath);
    static void downloadImage(QString imageByteArray, QString imageName, QString usernames);
    static Image* getImageByID(int id);
    static void deleteImagesByOwner(string owner);
    static RemoteImage* getRemoteImage(string imageName, string owner);
    static void deleteRequestIfAlreadyExists(int imageID, string username);
};

#endif // IMAGE_H
