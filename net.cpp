#include "net.h"
#include <QByteArray>

net::net(ConnectionInfoDialog *dialog, Field *myField_, QMainWindow *mainwindow_)
{
    dialog_ = dialog;
    state = ST_WAITING_STEP;
    myField = myField_;
    mainWindow = mainwindow_;
}

net::~net()
{
    delete socket;
}

void net::newCon()
{
    socket = new QTcpSocket;
    socket->connectToHost(QHostAddress(dialog_->getAddress()), dialog_->getPort());
    QString auth = "authorized:"+dialog_->getLogin()+":"+dialog_->getPassword();
    socket->write(auth.toLocal8Bit());
    connect(socket, SIGNAL(readyRead()), this , SLOT(onReadyRead()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

Status net::getState()
{
    return state;
}

void net::onReadyRead()
{
    QByteArray data = socket->readAll();
    parse(data);
}

void net::parse(const QByteArray &cmd)
{
    QRegExp rx("step:(\\d{1,2}):(\\d{1,2})");
    QRegExp re("state:(\\w+)");

    if (re.indexIn(cmd) != -1)
    {
        if (re.cap(1) == "ST_WAITING_STEP")
            state = ST_WAITING_STEP;
    }

    if (rx.indexIn(cmd) != -1)
    {
        if (mySymbol == SM_X)
            myField->setField(rx.cap(1).toInt(), rx.cap(2).toInt(), CL_O);
        else myField->setField(rx.cap(1).toInt(), rx.cap(2).toInt(), CL_X);
        state = ST_MAKING_STEP;
        mainWindow->update();
    }

    if (cmd == "wrong login or password\n")
             QMessageBox::information( dialog_->getParent(), QString("Attention"),
                                       QString("wrong login or password" ));
    if (cmd == "wrongcmd\n")
        QMessageBox::information( dialog_->getParent(), QString("Attention"),
                                      QString("wrong cmd" ));
    if (cmd == "found:x")
    {
        mySymbol = SM_X;
        state = ST_MAKING_STEP;
    }
    if (cmd == "found:o")
    {
        mySymbol = SM_O;
        state = ST_WAITING_STEP;
    }

    if (cmd == "win")
    {
        socket->disconnectFromHost();
        QMessageBox::information( dialog_->getParent(), QString("Attention"),
                                      QString("You greate!" ));
    }
    if (cmd == "lose")
    {
        socket->disconnectFromHost();
        QMessageBox::information( dialog_->getParent(), QString("Attention"),
                                      QString("You louse..." ));
    }


       return;
}

QTcpSocket* net::getSocket()
{
    return socket;
}

Symbol net::getSymbol()
{
    return mySymbol;
}

void net::onDisconnected()
{
    myField->clear();
    state = ST_WAITING_STEP;
}
