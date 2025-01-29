#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include <memory>
#include "Network.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();
    void setSocket(Network *socket);
    void setData(std::shared_ptr<Data> dbPtr);

signals:
    void loginRequested();
    void accepted(QString userLogin);
    void rejected();

private slots:
    void on_loginButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::RegistrationForm *ui;
    Network *_socket;
    std::shared_ptr<Data> _dbPtr;
};

#endif // REGISTRATIONFORM_H
