#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "admin_dialog.h"
#include"user_dialog.h"
#include "DBConnexion.h"
#include<QtSql>
#include<QDebug>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
     DBConnexion conn;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_pushButton_login_clicked();



    void on_pushButton_confirm_clicked();
    void goToTab_in();
    void goToTab_up();




private:
    Ui::MainWindow *ui;
    admin_dialog *admin ;
    user_dialog *user;
};

#endif // MAINWINDOW_H
