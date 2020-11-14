/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label_2;
    QPushButton *RegisterButton;
    QLabel *LoginResult;
    QLineEdit *UsernameText;
    QLabel *label;
    QPushButton *LoginButton;
    QLineEdit *PasswordText;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(400, 213);
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 86, 71, 17));
        RegisterButton = new QPushButton(LoginDialog);
        RegisterButton->setObjectName(QStringLiteral("RegisterButton"));
        RegisterButton->setGeometry(QRect(250, 140, 89, 25));
        LoginResult = new QLabel(LoginDialog);
        LoginResult->setObjectName(QStringLiteral("LoginResult"));
        LoginResult->setGeometry(QRect(50, 176, 291, 20));
        LoginResult->setTextFormat(Qt::AutoText);
        LoginResult->setAlignment(Qt::AlignCenter);
        UsernameText = new QLineEdit(LoginDialog);
        UsernameText->setObjectName(QStringLiteral("UsernameText"));
        UsernameText->setGeometry(QRect(130, 30, 211, 31));
        label = new QLabel(LoginDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 36, 71, 17));
        LoginButton = new QPushButton(LoginDialog);
        LoginButton->setObjectName(QStringLiteral("LoginButton"));
        LoginButton->setGeometry(QRect(130, 140, 80, 25));
        PasswordText = new QLineEdit(LoginDialog);
        PasswordText->setObjectName(QStringLiteral("PasswordText"));
        PasswordText->setGeometry(QRect(130, 80, 211, 31));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Login", Q_NULLPTR));
        label_2->setText(QApplication::translate("LoginDialog", "Password", Q_NULLPTR));
        RegisterButton->setText(QApplication::translate("LoginDialog", "Register", Q_NULLPTR));
        LoginResult->setText(QString());
        label->setText(QApplication::translate("LoginDialog", "Username", Q_NULLPTR));
        LoginButton->setText(QApplication::translate("LoginDialog", "Login", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
