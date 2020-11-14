#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "peer.h"
#include "image.h"
#include "message.h"

#include <iostream>
#include <string>
#include <QFileDialog>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //resizing tree widgets
    ui->OtherImagesTree->setColumnWidth(0, 30);
    ui->OtherImagesTree->setColumnWidth(0, 100);
    ui->OtherImagesTree->setColumnWidth(0, 70);
    ui->OtherImagesTree->setColumnWidth(0, 30);

    connect(ui->MyImagesTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(handleSelectedOwnImage()));
    connect(ui->UploadNewImageButton, SIGNAL(pressed()), this, SLOT(uploadNewImage()));
    connect(ui->AddOrUpdateButton, SIGNAL(pressed()), this, SLOT(addOrUpdateUser()));
    connect(ui->AllowedPeersComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updatePeerViewCount()));
    connect(ui->OnlinePeersComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(updateSpinBoxViewCount()));
    connect(ui->DeleteUserButton, SIGNAL(pressed()), this, SLOT(deleteUser()));
    connect(ui->ForceUpdateButton, SIGNAL(pressed()), this, SLOT(forceOtherImagesUpdate()));
    connect(ui->ViewImageButton, SIGNAL(pressed()), this, SLOT(requestToViewImage()));
    connect(ui->ViewUserImagesButton, SIGNAL(pressed()), this, SLOT(requestAllImages()));
    connect(ui->RequestViewsButton, SIGNAL(pressed()), this, SLOT(requestViews()));
    connect(ui->AcceptRequestButton, SIGNAL(pressed()), this, SLOT(acceptRequest()));
    connect(ui->DenyRequestButton, SIGNAL(pressed()), this, SLOT(denyRequest()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init()
{
    ui->AllowedPeersComboBox->setEnabled(false);
    ui->DeleteUserButton->setEnabled(false);
    ui->OnlinePeersComboBox->setEnabled(false);
    ui->NewViewingQuotaSpinBox->setEnabled(false);
    ui->AddOrUpdateButton->setEnabled(false);

    Image::loadMyImages(Peer::myUsername);
    viewMyImages();
}

void MainWindow::requestViews()
{
    if(!ui->UserImagesTree->currentItem())
        return;

    int id = ui->UserImagesTree->currentItem()->text(0).toInt();
    string username = ui->UserImagesTree->currentItem()->text(2).toStdString();

    Peer* peer = Peer::getPeerByUsername(username);

    if(!peer)
        return;

    int val = ui->NumberOfViewsSpinBox->value();

    Message::sendRequestViewsMessage(Peer::myUsername, id, val, peer->IPAddress, peer->port);
}


void MainWindow::acceptRequest()
{
    if(!ui->OtherUpdateRequestsTreeWidget->currentItem())
        return;

    int id = ui->OtherUpdateRequestsTreeWidget->currentItem()->text(0).toInt();
    string username = ui->OtherUpdateRequestsTreeWidget->currentItem()->text(1).toStdString();
    int views = ui->OtherUpdateRequestsTreeWidget->currentItem()->text(2).toInt();

    Image* image = Image::getImageByID(id);

    if(!image)
        return;

    if(image->isUserAdded(username))
    {
        image->updateUserViewCount(username, views);
    }
    else
    {
        image->addUser(username, views);
    }

    Image::deleteRequestIfAlreadyExists(id, username);
}

void MainWindow::denyRequest()
{
    if(!ui->OtherUpdateRequestsTreeWidget->currentItem())
        return;

    int id = ui->OtherUpdateRequestsTreeWidget->currentItem()->text(0).toInt();
    string username = ui->OtherUpdateRequestsTreeWidget->currentItem()->text(1).toStdString();

    Image* image = Image::getImageByID(id);

    if(!image)
        return;

    Image::deleteRequestIfAlreadyExists(id, username);
}

void MainWindow::handleSelectedOwnImage()
{
    if(!ui->MyImagesTree->currentItem())
    {
        ui->ImageThumbnail->clear();

        ui->AllowedPeersComboBox->setEnabled(false);
        ui->DeleteUserButton->setEnabled(false);
        ui->OnlinePeersComboBox->setEnabled(false);
        ui->NewViewingQuotaSpinBox->setEnabled(false);
        ui->AddOrUpdateButton->setEnabled(false);

        return;
    }

    int id = ui->MyImagesTree->currentItem()->text(0).toInt();
    Image* image = Image::getImageByID(id);

    if(!image)
        return;

    QPixmap p(image->imagePixmap);

    int w = ui->ImageThumbnail->width();
    int h = ui->ImageThumbnail->height();

    ui->ImageThumbnail->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));

    if(image->userViewsPairs.size() > 0)
    {
        ui->AllowedPeersComboBox->setEnabled(true);
        ui->DeleteUserButton->setEnabled(true);

        ui->AllowedPeersComboBox->clear();
        for(int i = 0; i < image->userViewsPairs.size(); i++)
        {
            ui->AllowedPeersComboBox->addItem(QString::fromStdString(image->userViewsPairs.at(i).username));
        }
    }
    else
    {
        ui->AllowedPeersComboBox->clear();

        ui->AllowedPeersComboBox->setEnabled(false);
        ui->DeleteUserButton->setEnabled(false);
    }

    updatePeerViewCount();
    updateSpinBoxViewCount();

    ui->OnlinePeersComboBox->setEnabled(true);
    ui->NewViewingQuotaSpinBox->setEnabled(true);
    ui->AddOrUpdateButton->setEnabled(true);

    ui->OnlinePeersComboBox->clear();

    for(int i = 0; i < Peer::onlinePeers.size(); i++)
    {
        ui->OnlinePeersComboBox->addItem(QString::fromStdString(Peer::onlinePeers.at(i).username));
    }
}

