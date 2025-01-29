#include"Network.h"
#include "mainwindow.h"
#include <QDebug>

#define SERVER_IP "localhost"
#define PORT 5555


Network::Network(QWidget* pwgt ) : QWidget(pwgt) {}
Network::~Network() = default;

void Network::connectClientOpen()
{
    _clientSocket = new QTcpSocket();
    _clientSocket->connectToHost(SERVER_IP, PORT);
    qDebug() << "соединение с сервером ---  " << _clientSocket;
    qDebug() << _clientSocket->errorString();
    //connect(_clientSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(_clientSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
}

// отправить
void Network::sendMessage(const QString &str)
{
        if(_clientSocket->write(str.toUtf8())!= -1)
            qDebug() << "отправлено серверу ###  " << str;
}

void Network::connectClose(/*QTcpServer* _tcpServer*/)
{
	//std::cout << "Disconnect." << std::endl;
    _clientSocket->close();
}

void Network::slotReadyRead()
{
    _str.clear();
    _str.append(_clientSocket->readAll());
    qDebug() << "пришла строка ###" << _str;
    dataProcessing();
}

QString Network::dataProcessing()
{
    if(_str.isEmpty())
        _str = "error";
        return "error";

    if(_str[0] == '1'){
        _strUser = _str.sliced(1);
        qDebug() << "_strUser - " << _strUser << "  ###";
        return _strUser;
    }

    if(_str == "true")
    {
        _str = "true";
        return "true";
    }

    _str = "error";
    return "error";
}

QString Network::getStr() const
{
    return _str;
}

QString Network::getStrUser() const
{
    return _strUser;
}






