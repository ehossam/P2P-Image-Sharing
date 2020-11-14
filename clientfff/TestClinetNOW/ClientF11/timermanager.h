#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include <QObject>
#include <QTimer>


class TimerManager : public QObject
{
    Q_OBJECT
public:
    explicit TimerManager(QObject *parent = nullptr);

    QTimer* updateStatusOnServerTimer;
    QTimer* updateRemoteImagesTimer;
signals:

public slots:
    void updateStatusOnServer();
    void updateRemoteImages();
};

#endif // TIMERMANAGER_Hv
