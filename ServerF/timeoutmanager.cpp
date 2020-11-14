#include "timeoutmanager.h"
#include "client.h"

TimeoutManager::TimeoutManager(QObject *parent) : QObject(parent)
{
    sessionCheckTimer = new QTimer(this);
    QObject::connect(sessionCheckTimer, SIGNAL(timeout()), this, SLOT(checkClientsTimeout()));
}


void TimeoutManager::checkClientsTimeout()
{
    for(int i = 0; i < Client::loggedInClients.size(); i++)
    {
        Client::loggedInClients.at(i).timeout += SESSION_CHECK_INTERVAL;

        if(Client::loggedInClients.at(i).timeout >= SESSION_TIMEOUT)
        {
            Client::logoutUser(Client::loggedInClients.at(i).username);
        }
    }
}
