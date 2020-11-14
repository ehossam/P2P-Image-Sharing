#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <iostream>

DatabaseManager::DatabaseManager(string path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QString::fromStdString(path));

    if(!db.open())
    {
        cout << "Error: connecting to database has failed." <<endl;
    }
    else
    {
        cout << "Connected successfully to database." << endl;
    }

}


DatabaseManager::~DatabaseManager()
{
    if(db.isOpen())
    {
        db.close();
    }
}

bool DatabaseManager::addUser(string username, string password)
{
    cout<< "User recieved :" << username << " password :" <<password<<endl;
    if(username.length() > 0 && password.length() > 0)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO User (username, password) VALUES (:username, :password)");
        query.bindValue(":username", QString::fromStdString(username));
        query.bindValue(":password", QString::fromStdString(password));


        if(query.exec())
        {
            cout << "Adding new user: " << username << " has succeeded." << endl;
            return true;
        }
    }
    //qDebug() << query.lastError().text();
    cout << "Adding new user: " << username << " has failed." << endl;
    return false;
}


bool DatabaseManager::doesUserExist(string username, string password) const
{
    QSqlQuery query;
    query.prepare("SELECT username, password FROM User WHERE username = (:username) AND password = (:password)");
    query.bindValue(":username", QString::fromStdString(username));
    query.bindValue(":password", QString::fromStdString(password));

    if(query.exec())
    {
        if(query.next())
            return true;
    }

    return false;
}


string DatabaseManager::getIPFromUser(string username) const
{
    QSqlQuery query;
    query.prepare("SELECT ip_address FROM User WHERE username = (:username)");
    query.bindValue(":username", QString::fromStdString(username));

    if(query.exec())
    {
        if(query.next())
        {
            return query.value(0).toString().toStdString();
        }
    }

    return "";
}


bool DatabaseManager::updateUserIP(string username, string IPAddress)
{
    QSqlQuery query;
    query.prepare("UPDATE User SET ip_address = (:ip) WHERE username = (:username)");
    query.bindValue(":ip", QString::fromStdString(IPAddress));
    query.bindValue(":username", QString::fromStdString(username));

    if(query.exec())
    {
     //   cout << query.executedQuery().toStdString();

        return true;
    }
   // cout << "QUERY: " << query.executedQuery().toStdString();

    return false;
}


string DatabaseManager::debug()
{
    return db.tables().back().toStdString();

}
