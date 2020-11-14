#include "logindialog.h"
#include "ui_logindialog.h"

#include "message.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->LoginButton, SIGNAL(pressed()), this, SLOT(handleLogin()));
    connect(ui->RegisterButton, SIGNAL(pressed()), this, SLOT(handleRegistration()));


    isLoggedIn = false;
}


void LoginDialog::setRegisterResultString(string result)
{
    ui->LoginResult->setText(QString::fromStdString(result));
}

void LoginDialog::handleRegistration()
{
    //cout << "Register pressed";
    string username = ui->UsernameText->text().toStdString();
    string password = ui->PasswordText->text().toStdString();

    Message::sendRegisterMessage(username, password, 0);
}

void LoginDialog::handleLogin()
{
   // cout << "login pressed";
    string username = ui->UsernameText->text().toStdString();
    string password = ui->PasswordText->text().toStdString();

    //Message::sendLoginMessage(username, password);
    Message::sendRegisterMessage(username, password,1);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

