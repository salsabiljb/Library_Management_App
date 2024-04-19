#ifndef LIVRE_DIALOG_H
#define LIVRE_DIALOG_H

#include<Livre.h>

#include <QDialog>

#include<QtSql>
#include<QDebug>
#include "DBConnexion.h"

namespace Ui {
class livre_dialog;
}

class livre_dialog : public QDialog
{
    Q_OBJECT

public:
    DBConnexion conn;
    explicit livre_dialog(QWidget *parent = 0);
    ~livre_dialog();

private slots:
     void on_pushButton_save_clicked();

     void on_pushButton_edit_clicked();

     void on_pushButton_delete_clicked();

     void on_pushButton_load_clicked();

     void on_pushButton_init_clicked();

     void on_tableView_activated(const QModelIndex &index);

     void on_pushButton_stats_livre_clicked();

private:
    Ui::livre_dialog *ui;
};

#endif // LIVRE_DIALOG_H
