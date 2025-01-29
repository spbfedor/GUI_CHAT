#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <memory>
#include "Network.h"


namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(Network *socket /*= nullptr*/,
                         std::shared_ptr<Data> _dbPtr,
                         QWidget *parent = nullptr );
    ~StartScreen();
    void setLoginForm();
    void setRegistrationForm();
    void setUserLogin(const QString &userLogin);

    QString getUserLogin() const;
    Network *getSocket() const;
    std::shared_ptr<Data> getData() const;

public slots:
    void onLoggedIn(QString userLogin);
    void onRejectedRequested();

private:
    Ui::StartScreen *ui;
    QString _userLogin;
    Network *_socket;
    std::shared_ptr<Data> _dbPtr;
};

#endif // STARTSCREEN_H
