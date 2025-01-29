#include"Network.h"
#include "mainwindow.h"


#define PORT 5555


QString Network::getStr() const
{
    return _str;
}

QTcpSocket *Network::getClientSocket() const
{
    return _clientSocket;
}

void Network::setDbPtr(const std::shared_ptr<Data> &newDbPtr)
{
    _dbPtr = newDbPtr;
}

Network::Network(QWidget* pwgt) : QWidget(pwgt) {}

Network::~Network()
{
    _tcpServer->close();
}

void Network::connectServerOpen()
{
    _tcpServer = new QTcpServer();
    qDebug() << "сервер ---  " << _tcpServer;
    if(!_tcpServer->listen(QHostAddress::Any, PORT))
    {
        QMessageBox::information(0, "Server Error",
                                 "Unableto start the server:"
                                     +_tcpServer->errorString());
        _tcpServer->close();
        return;
    }
    connect(_tcpServer, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));
}

void Network::slotNewConnection(){
    _clientSocket = _tcpServer->nextPendingConnection();

    qDebug() << "соединение с клиентом ---  " << _clientSocket;
    qDebug() << _clientSocket->errorString();

    connect(_clientSocket, SIGNAL(disconnected()),
            _clientSocket, SLOT(deleteLater()));
    connect(_clientSocket, SIGNAL(readyRead()),
            this, SLOT(slotReadClient()));   
}

void Network::slotReadClient()
{
    _str.clear();
    _str.append(_clientSocket->readAll());
    qDebug() << "получаем от клиента ###  " << _str;
   dataProcessing();
    //emit ale();
}

// отправить
void Network::sendMessage(const QString &str)
{
    if(_clientSocket->write(str.toUtf8())!= -1)
        qDebug() << "отправляем клиенту ### " << str;
}

void Network::dataProcessing()
{
    QStringList list;
    bool b;
    //qDebug() << "получили _str- " << getStr();
     int i = _str[0].digitValue();
    //qDebug() << "i ------ " << i;
    switch(i)
    {
    case 1:
        list = _str.sliced(1).split('\n');
        b = _dbPtr->insirtDataUser(list[0], list[1], list[2]);
        if(b)
        {
            sendMessage("true");
            _strLogin = list[1];
        }
        else sendMessage("error");
    break;
    case 2:
        list = _str.sliced(1).split('\n');
        b = _dbPtr->entranceDataUser(list[0], list[1]);
        if(b)
        {
            sendMessage("true");
            _strLogin = list[1];
        }
        else sendMessage("error");
    break;
    case 3:
        list = _str.sliced(1).split('\n');
        b = _dbPtr->insertDataMessageAll(list[0], list[1]);
        if(b) sendMessage("true");
        else sendMessage("error");
    break;
    case 4:
        list = _str.sliced(1).split('\n');
        b = _dbPtr->insertDataMessage(list[0], list[1], list[2]);
        if(b) sendMessage("true");
        else sendMessage("error");
    break;
    case 5:
        sendMessage("1" + _dbPtr->readDataUsersLogin(_str.sliced(1)));
        break;
    default:
        sendMessage("error");
        break;
    }
}


