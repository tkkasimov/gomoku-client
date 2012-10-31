#ifndef NET_H
#define NET_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include "ConnectionInfoDialog.h"
#include "field.h"
#include <QMainWindow>

enum Symbol
{
    SM_O,
    SM_X
};

enum Status
{
    ST_WAITING_STEP,
    ST_MAKING_STEP
};

class net:public QObject
{
    Q_OBJECT
public:
    net(ConnectionInfoDialog *dialog, Field* myField_, QMainWindow *mainwindow_);
    ~net();
    void newCon();
    Status getState();
    void parse(const QByteArray &cmd);
    QTcpSocket* getSocket();
    Symbol getSymbol();

private:
    Symbol mySymbol;
    QTcpSocket *socket;
    Status state;
    ConnectionInfoDialog *dialog_;
    Field *myField;
    QMainWindow* mainWindow;

public slots:
    void onReadyRead();
    void onDisconnected();
};

#endif // NET_H
