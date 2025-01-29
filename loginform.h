#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <memory>
#include "Network.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();
    void setSocket(Network *socket);
    void setDbPtr(const std::shared_ptr<Data> &DbPtr);

signals:
    void registerRequested();
    void accepted( QString userLogin);
    void rejected();

private slots:
    void on_buttonBox_rejected();
    void on_registrationPushButton_clicked();
    void on_buttonBox_accepted();

private:
    Ui::LoginForm *ui;
    Network *_socket;
    std::shared_ptr<Data> _dbPtr;
};

#endif // LOGINFORM_H
