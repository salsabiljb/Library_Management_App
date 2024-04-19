#ifndef USER_DIALOG_H
#define USER_DIALOG_H

#include <QDialog>
#include "DBConnexion.h"
#include <QString>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include"Livre.h"
#include "stat_dialog.h"

namespace Ui {
class user_dialog;
}

class user_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit user_dialog(QWidget *parent = 0);

    DBConnexion conn;
    ~user_dialog();

private slots:
    void on_pushButton_load_user_clicked();

    void on_tableView_user_activated(const QModelIndex &index);


    void on_comboBox_auteur_currentIndexChanged(const QString &arg1);


    void on_pushButton_search_clicked();

    void on_pushButton_init_clicked();

    void on_pushButton_stat_clicked();

private:
    Ui::user_dialog *ui;
    stat_dialog *StatDialog;
};

#endif // USER_DIALOG_H
