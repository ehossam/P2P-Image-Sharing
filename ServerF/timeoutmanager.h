#ifndef TIMEOUTMANAGER_H
#define TIMEOUTMANAGER_H

#include <QObject>
#include <QTimer>

#define SESSION_TIMEOUT 5000
#define SESSION_CHECK_INTERVAL 1000

class TimeoutManager : public QObject
{
    Q_OBJECT
public:
    explicit TimeoutManager(QObject *parent = nullptr);

    QTimer* sessionCheckTimer;
signals:

public slots:
    void checkClientsTimeout();
};

#endif // TIMEOUTMANAGER_H
