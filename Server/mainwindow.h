#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Network.h"
#include <memory>
#include <QStringList>
#include<QChar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::shared_ptr<Data> dbPtr() const;

public slots:
    void updateChats();    

private:
    Ui::MainWindow *ui;
    Network server;
    std::shared_ptr<Data> _dbPtr;
    QString login;
};
#endif // MAINWINDOW_H
