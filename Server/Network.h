#pragma once
#include <QtCore/QString>
#include <QTcpServer>
#include <QTextEdit>
#include <QTcpSocket>
#include <QMessageBox>
#include <QWidget>
#include<QVector>
#include"Data.h"

class Network: QWidget
{
    Q_OBJECT;

    QTcpServer* _tcpServer;
    QTcpSocket* _clientSocket = nullptr;
    QString _str;
    std::shared_ptr<Data> _dbPtr;


public:
    QString _strLogin;
    Network(QWidget* pwgt = 0);
    ~Network();
    void connectServerOpen();    
    void sendMessage(const QString &str);

    void connectClose();
    QString getStr() const;

    QTcpSocket *getClientSocket() const;

    void setDbPtr(const std::shared_ptr<Data> &newDbPtr);

signals:
    void ale();

public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void dataProcessing();
};
