#ifndef EMPRUNTS_DIALOG_H
#define EMPRUNTS_DIALOG_H

#include <QDialog>
#include <QDialog>
#include <emprunts.h>
#include<QtSql>
#include<QDebug>
#include "DBConnexion.h"
#include"adherents.h"
#include"adherentsdialog.h"

#include"Livre.h"
#include"livre_dialog.h"
namespace Ui {
class emprunts_dialog;
}

class emprunts_dialog : public QDialog
{
    Q_OBJECT

public:
    DBConnexion conn;

    explicit emprunts_dialog(QWidget *parent = 0);
    ~emprunts_dialog();




private slots:
    void on_pushButton_init_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_load_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_comboBox_id_livre_currentIndexChanged(const QString &arg1);


    void on_comboBox_id_adr_currentIndexChanged(const QString &arg1);

private:
    Ui::emprunts_dialog *ui;
};

#endif // EMPRUNTS_DIALOG_H




