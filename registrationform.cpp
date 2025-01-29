#include "registrationform.h"
#include "ui_registrationform.h"
#include <QMessageBox>
#include <QTimer>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_loginButton_clicked()
{
    emit loginRequested();
}

void RegistrationForm::setData(std::shared_ptr<Data> dbPtr)
{
    _dbPtr = dbPtr;
}

void RegistrationForm::on_buttonBox_accepted()
{
    //_socket->clearStr();
    if(ui->nameEdit->text().isEmpty() || ui->loginEdit->text().isEmpty() ||
        ui->passwordEdit->text().isEmpty() || ui->PasswordConfirmEdit->text().isEmpty())
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Поля должны быть заполнены"));
        return;
    }
    if(ui->passwordEdit->text() !=
        ui->PasswordConfirmEdit->text())
    {
        QMessageBox::critical(this,
                              tr("Error"),
                              tr("Пароли не совпадают"));
        return;
    }
    QString str = "1" + ui->nameEdit->text()+ "\n" + ui->loginEdit->text()+ "\n" +
                  ui->passwordEdit->text();
    _socket->sendMessage(str);

    QEventLoop loop;
    QTimer timer2;
    timer2.setInterval(400); //5 sec
    connect (&timer2, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer2.start();
    loop.exec();

    if(_socket->getStr() == "error")
    {
        QMessageBox::critical(this,  tr("Error"), tr("Такой логин уже есть"));
        return;
    }
    emit accepted(ui->loginEdit->text());

}

void RegistrationForm::on_buttonBox_rejected()
{
    emit rejected();
}

void RegistrationForm::setSocket(Network *socket)
{
    _socket = socket;
}

