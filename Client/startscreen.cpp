#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(Network *socket,
                         std::shared_ptr<Data> dbPtr,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    if(socket)
        _socket = socket;
    else
    {
        _socket =  new Network();
        _socket->connectClientOpen();
    }
    if(dbPtr)
        _dbPtr = dbPtr;
    else
        _dbPtr = std::make_shared<Data>();

    ui->loginWidget->setSocket(_socket);
    ui->registrWidget->setSocket(_socket);

    connect(ui->loginWidget, &LoginForm::registerRequested, this, &StartScreen::setRegistrationForm);
    connect(ui->loginWidget, &LoginForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->loginWidget, &LoginForm::rejected, this, &StartScreen::onRejectedRequested);
    connect(ui->registrWidget, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);
    connect(ui->registrWidget, &RegistrationForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->registrWidget, &RegistrationForm::rejected, this, &StartScreen::onRejectedRequested);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartScreen::setRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::onLoggedIn( QString userLogin)
{

    _userLogin = userLogin;
    accept();
}

void StartScreen::onRejectedRequested()
{
    reject();
}

Network *StartScreen::getSocket() const
{
    return _socket;
}

void StartScreen::setUserLogin(const QString &userLogin)
{
    _userLogin = userLogin;
}

QString StartScreen::getUserLogin() const
{
    return _userLogin;
}

std::shared_ptr<Data> StartScreen::getData() const
{
    return _dbPtr;
}
