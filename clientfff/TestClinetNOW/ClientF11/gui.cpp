#include "gui.h"
#include "peer.h"
#include "image.h"

void GUI::init()
{
    loginDialog = NULL;
    mainWindow = NULL;

    updateGUITimer = new QTimer(this);
    QObject::connect(updateGUITimer, SIGNAL(timeout()), this, SLOT(updateGUI()));
}

void GUI::viewRegisterResult(bool success)
{
    string result = "";

    if(success)
        result = "Registration Succeeded, Please Login.";
    else
        result = "Registration Failed, User already exists.";

    loginDialog->setRegisterResultString(result);
}

void GUI::viewLoginResult(bool success)
{
    if(!success)
    {
        string result = "Login Failed.";
        loginDialog->setRegisterResultString(result);
    }
    else
    {
        string result = "Login Succeeded. Please Wait..";
        loginDialog->setRegisterResultString(result);

        loginDialog->isLoggedIn = true;
    }
}


void GUI::updateGUI()
{
    if(loginDialog)
    {
        if(loginDialog->isLoggedIn)
        {
            delete loginDialog;
            loginDialog = NULL;

            mainWindow = new MainWindow;
            mainWindow->show();
            mainWindow->init();
        }
    }

    if(mainWindow)
    {
        mainWindow->setWindowTitle("Image Service - " + QString::fromStdString(Peer::myUsername));
        mainWindow->updateOnlinePeers();
        mainWindow->viewOtherImages();
        mainWindow->updatePeerViewCount();
    }
}
