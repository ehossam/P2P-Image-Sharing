#include "timermanager.h"
#include "message.h"
#include "peer.h"
#include "gui.h"

TimerManager::TimerManager(QObject *parent) : QObject(parent)
{
    updateStatusOnServerTimer = new QTimer(this);
    updateRemoteImagesTimer = new QTimer(this);
    QObject::connect(updateStatusOnServerTimer, SIGNAL(timeout()), this, SLOT(updateStatusOnServer()));
    QObject::connect(updateRemoteImagesTimer, SIGNAL(timeout()), this, SLOT(updateRemoteImages()));
}

void TimerManager::updateStatusOnServer()
{
    if(Peer::myUsername.size() > 0 && Peer::myPassword.size() > 0 && GUI::getInstance().mainWindow)
        Message::sendUpdateStatusMessage(Peer::myUsername, Peer::myPassword);
}


void TimerManager::updateRemoteImages()
{
    if(!GUI::getInstance().mainWindow)
        return;

    for(int i = 0; i < Peer::onlinePeers.size(); i++)
    {
        Message::sendRequestAllowedImagesMessage(Peer::myUsername, Peer::onlinePeers.at(i).IPAddress, Peer::onlinePeers.at(i).port);
    }
}
