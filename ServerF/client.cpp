#include "client.h"
#include <QDir>
#include <QStringList>

#include <iostream>

DatabaseManager Client::databaseManager = DatabaseManager("users");

vector<Client> Client::loggedInClients;

Client::Client(string _username, string _IPAddress, int _port)
{
    username = _username;
    IPAddress = _IPAddress;
    port = _port;
    timeout = 0;
}


bool Client::registerUser(string username, string password)
{
    //cout<<"HERE: "<<databaseManager.debug()<<endl;
    if(databaseManager.addUser(username, password))
        return true;
    else
        return false;
}

bool Client::loginUser(string username, string password, string ip, int port)
{
    cout<< "There are logged in client: "<<loggedInClients.size();
    if(!isUserLoggedIn(username, ip))
    {

        //cout << "Username: " << username <<"  password: "<< password<< "    Status: "<< isUserLoggedIn(username, ip);

        if(databaseManager.doesUserExist(username, password) )
        {
            databaseManager.updateUserIP(username, ip);
            loggedInClients.push_back(Client(username, ip, port));
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

bool Client::isUserLoggedIn(string username, string ip)
{
    bool found = false;
    for(unsigned int i = 0; i < loggedInClients.size(); i++)
    {
        if(loggedInClients.at(i).username == username)
        {
            found = true;
            databaseManager.updateUserIP(username, ip);
            loggedInClients.at(i).timeout = 0;
            break;
        }
    }

    return found;
}


bool Client::logoutUser(string username)
{
    int foundIndex = -1;
    for(unsigned int i = 0; i < loggedInClients.size(); i++)
    {
        if(loggedInClients.at(i).username == username)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex != -1)
    {
        loggedInClients.erase(loggedInClients.begin() + foundIndex);
        databaseManager.updateUserIP(username, "");
        return true;
    }

    return false;
}
