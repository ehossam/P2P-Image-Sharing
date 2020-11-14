#include "steg.h"
#include <QDir>
#include <QFile>
#include <QString>

Steg::Steg()
{

}

void Steg::embedStringIntoImage(string imagePath, string text, string password)
{
    ofstream outfile;
    outfile.open("secret.txt");
    outfile << text;
    outfile.close();

    string embedCommand = "steghide embed -cf " + imagePath + " -ef secret.txt -f -p " + password;
    system(embedCommand.c_str());

    string deleteSecretCommand = "rm secret.txt";
    system(deleteSecretCommand.c_str());
}

string Steg::restoreStringFromImage(string imagePath, string password)
{
    string extractCommand ="steghide extract --stegofile " + imagePath;
    extractCommand += " -xf secret.txt -f -p " + password;
    system(extractCommand.c_str());

    QDir dir("secret.txt");
    QString secretPath = dir.absolutePath();
    QFile* secretFile = new QFile(secretPath);

    if(secretFile->open(QIODevice::ReadOnly))
    {
        string result = QString(secretFile->readAll()).toStdString();

        string deleteSecretCommand = "rm secret.txt";
        system(deleteSecretCommand.c_str());

        return result;
    }



    return "";
}

