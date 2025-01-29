#pragma once
#include <QTextEdit>
#include <QTcpSocket>
#include <QMessageBox>
#include <QWidget>
#include <iostream>
#include "Data.h"

class Network: public  QWidget
{
    Q_OBJECT;

   QTcpSocket * _clientSocket;
    QString _str;
   QString _strUser;

public:
    Network(QWidget* pwgt = 0);
    ~Network();
    void connectClientOpen();
    void sendMessage(const QString &str);
    void connectClose();
    QString getStr() const;
    QString dataProcessing();
    QString getStrUser() const;

public slots:
    void slotReadyRead();
};
