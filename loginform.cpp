 #include "loginform.h"
#include "ui_loginform.h"
#include <QMessageBox>
#include <QTimer>


LoginForm::LoginForm(QWidget *parent) :

    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);    
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_buttonBox_rejected()
{
    emit rejected();
}

void LoginForm::on_registrationPushButton_clicked()
{
    emit registerRequested();
}

void LoginForm::on_buttonBox_accepted()
{

    if(ui->loginEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Поля должны быть заполнены"));
        return;
    }
    QString str = "2"+ ui->loginEdit->text() + "\n" + ui->passwordEdit->text();

    _socket->sendMessage(str);

    QEventLoop loop;
    QTimer timer2;
    timer2.setInterval(400);
    connect (&timer2, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer2.start();
    loop.exec();
    //qDebug() << "Логинимся и получаем - " << _socket->getStr();

    if(_socket->getStr() == "true")
    {
        emit accepted(ui->loginEdit->text());

    }
    else
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Пара логин/пароль невена"));
    return;
}

void LoginForm::setDbPtr(const std::shared_ptr<Data> &DbPtr)
{
    _dbPtr = DbPtr;
}

void LoginForm::setSocket(Network *socket)
{
    _socket = socket;
}