void MainWindow::updatePeerViewCount()
{
    if(!ui->MyImagesTree->currentItem())
        return;

    int id = ui->MyImagesTree->currentItem()->text(0).toInt();
    Image* image = Image::getImageByID(id);

    if(!image)
        return;


    string username = ui->AllowedPeersComboBox->currentText().toStdString();

    int val = image->getUserViewQuota(username);
    if(val != -1)
    {
        ui->MyImageViewQuota->setText(QString::number(val));
    }
    else
    {
        ui->MyImageViewQuota->setText("");
    }
}

void MainWindow::updateSpinBoxViewCount()
{
    if(!ui->MyImagesTree->currentItem())
        return;

    int id = ui->MyImagesTree->currentItem()->text(0).toInt();
    Image* image = Image::getImageByID(id);

    if(!image)
        return;

    string username = ui->OnlinePeersComboBox->currentText().toStdString();

    int val = image->getUserViewQuota(username);
    if(val != -1)
    {
        ui->NewViewingQuotaSpinBox->setValue(val);
    }
    else
    {
        ui->NewViewingQuotaSpinBox->setValue(0);
    }
}

void MainWindow::uploadNewImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home", tr("Image Files (*.jpg)"));

    Image::uploadImage(fileName);
    Image::loadMyImages(Peer::myUsername);
    viewMyImages();
}


void MainWindow::addOrUpdateUser()
{
    if(!ui->MyImagesTree->currentItem())
        return;

    int id = ui->MyImagesTree->currentItem()->text(0).toInt();
    Image* image = Image::getImageByID(id);

    if(!image)
        return;

    string username = ui->OnlinePeersComboBox->currentText().toStdString();
    int views = ui->NewViewingQuotaSpinBox->value();

    if(image->isUserAdded(username))
    {
        image->updateUserViewCount(username, views);
    }
    else
    {
        image->addUser(username, views);
    }

    handleSelectedOwnImage();
}


void MainWindow::deleteUser()
{
    if(!ui->MyImagesTree->currentItem())
        return;

    int id = ui->MyImagesTree->currentItem()->text(0).toInt();
    Image* image = Image::getImageByID(id);

    if(!image)
        return;

    string username = ui->AllowedPeersComboBox->currentText().toStdString();

    if(image->isUserAdded(username))
    {
        image->removeUser(username);
    }

    handleSelectedOwnImage();
}


void MainWindow::forceOtherImagesUpdate()
{
    for(int i = 0; i < Peer::onlinePeers.size(); i++)
    {
        Message::sendRequestAllowedImagesMessage(Peer::myUsername, Peer::onlinePeers.at(i).IPAddress, Peer::onlinePeers.at(i).port);
    }
}

void MainWindow::requestAllImages()
{
    if(!ui->OnlineUsersList->currentItem())
        return;

    Peer *peer = Peer::getPeerByUsername(ui->OnlineUsersList->currentItem()->text().toStdString());

    Message::sendRequestImagesMessage(Peer::myUsername, peer->IPAddress, peer->port);
}

void MainWindow::requestToViewImage()
{
    if(!ui->OtherImagesTree->currentItem())
        return;

    int id = ui->OtherImagesTree->currentItem()->text(0).toInt();
    string username = ui->OtherImagesTree->currentItem()->text(2).toStdString();

    Peer* peer = Peer::getPeerByUsername(username);

    if(!peer)
        return;

    Message::sendViewImageMessage(Peer::myUsername, id, peer->IPAddress, peer->port);
}


void MainWindow::viewMyImages()
{
    ui->MyImagesTree->clear();
    for(int i = 0; i < Image::myImages.size(); i++)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::number(Image::myImages.at(i).imageID));
        item->setText(1, QString::fromStdString(Image::myImages.at(i).imageName));
        ui->MyImagesTree->addTopLevelItem(item);
    }
}




