#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "databasemanager.h"


using namespace std;

class Client
{
public:
    static vector<Client> loggedInClients;
    static DatabaseManager databaseManager;

    string username;
    string IPAddress;
    int port;
    int timeout;

    Client(string _username, string _IPAddress, int _port);

    static bool isUserLoggedIn(string username, string ip);
    static bool loginUser(string username, string password, string ip, int port);
    static bool logoutUser(string username);
    static bool registerUser(string username, string password);
};

#endif // CLIENT_H
