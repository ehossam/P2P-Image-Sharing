#include <iostream>
#include "client.h"
#include "udpsocket.h"
#include "message.h"
#include "timeoutmanager.h"

#include <QApplication>

using namespace std;

#define DEFAULT_SERVER_PORT 78966

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Message::mySocket.myPort = DEFAULT_SERVER_PORT;
    Message::mySocket.initializeSocket();

    TimeoutManager tm;
    tm.sessionCheckTimer->start(1000);

    return a.exec();
}
