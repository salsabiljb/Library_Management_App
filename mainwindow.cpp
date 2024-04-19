#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_login_3, &QPushButton::clicked, this, &MainWindow::goToTab_in);
    connect(ui->pushButton_confirm_3, &QPushButton::clicked, this, &MainWindow::goToTab_up);

    if (!conn.connOpen()){
        ui->label_status->setText("FAILED TO OPEN DATABASE");
        ui->label_status_2->setText("FAILED TO OPEN DATABASE");}
    else {
        ui->label_status->setText("MP_DataBase CONNECTED!");
        ui->label_status_2->setText("MP_DataBase CONNECTED!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::goToTab_in()
{
    ui->tabWidget_home->setCurrentIndex(1); // Assuming the index of "tab" is 1
}

void MainWindow::goToTab_up()
{
    ui->tabWidget_home->setCurrentIndex(2); // Assuming the index of "tab" is 1
}

void MainWindow::on_pushButton_login_clicked()
{
   QString username = ui->lineEdit_username->text();
   QString password = ui->lineEdit_password->text();
   QString role;

  if(!conn.connOpen())
  {
      qDebug()<<"Failed to open the database";
      return;
  }

  if (ui->radioButton_admin->isChecked())
      {
              qDebug()<<"Admin checked";
              role="admin";
      }
      else if (ui->radioButton_user->isChecked())
      {
              qDebug()<<"User checked";
              role="user";
      }

  conn.connOpen();
  QSqlQuery qry;
  qry.prepare("select * from Login where User_name='"+username+"' and PSW='"+password+"' and Role='"+role+"' ");
  if (qry.exec( ))
  {
    int count=0;
    while (qry.next())
    {
        count++;
        qDebug()<<count;
    }
    if(count==1 && role=="admin")
    {
        QMessageBox:: information(this, "login", "username and password are correct");
        conn.connClose();
        admin = new admin_dialog(this);
        admin->show();
    }
    if(count==1 && role=="user")
    {
        QMessageBox:: information(this, "login", "username and password are correct");
        conn.connClose();
        user = new user_dialog(this);
        user->show();
    }
    if(count>1)
        ui->label_status->setText("username and password are duplicated");
    if(count<1)
        ui->label_status->setText("username and password are not correct");
}
}

void MainWindow::on_pushButton_confirm_clicked()
{
    QString new_username = ui->lineEdit_newuser->text();
    QString new_password = ui->lineEdit_newpwd->text();
    QString new_role = "user";

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

    conn.connOpen();
    if (ui->checkBox->isChecked()) {
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT User_name FROM Login WHERE User_name = ?");
    checkQuery.addBindValue(new_username);
    if(checkQuery.exec() && checkQuery.next()) {
        qDebug() << "Username already exists";
        conn.connClose();
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Login (User_name, PSW, Role) VALUES (?, ?, ?)");
    insertQuery.addBindValue(new_username);
    insertQuery.addBindValue(new_password);
    insertQuery.addBindValue(new_role);

    if(insertQuery.exec())
    {
        qDebug()<<"Data added successfully to the database";
        conn.connClose();
    }
}
    else
    {
        qDebug()<<"An error has occurred";
    }
}


