#include "udpsocket.h"
#include "message.h"
#include "gui.h"
#include "timermanager.h"
#include <QApplication>
#include <pthread.h>

#define DEFAULT_PORT 22246
#define UPDATE_GUI_INTERVAL 1000
#define UPDATE_SERVER_INTERVAL 2000
#define ROBOT_INTERVAL 2000


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Connecting to default port unless a port was passed as argument
    int port = DEFAULT_PORT;

    if(argc > 1)
        port = atoi(argv[1]);


    Message::mySocket.myPort = port;
    Message::mySocket.initializeSocket();

    GUI::getInstance().init();
    GUI::getInstance().loginDialog = new LoginDialog;
    GUI::getInstance().loginDialog->show();
    GUI::getInstance().updateGUITimer->start(500);

    TimerManager tm;
    tm.updateStatusOnServerTimer->start(UPDATE_SERVER_INTERVAL);
    tm.updateRemoteImagesTimer->start(ROBOT_INTERVAL);


  MainWindow w;
//w.show();

    return a.exec();
}
