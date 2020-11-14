#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <QSqlDatabase>

using namespace std;

class DatabaseManager
{
public:
    QSqlDatabase db;
public:
    DatabaseManager(string path);

    bool addUser(string username, string password);

    bool doesUserExist(string username, string password) const;

    string getIPFromUser(string username) const;

    bool updateUserIP(string username, string IPAddress);

    string debug();

    ~DatabaseManager();
};
#endif // DATABASEMANAGER_H
