/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *TabWidget;
    QWidget *RequestViewsTab;
    QListWidget *OnlineUsersList;
    QLabel *label;
    QPushButton *ViewUserImagesButton;
    QTreeWidget *UserImagesTree;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *RequestViewsButton;
    QFrame *line;
    QSpinBox *NumberOfViewsSpinBox;
    QWidget *tab_2;
    QTreeWidget *OtherUpdateRequestsTreeWidget;
    QLabel *label_4;
    QPushButton *AcceptRequestButton;
    QPushButton *DenyRequestButton;
    QWidget *MyImages;
    QTreeWidget *OtherImagesTree;
    QLabel *label_6;
    QPushButton *UploadNewImageButton;
    QComboBox *AllowedPeersComboBox;
    QLabel *label_7;
    QTreeWidget *MyImagesTree;
    QLabel *label_8;
    QLabel *ImageThumbnail;
    QLabel *MyImageViewQuota;
    QLabel *label_9;
    QLabel *label_10;
    QPushButton *DeleteUserButton;
    QComboBox *OnlinePeersComboBox;
    QLabel *label_11;
    QSpinBox *NewViewingQuotaSpinBox;
    QPushButton *AddOrUpdateButton;
    QLabel *label_12;
    QPushButton *ViewImageButton;
    QLabel *RemainingViews;
    QLabel *RemoteImage;
    QPushButton *ForceUpdateButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(863, 571);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TabWidget = new QTabWidget(centralWidget);
        TabWidget->setObjectName(QStringLiteral("TabWidget"));
        TabWidget->setGeometry(QRect(30, 20, 841, 551));
        RequestViewsTab = new QWidget();
        RequestViewsTab->setObjectName(QStringLiteral("RequestViewsTab"));
        OnlineUsersList = new QListWidget(RequestViewsTab);
        OnlineUsersList->setObjectName(QStringLiteral("OnlineUsersList"));
        OnlineUsersList->setGeometry(QRect(40, 60, 311, 291));
        label = new QLabel(RequestViewsTab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 40, 91, 17));
        ViewUserImagesButton = new QPushButton(RequestViewsTab);
        ViewUserImagesButton->setObjectName(QStringLiteral("ViewUserImagesButton"));
        ViewUserImagesButton->setGeometry(QRect(80, 370, 231, 25));
        UserImagesTree = new QTreeWidget(RequestViewsTab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(1, QStringLiteral("Name"));
        __qtreewidgetitem->setText(0, QStringLiteral("ID"));
        UserImagesTree->setHeaderItem(__qtreewidgetitem);
        UserImagesTree->setObjectName(QStringLiteral("UserImagesTree"));
        UserImagesTree->setGeometry(QRect(420, 60, 391, 291));
        UserImagesTree->setColumnCount(4);
        UserImagesTree->header()->setCascadingSectionResizes(false);
        UserImagesTree->header()->setDefaultSectionSize(75);
        UserImagesTree->header()->setHighlightSections(false);
        UserImagesTree->header()->setStretchLastSection(true);
        label_2 = new QLabel(RequestViewsTab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(460, 40, 131, 17));
        label_3 = new QLabel(RequestViewsTab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(510, 380, 121, 17));
        RequestViewsButton = new QPushButton(RequestViewsTab);
        RequestViewsButton->setObjectName(QStringLiteral("RequestViewsButton"));
        RequestViewsButton->setGeometry(QRect(500, 430, 261, 25));
        line = new QFrame(RequestViewsTab);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(390, 60, 31, 291));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        NumberOfViewsSpinBox = new QSpinBox(RequestViewsTab);
        NumberOfViewsSpinBox->setObjectName(QStringLiteral("NumberOfViewsSpinBox"));
        NumberOfViewsSpinBox->setGeometry(QRect(650, 370, 61, 41));
        TabWidget->addTab(RequestViewsTab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        OtherUpdateRequestsTreeWidget = new QTreeWidget(tab_2);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("ID"));
        OtherUpdateRequestsTreeWidget->setHeaderItem(__qtreewidgetitem1);
        OtherUpdateRequestsTreeWidget->setObjectName(QStringLiteral("OtherUpdateRequestsTreeWidget"));
        OtherUpdateRequestsTreeWidget->setGeometry(QRect(230, 80, 341, 311));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 60, 231, 17));
        AcceptRequestButton = new QPushButton(tab_2);
        AcceptRequestButton->setObjectName(QStringLiteral("AcceptRequestButton"));
        AcceptRequestButton->setGeometry(QRect(230, 400, 121, 25));
        DenyRequestButton = new QPushButton(tab_2);
        DenyRequestButton->setObjectName(QStringLiteral("DenyRequestButton"));
        DenyRequestButton->setGeometry(QRect(450, 400, 121, 25));
        TabWidget->addTab(tab_2, QString());
        MyImages = new QWidget();
        MyImages->setObjectName(QStringLiteral("MyImages"));
        OtherImagesTree = new QTreeWidget(MyImages);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QStringLiteral("ID"));
        OtherImagesTree->setHeaderItem(__qtreewidgetitem2);
        OtherImagesTree->setObjectName(QStringLiteral("OtherImagesTree"));
        OtherImagesTree->setGeometry(QRect(20, 300, 431, 161));
        OtherImagesTree->header()->setDefaultSectionSize(100);
        label_6 = new QLabel(MyImages);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 20, 81, 17));
        UploadNewImageButton = new QPushButton(MyImages);
        UploadNewImageButton->setObjectName(QStringLiteral("UploadNewImageButton"));
        UploadNewImageButton->setGeometry(QRect(270, 210, 141, 31));
        AllowedPeersComboBox = new QComboBox(MyImages);
        AllowedPeersComboBox->setObjectName(QStringLiteral("AllowedPeersComboBox"));
        AllowedPeersComboBox->setGeometry(QRect(470, 50, 151, 31));
        label_7 = new QLabel(MyImages);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(470, 80, 241, 31));
        MyImagesTree = new QTreeWidget(MyImages);
        MyImagesTree->setObjectName(QStringLiteral("MyImagesTree"));
        MyImagesTree->setGeometry(QRect(20, 40, 241, 201));
        MyImagesTree->setColumnCount(2);
        MyImagesTree->header()->setDefaultSectionSize(10);
        MyImagesTree->header()->setMinimumSectionSize(57);
        label_8 = new QLabel(MyImages);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(270, 30, 131, 20));
        ImageThumbnail = new QLabel(MyImages);
        ImageThumbnail->setObjectName(QStringLiteral("ImageThumbnail"));
        ImageThumbnail->setGeometry(QRect(270, 60, 181, 131));
        MyImageViewQuota = new QLabel(MyImages);
        MyImageViewQuota->setObjectName(QStringLiteral("MyImageViewQuota"));
        MyImageViewQuota->setGeometry(QRect(720, 80, 91, 31));
        label_9 = new QLabel(MyImages);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(470, 30, 131, 17));
        label_10 = new QLabel(MyImages);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(470, 140, 91, 17));
        DeleteUserButton = new QPushButton(MyImages);
        DeleteUserButton->setObjectName(QStringLiteral("DeleteUserButton"));
        DeleteUserButton->setGeometry(QRect(630, 50, 111, 31));
        OnlinePeersComboBox = new QComboBox(MyImages);
        OnlinePeersComboBox->setObjectName(QStringLiteral("OnlinePeersComboBox"));
        OnlinePeersComboBox->setGeometry(QRect(470, 160, 151, 31));
        label_11 = new QLabel(MyImages);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(630, 140, 141, 17));
        NewViewingQuotaSpinBox = new QSpinBox(MyImages);
        NewViewingQuotaSpinBox->setObjectName(QStringLiteral("NewViewingQuotaSpinBox"));
        NewViewingQuotaSpinBox->setGeometry(QRect(630, 160, 91, 31));
        AddOrUpdateButton = new QPushButton(MyImages);
        AddOrUpdateButton->setObjectName(QStringLiteral("AddOrUpdateButton"));
        AddOrUpdateButton->setGeometry(QRect(470, 210, 141, 31));
        label_12 = new QLabel(MyImages);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 280, 111, 17));
        ViewImageButton = new QPushButton(MyImages);
        ViewImageButton->setObjectName(QStringLiteral("ViewImageButton"));
        ViewImageButton->setGeometry(QRect(330, 470, 111, 31));
        RemainingViews = new QLabel(MyImages);
        RemainingViews->setObjectName(QStringLiteral("RemainingViews"));
        RemainingViews->setGeometry(QRect(150, 470, 67, 31));
        RemoteImage = new QLabel(MyImages);
        RemoteImage->setObjectName(QStringLiteral("RemoteImage"));
        RemoteImage->setGeometry(QRect(470, 300, 351, 201));
        ForceUpdateButton = new QPushButton(MyImages);
        ForceUpdateButton->setObjectName(QStringLiteral("ForceUpdateButton"));
        ForceUpdateButton->setEnabled(true);
        ForceUpdateButton->setGeometry(QRect(70, 470, 111, 31));
        TabWidget->addTab(MyImages, QString());
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        TabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Image Service", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Online Users", Q_NULLPTR));
        ViewUserImagesButton->setText(QApplication::translate("MainWindow", "View Selected User's Images", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = UserImagesTree->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "Views", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Owner", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "User's Images", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Number of Views", Q_NULLPTR));
        RequestViewsButton->setText(QApplication::translate("MainWindow", "Request Views' Update From Owner", Q_NULLPTR));
        TabWidget->setTabText(TabWidget->indexOf(RequestViewsTab), QApplication::translate("MainWindow", "Request Views", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem1 = OtherUpdateRequestsTreeWidget->headerItem();
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "Requested Views", Q_NULLPTR));
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "Username", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Other Users' Update Requests", Q_NULLPTR));
        AcceptRequestButton->setText(QApplication::translate("MainWindow", "Accept Request", Q_NULLPTR));
        DenyRequestButton->setText(QApplication::translate("MainWindow", "Deny Request", Q_NULLPTR));
        TabWidget->setTabText(TabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Pending Requests", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem2 = OtherImagesTree->headerItem();
        ___qtreewidgetitem2->setText(3, QApplication::translate("MainWindow", "Number of Views", Q_NULLPTR));
        ___qtreewidgetitem2->setText(2, QApplication::translate("MainWindow", "Owner", Q_NULLPTR));
        ___qtreewidgetitem2->setText(1, QApplication::translate("MainWindow", "Name", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "My Images", Q_NULLPTR));
        UploadNewImageButton->setText(QApplication::translate("MainWindow", "Upload New Image", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Remaining views for selected user: ", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem3 = MyImagesTree->headerItem();
        ___qtreewidgetitem3->setText(1, QApplication::translate("MainWindow", "Name", Q_NULLPTR));
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Image Thumbnail", Q_NULLPTR));
        ImageThumbnail->setText(QString());
        MyImageViewQuota->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Authorized Users", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Online Users", Q_NULLPTR));
        DeleteUserButton->setText(QApplication::translate("MainWindow", "Delete User", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "New Viewing Quota", Q_NULLPTR));
        AddOrUpdateButton->setText(QApplication::translate("MainWindow", "Add or Update User", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Others' Images", Q_NULLPTR));
        ViewImageButton->setText(QApplication::translate("MainWindow", "View Image", Q_NULLPTR));
        RemainingViews->setText(QString());
        RemoteImage->setText(QString());
        ForceUpdateButton->setText(QApplication::translate("MainWindow", "Refresh Now", Q_NULLPTR));
        TabWidget->setTabText(TabWidget->indexOf(MyImages), QApplication::translate("MainWindow", "My Images", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
