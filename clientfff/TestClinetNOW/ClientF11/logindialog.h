#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <string>

using namespace std;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    bool isLoggedIn;
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    void setRegisterResultString(string result);

public slots:
    void handleRegistration();
    void handleLogin();


private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
