#pragma once
//#include"Func.h"
//#include<mysql/mysql.h>
#include<QtSql>
#include <QSqlDatabase>
#include<iostream>
#include<QDebug>
#include<QSqlDriver>
#include<QSqlDriverPlugin>
#include<QSqlQuery>

class Data
{
    QSqlDatabase _db;


public:
    Data();
    ~Data();

    void openData();
    void createDataTable();
    bool insirtDataUser(const QString &name, const QString &login, const QString &password);
    bool entranceDataUser(const QString &login, const QString &password);
    bool insertDataMessage(const QString &from, const QString &to, const QString &text);
    bool insertDataMessageAll(const QString &from, const QString &text);
    QString readDataUsersLogin(const QString &login);
    bool correctDataInputAbonent(const QString& login_to);
    QString readDataMessage(const QString &login);
    QString readDataMessageAll();
    void closeData();
    QString readDataUsers();
};