void MainWindow::viewOtherImages()
{
    string previousSelectedImageName = "";
    string previousSelectedOwner = "";

    if(ui->OtherImagesTree->currentItem())
    {
       ui->ViewImageButton->setEnabled(true);
       ui->ForceUpdateButton->setEnabled(true);
       previousSelectedImageName = ui->OtherImagesTree->currentItem()->text(1).toStdString();
       previousSelectedOwner = ui->OtherImagesTree->currentItem()->text(2).toStdString();
    }
    else
    {
        ui->ViewImageButton->setEnabled(false);
        ui->ForceUpdateButton->setEnabled(false);
    }

    ui->OtherImagesTree->setSortingEnabled(false);

    ui->OtherImagesTree->clear();
    for(int i = 0; i < Image::otherImages.size(); i++)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::number(Image::otherImages.at(i).imageID));
        item->setText(1, QString::fromStdString(Image::otherImages.at(i).imageName));
        item->setText(2, QString::fromStdString(Image::otherImages.at(i).owner));
        item->setData(3, Qt::DisplayRole, Image::otherImages.at(i).viewCount);
        ui->OtherImagesTree->addTopLevelItem(item);

        if(Image::otherImages.at(i).imageName == previousSelectedImageName
                && Image::otherImages.at(i).owner == previousSelectedOwner)
        {
            ui->OtherImagesTree->setCurrentItem(item);
        }
    }

   ui->OtherImagesTree->setSortingEnabled(true);
   ui->OtherImagesTree->sortByColumn(3);
}

void MainWindow::viewRemoteImage(QString imageByteArray)
{
    QByteArray imageBytes = QByteArray::fromStdString(imageByteArray.toStdString());
    imageBytes = QByteArray::fromBase64(imageBytes);
    QPixmap pic;
    //Image image= Image("default");

    //if (image.viewimageflag==0){
    if(pic.loadFromData(imageBytes,"JPG"))
    {
        int w = ui->RemoteImage->width();
        int h = ui->RemoteImage->height();

        ui->RemoteImage->setPixmap(pic.scaled(w,h,Qt::KeepAspectRatio));
    }
   // }
 //   else{
      //  ui->RemoteImage->clear();
   // }
}

void MainWindow::updateOnlinePeers()
{
    string previousOnlineUserListSelection = "";

    if(ui->OnlineUsersList->currentItem())
    {
       ui->ViewUserImagesButton->setEnabled(true);
       previousOnlineUserListSelection = ui->OnlineUsersList->currentItem()->text().toStdString();
    }
    else
    {
        ui->ViewUserImagesButton->setEnabled(false);
    }

    ui->OnlineUsersList->clear();


    for(int i = 0; i < Peer::onlinePeers.size(); i++)
    {
        QListWidgetItem* newPeer = new QListWidgetItem(QString::fromStdString(Peer::onlinePeers.at(i).username));

        ui->OnlineUsersList->addItem(newPeer);
        if(Peer::onlinePeers.at(i).username == previousOnlineUserListSelection)
        {
            ui->OnlineUsersList->setCurrentItem(newPeer);
        }
    }

    int previousUserImagesTreeSelectionImageID = 0;

    if(ui->UserImagesTree->currentItem())
    {
       ui->RequestViewsButton->setEnabled(true);
       previousUserImagesTreeSelectionImageID = ui->UserImagesTree->currentItem()->text(0).toInt();
    }
    else
    {
        ui->RequestViewsButton->setEnabled(false);
    }

    ui->UserImagesTree->clear();
    for(int i = 0; i < Image::selectedPeerRemoteImages.size(); i++)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::number(Image::selectedPeerRemoteImages.at(i).imageID));
        item->setText(1, QString::fromStdString(Image::selectedPeerRemoteImages.at(i).imageName));
        item->setText(2, QString::fromStdString(Image::selectedPeerRemoteImages.at(i).owner));
        item->setData(3, Qt::DisplayRole, Image::selectedPeerRemoteImages.at(i).viewCount);
        ui->UserImagesTree->addTopLevelItem(item);

        if(Image::selectedPeerRemoteImages.at(i).imageID == previousUserImagesTreeSelectionImageID)
        {
            ui->UserImagesTree->setCurrentItem(item);
        }
    }

    int previousOtherRequestsImageID = 0;
    string previousOtherRequestsUsername = "";

    if(ui->OtherUpdateRequestsTreeWidget->currentItem())
    {
       ui->AcceptRequestButton->setEnabled(true);
       ui->DenyRequestButton->setEnabled(true);
       previousOtherRequestsImageID = ui->OtherUpdateRequestsTreeWidget->currentItem()->text(0).toInt();
       previousOtherRequestsUsername = ui->OtherUpdateRequestsTreeWidget->currentItem()->text(1).toStdString();
    }
    else
    {
        ui->AcceptRequestButton->setEnabled(false);
        ui->DenyRequestButton->setEnabled(false);
    }

    ui->OtherUpdateRequestsTreeWidget->clear();
    for(int i = 0; i < Image::pendingViewsRequests.size(); i++)
    {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, QString::number(Image::pendingViewsRequests.at(i).imageID));
        item->setText(1, QString::fromStdString(Image::pendingViewsRequests.at(i).username));
        item->setData(2, Qt::DisplayRole, Image::pendingViewsRequests.at(i).viewCount);
        ui->OtherUpdateRequestsTreeWidget->addTopLevelItem(item);

        if(Image::pendingViewsRequests.at(i).imageID == previousOtherRequestsImageID
                && Image::pendingViewsRequests.at(i).username == previousOtherRequestsUsername)
        {
            ui->OtherUpdateRequestsTreeWidget->setCurrentItem(item);
        }
    }
}
