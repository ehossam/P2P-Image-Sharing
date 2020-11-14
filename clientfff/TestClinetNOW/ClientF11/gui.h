#ifndef GUI_H
#define GUI_H

#include "logindialog.h"
#include "mainwindow.h"

#include <QObject>
#include <QTimer>

class GUI : QObject
{
    Q_OBJECT

public:
    LoginDialog* loginDialog;
    MainWindow* mainWindow;

    QTimer* updateGUITimer;
public:
    void init();

    void viewRegisterResult(bool success);
    void viewLoginResult(bool success);

public slots:
    void updateGUI();

//singleton
public:
    static GUI& getInstance()
    {
        static GUI instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
private:
    GUI() {}

public:
    GUI(GUI const&)               = delete;
    void operator=(GUI const&)  = delete;

};

#endif // GUI_H
