#ifndef ADMIN_DIALOG_H
#define ADMIN_DIALOG_H

#include <QDialog>
#include "livre_dialog.h"
#include "adherentsdialog.h"
#include "emprunts_dialog.h"


namespace Ui {
class admin_dialog;
}

class admin_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit admin_dialog(QWidget *parent = 0);
    ~admin_dialog();

private slots:

    void goToTab_next();

    void on_pushButton_adherents_clicked();

    void on_pushButton_emprunts_clicked();

    void on_pushButton_livre_dialog_clicked();

    void on_tableView_user_activated(const QModelIndex &index);

    void on_pushButton_load_user_clicked();

    void on_pushButton_delete_user_clicked();

    void on_pushButton_load_admin_clicked();

    void on_tableView_admin_activated(const QModelIndex &index);

    void on_pushButton_add_admin_clicked();

    void on_pushButton_update_admin_clicked();

    void on_pushButton_delete_admin_clicked();

    void on_pushButton_init_admin_clicked();

private:
    Ui::admin_dialog *ui;
    livre_dialog *livdialog;
    adherentsdialog *AdhDialog;
    emprunts_dialog *Empr;

};

#endif // ADMIN_DIALOG_H
