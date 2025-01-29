#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->userList->setReadOnly(true);
    ui->messagesVew->setReadOnly(true);
    ui->userList->setTextColor(QColor(0, 150, 170, 200));

    _dbPtr = std::make_shared<Data>();
    _dbPtr->openData();
    _dbPtr->createDataTable();
    server.connectServerOpen();
    server.setDbPtr(_dbPtr);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChats);
    timer->start(100);
//    auto timer1 = new QTimer(this);
//    connect(timer1, &QTimer::timeout, this, &MainWindow::sendChatAll);
//    timer1->start(100000);
}

MainWindow::~MainWindow()
{
    _dbPtr->closeData();
    delete ui;
}

void MainWindow::updateChats()
{
    auto chatMessages = _dbPtr->readDataMessageAll();

    if(ui->messagesVew->toPlainText()!= chatMessages)
    {
        ui->messagesVew->setText(chatMessages);
        ui->messagesVew->moveCursor(QTextCursor::End);
    }

    auto usersLogin = _dbPtr->readDataUsers();

    if(ui->userList->toPlainText()!= usersLogin)
    {
        ui->userList->setText(usersLogin);
        ui->userList->moveCursor(QTextCursor::End);
    }    
}

std::shared_ptr<Data> MainWindow::dbPtr() const
{
    return _dbPtr;
}




