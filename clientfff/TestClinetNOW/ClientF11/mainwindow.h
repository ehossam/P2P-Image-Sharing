#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init();

    void updateOnlinePeers();
    void viewMyImages();
    void viewOtherImages();
    void viewRemoteImage(QString imageByteArray);

public slots:
    void handleSelectedOwnImage();
    void uploadNewImage();
    void addOrUpdateUser();
    void deleteUser();
    void updatePeerViewCount();
    void updateSpinBoxViewCount();
    void requestAllImages();
    void requestViews();
    void acceptRequest();
    void denyRequest();
    void forceOtherImagesUpdate();
    void requestToViewImage();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
