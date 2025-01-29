#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Network.h"
#include <memory>
#include "startscreen.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString userLogin, Network *socket = nullptr,
                        std::shared_ptr<Data> dbPtr = nullptr,
                        QWidget *parent = nullptr);

    ~MainWindow();
    static MainWindow* createClient(Network *socket  = nullptr, std::shared_ptr<Data> dbPtr = nullptr);

    static int kInstanceCount;

    QString getUserLogin() const;

private slots:
    void on_messageLineEdit_returnPressed();
    void on_sendMessageBatton_clicked();
    void on_privateMessageSendButton_clicked();
    void on_actionOpen_another_client_triggered();
    void on_actionCloseClient_triggered();
    void updateChats();

private:
    Ui::MainWindow *ui;
    Network *_socket;
    QString _userLogin;
    std::shared_ptr<Data> _dbPtr;
};

#endif // MAINWINDOW_H
