#include "mainwindow.h"
#include "ui_mainwindow.h"


int MainWindow::kInstanceCount = 0;

MainWindow::MainWindow(QString userLogin, Network *socket,
                       std::shared_ptr<Data> dbPtr,
                       QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _userLogin(userLogin)
{
    ui->setupUi(this);
    kInstanceCount++;
    if(socket)
        _socket = socket;
    else
    {
        _socket = new Network();
        _socket->connectClientOpen();

    }
    if(dbPtr)
        _dbPtr = dbPtr;
    else
        _dbPtr = std::make_shared<Data>();


    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChats);
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
    kInstanceCount--;
    if(kInstanceCount <= 0)
    {
        qApp->exit(0);
    }    
}

MainWindow *MainWindow::createClient(Network *socket,
                                std::shared_ptr<Data> dbPtr)
{
    StartScreen s(socket, dbPtr);
    auto result = s.exec();
    if(result == QDialog::Rejected)
    {
        return nullptr;
    }
    auto w = new MainWindow(s.getUserLogin(), s.getSocket(), s.getData());
    w->setAttribute(Qt::WA_DeleteOnClose);

    return w;
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageBatton_clicked();
}


void MainWindow::on_sendMessageBatton_clicked()
{    
    QString str = "3" + _userLogin +"\n" + ui->messageLineEdit->text();
    ui->messageLineEdit->clear();
    _socket->sendMessage(str);
    //qDebug() << "пришла строка - " << str;

    QEventLoop loop;
    QTimer timer2;
    timer2.setInterval(400); //5 sec
    connect (&timer2, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer2.start();
    loop.exec();

    //qDebug() << "пришла строка - " << _socket->getStr();
    if(_socket->getStr() == "error")
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Ошибка данных"));
}

void MainWindow::on_privateMessageSendButton_clicked()
{
   _socket->sendMessage("5"+getUserLogin());
    QEventLoop loop;
    QTimer timer2;
    timer2.setInterval(500); //5 sec
    connect (&timer2, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer2.start();
    loop.exec();

    QDialog dial(this);
    dial.setModal(true);
    QVBoxLayout *l = new QVBoxLayout();
    dial.setLayout(l);
    auto userListWgt = new QListWidget(&dial);
    l->addWidget(userListWgt);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dial);
    l->addWidget((buttonBox));
    connect(buttonBox, &QDialogButtonBox::accepted, &dial, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);

    QStringList userList = _socket->getStr().sliced(1).split('\n');
    //qDebug() << "userList - " << userList;

    if(!userList.isEmpty() && userList[0] == "")
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Абонентов нет"));
        return;
    }

    for(auto user : userList)
    {
        userListWgt->addItem(user);
    }
    userListWgt->setCurrentRow(0);

    auto result = dial.exec();

    if(result == QDialog::Accepted &&
        userListWgt->currentItem())
    {
        QString str = "4" + _userLogin + "\n" + userListWgt->currentItem()->text() +
                      "\n" + ui->messageLineEdit->text();

        _socket->sendMessage(str);
        ui->messageLineEdit->clear();
        QEventLoop loop;
        QTimer timer2;
        timer2.setInterval(400); //5 sec
        connect (&timer2, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer2.start();
        loop.exec();

        //qDebug() << "пришла строка - " << _socket->getStr();
        if(_socket->getStr() == "error")
            QMessageBox::critical(this,
                                  tr("Error"),
                                  tr("Ошибка данных"));
    }
}

void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient(_socket, _dbPtr);
    if(w)
        w->show();
}

void MainWindow::on_actionCloseClient_triggered()
{
    this->close();
}

void MainWindow::updateChats()
{    
    auto chat = _dbPtr->readDataMessageAll();
    if(ui->commonChatBrowser->toPlainText()!= chat)
    {
        ui->commonChatBrowser->setText(chat);
        ui->commonChatBrowser->moveCursor(QTextCursor::End);
    }

    chat.clear();

    chat = _dbPtr->readDataMessage(_userLogin);
    if(ui->privateChatBrowser->toPlainText()!= chat)
    {
        ui->privateChatBrowser->setText(chat);
        ui->privateChatBrowser->moveCursor(QTextCursor::End);
    }}

QString MainWindow::getUserLogin() const
{
    return _userLogin;
}

