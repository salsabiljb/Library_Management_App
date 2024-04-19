#include "admin_dialog.h"
#include "ui_admin_dialog.h"
#include <QPixmap>
#include <QMessageBox>




admin_dialog::admin_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &admin_dialog::goToTab_next);



  //  QPixmap pix2("./livrepic.png");
   // int w2 = ui->label_admin_pic_livre->width();
   // int h2= ui->label_admin_pic_livre->height();
  //  ui->label_admin_pic_livre->setPixmap(pix2.scaled(w2,h2,Qt::KeepAspectRatio));


}

admin_dialog::~admin_dialog()
{
    delete ui;
}



void admin_dialog::goToTab_next()
{
    // Switch to the "tab" widget
    ui->Admin1->setCurrentIndex(1); // Assuming the index of "tab" is 1
}



void admin_dialog::on_pushButton_adherents_clicked()
{
    AdhDialog = new adherentsdialog(this);
    AdhDialog->show();
}

void admin_dialog::on_pushButton_emprunts_clicked()
{
    Empr =new emprunts_dialog(this);
    Empr ->show();
}

void admin_dialog::on_pushButton_livre_dialog_clicked()
{
    livdialog = new livre_dialog(this);
    livdialog->show();
}








/**************************************************** users ********************************************************************/



void admin_dialog::on_tableView_user_activated(const QModelIndex &index)
{
    QString val=ui->tableView_user->model()->data(index).toString();

    DBConnexion conn ;
    if(!conn.connOpen())
    {
        qDebug()<<"FAILED TO OPEN DATABASE";
        return;

    }

    conn.connOpen();
    QSqlQuery qry ;
    qry.prepare("select * from Login where idlogin='"+val+"'");

    if(qry.exec( ))
    {
        while(qry.next())
        {
        }
        conn.connClose();
    }

    else
    {

        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }


}

void admin_dialog::on_pushButton_load_user_clicked()
{
    DBConnexion conn;
        conn.connOpen();
        QSqlQueryModel *modal = new QSqlQueryModel();

        QSqlQuery* qry = new QSqlQuery(conn.get_mydb());
        qry->prepare("SELECT idlogin,User_name,PSW FROM Login where Role='user'");

        if(qry->exec()) {
            modal->setQuery(*qry);
            ui->tableView_user->setModel(modal); // Set the model to the table view
        } else {
            qDebug() << "Erreur lors de l'exécution de la requête SQL:" << qry->lastError().text();
        }

        conn.connClose();
}

void admin_dialog::on_pushButton_delete_user_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_user->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::information(this, "Information", "Please select a user to delete.");
        return;
    }

    int row = selectedIndexes.first().row(); // Assuming you want to delete the first selected row
    QString idLogin = ui->tableView_user->model()->index(row, 0).data().toString(); // Assuming idLogin is in the first column

    DBConnexion conn;
    if (!conn.connOpen()) {
        qDebug() << "FAILED TO OPEN DATABASE";
        return;
    }

    QSqlQuery qry(conn.get_mydb());
    qry.prepare("DELETE FROM Login WHERE idlogin = :id");
    qry.bindValue(":id", idLogin);

    if (qry.exec()) {
        qDebug() << "User deleted successfully.";
        // Refresh the user list after deletion
        on_pushButton_load_user_clicked();
    } else {
        qDebug() << "Error deleting user:" << qry.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete user.");
    }

    conn.connClose();
}




/**************************************************** Admins ********************************************************************/

void admin_dialog::on_pushButton_load_admin_clicked()
{
    DBConnexion conn;
    if(!conn.connOpen()) {
        qDebug() << "FAILED TO OPEN DATABASE";
        return;
    }

    conn.connOpen();
    QSqlQueryModel *modal = new QSqlQueryModel();

    QSqlQuery* qry = new QSqlQuery(conn.get_mydb());
    qry->prepare("SELECT idlogin, User_name, PSW FROM Login where Role='admin'");

    if(qry->exec()) {
        modal->setQuery(*qry);
        ui->tableView_admin->setModel(modal); // Set the model to the table view
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête SQL:" << qry->lastError().text();
    }

    conn.connClose();
}

void admin_dialog::on_tableView_admin_activated(const QModelIndex &index)
{
    QString val = ui->tableView_admin->model()->data(index).toString();

    DBConnexion conn;
    if (!conn.connOpen()) {
        qDebug() << "FAILED TO OPEN DATABASE";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM Login where idlogin=:id");
    qry.bindValue(":id", val);

    if (qry.exec()) {
        while (qry.next()) {
            // Process data if needed
        }
        conn.connClose();
    } else {
        QMessageBox::critical(this, "Error:", qry.lastError().text());
    }
}

void admin_dialog::on_pushButton_add_admin_clicked()
{
    QString newUser = ui->lineEdit_new_usr_admin->text();
    QString newPassword = ui->lineEdit_new_pwd_admin->text();

    DBConnexion conn;
    if (!conn.connOpen()) {
        qDebug() << "FAILED TO OPEN DATABASE";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("INSERT INTO Login (User_name, PSW, Role) VALUES (:user, :pwd, 'admin')");
    qry.bindValue(":user", newUser);
    qry.bindValue(":pwd", newPassword);

    if (qry.exec()) {
        qDebug() << "Admin added successfully.";
        // Refresh the admin list after addition
        on_pushButton_load_admin_clicked();
    } else {
        qDebug() << "Error adding admin:" << qry.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to add admin.");
    }

    conn.connClose();
}
void admin_dialog::on_pushButton_update_admin_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_admin->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::information(this, "Information", "Please select an admin to update.");
        return;
    }

    int row = selectedIndexes.first().row(); // Assuming you want to update the first selected row
    QString idLogin = ui->tableView_admin->model()->index(row, 0).data().toString(); // Assuming idLogin is in the first column

    QString newUser = ui->lineEdit_new_usr_admin->text();
    QString newPassword = ui->lineEdit_new_pwd_admin->text();

    DBConnexion conn;
    if (!conn.connOpen()) {
        qDebug() << "FAILED TO OPEN DATABASE";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("UPDATE Login SET User_name = :user, PSW = :pwd WHERE idlogin = :id");
    qry.bindValue(":user", newUser);
    qry.bindValue(":pwd", newPassword);
    qry.bindValue(":id", idLogin);

    if (qry.exec()) {
        qDebug() << "Admin updated successfully.";
        // Refresh the admin list after update
        on_pushButton_load_admin_clicked();
    } else {
        qDebug() << "Error updating admin:" << qry.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to update admin.");
    }

    conn.connClose();
}

void admin_dialog::on_pushButton_delete_admin_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_admin->selectionModel()->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        QMessageBox::information(this, "Information", "Please select an admin to delete.");
        return;
    }

    int row = selectedIndexes.first().row(); // Assuming you want to delete the first selected row
    QString idLogin = ui->tableView_admin->model()->index(row, 0).data().toString(); // Assuming idLogin is in the first column

    DBConnexion conn;
    if (!conn.connOpen()) {
        qDebug() << "FAILED TO OPEN DATABASE";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("DELETE FROM Login WHERE idlogin = :id");
    qry.bindValue(":id", idLogin);

    if (qry.exec()) {
        qDebug() << "Admin deleted successfully.";
        // Refresh the admin list after deletion
        on_pushButton_load_admin_clicked();
    } else {
        qDebug() << "Error deleting admin:" << qry.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete admin.");
    }

    conn.connClose();
}

void admin_dialog::on_pushButton_init_admin_clicked()
{
    ui->lineEdit_new_pwd_admin->setText("");
    ui->lineEdit_new_usr_admin->setText("");

}
