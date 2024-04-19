#ifndef ADHERENTSDIALOG_H
#define ADHERENTSDIALOG_H

#include <QDialog>
#include<QtSql>
#include <QtDebug>
#include <QFileInfo>
#include<QMainWindow>
#include <QVector>
#include<QWidget>
#include<QPainter>
#include <QApplication>
#include"DBConnexion.h"
#include"qcustomplot.h"

namespace Ui {
class adherentsdialog;
}

class adherentsdialog : public QDialog
{
    Q_OBJECT

public:
    explicit adherentsdialog(QWidget *parent = 0);
    ~adherentsdialog();
    DBConnexion conn;
    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen()
    {
        mydb=QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("./MP_sujet8");

        if (!mydb.open())
        {
            qDebug()<<("Failed to open the database");
            return false;
        }
        else
        {
            qDebug()<<("Connected to database");
            return true;
        }
    }

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_init_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_stats_adh_clicked();

private:
    Ui::adherentsdialog *ui;

};

#endif // ADHERENTSDIALOG_H
