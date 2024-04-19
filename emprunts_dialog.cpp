#include "emprunts_dialog.h"
#include "ui_emprunts_dialog.h"

#include<QMessageBox>
#include<QDebug>


emprunts_dialog::emprunts_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::emprunts_dialog)
{
    ui->setupUi(this);
    if (!conn.connOpen())
        ui->label_status->setText("Failed to connect to the database");
    else
        ui->label_status->setText("Connected to database");



}

emprunts_dialog::~emprunts_dialog()
{
    delete ui;
}

void emprunts_dialog::on_pushButton_init_clicked()
{
    ui->lineEdit_id->setText("");
    QDate currentDate = QDate::currentDate();
    ui->lineEdit_date_emp->setDate(currentDate);
    ui->lineEdit_date_ret->setDate(currentDate);

    ui->lineEdit_id->clear();
    ui->lineEdit_code_adhr->clear();
    ui->lineEdit_code->clear();
    ui->lineEdit_titre->clear();
    ui->lineEdit_nbrp->clear();
    ui->lineEdit_auteur->clear();
    ui->lineEdit_etat->clear();
    ui->lineEdit_nom_adr->clear();
    ui->lineEdit_nbrEmp_adr_2->clear();

    ui->comboBox_id_adr->clear();
    ui->comboBox_id_livre->clear();

    ui->pushButton_save->setEnabled(true);

}




void emprunts_dialog::on_pushButton_save_clicked()
{
    emprunts E;
    E.set_id(ui->lineEdit_id->text().toInt());
    E.set_codeadhr(ui->lineEdit_code_adhr->text().toInt());
    E.set_CodeLiv(ui->lineEdit_code->text().toInt());


    E.set_dateEmp(ui->lineEdit_date_emp->date().toString());
    E.set_dateRet(ui->lineEdit_date_ret->date().toString());
    E.Ajouter();
}

void emprunts_dialog::on_pushButton_update_clicked()
{
    emprunts E;
    E.set_id(ui->lineEdit_id->text().toInt());
    E.set_codeadhr(ui->lineEdit_code_adhr->text().toInt());
    E.set_CodeLiv(ui->lineEdit_code->text().toInt());

    E.set_dateEmp(ui->lineEdit_date_emp->text());
    E.set_dateRet(ui->lineEdit_date_ret->text());
    E.Modifier();
}

void emprunts_dialog::on_pushButton_delete_clicked()
{
    emprunts E;
    E.set_id(ui->lineEdit_id->text().toInt());
    E.Supprimer();
}


void emprunts_dialog::on_pushButton_load_clicked()
{
    emprunts E;

    QSqlQueryModel * modal_e = new QSqlQueryModel();
    modal_e = E.Load();
    ui->tableView->setModel(modal_e);

    QSqlQueryModel * modal= new QSqlQueryModel();
    adherents A;
    modal = A.Load();
    ui->comboBox_id_adr->setModel(modal);

    QSqlQueryModel * modal_l=new QSqlQueryModel();
    Livre lv;
    modal_l=lv.Load();
    ui->comboBox_id_livre->setModel(modal_l);

    qDebug() << modal->rowCount();
}

void emprunts_dialog::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();
    DBConnexion conn;
    if (!conn.connOpen())
    {
        qDebug() << "FAILED TO OPEN DATABASE";
        return;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM emprunts WHERE id='" + val + "'");
    if (qry.exec())
    {
        while (qry.next())
        {
            ui->lineEdit_id->setText(qry.value(0).toString());
            ui->lineEdit_code->setText(qry.value(1).toString());
            ui->lineEdit_code_adhr->setText(qry.value(2).toString());

            QString dateEmpString = qry.value(3).toString();
            QString dateRetString = qry.value(4).toString();

            QDate dateEmp = QDate::fromString(dateEmpString, "yyyy-MM-dd");
            QDate dateRet = QDate::fromString(dateRetString, "yyyy-MM-dd");

            ui->lineEdit_date_emp->setDate(dateEmp);
            ui->lineEdit_date_ret->setDate(dateRet);

            // Update combo boxes
            QString codeLivre = qry.value(1).toString(); // Assuming codeLivre is related to the combo box
            QString codeAdherent = qry.value(2).toString(); // Assuming codeAdherent is related to the combo box

            // Update combo box for Livre
            int indexLivre = ui->comboBox_id_livre->findText(codeLivre);
            if (indexLivre >= 0)
                ui->comboBox_id_livre->setCurrentIndex(indexLivre);

            // Update combo box for Adherents
            int indexAdherent = ui->comboBox_id_adr->findText(codeAdherent);
            if (indexAdherent >= 0)
                ui->comboBox_id_adr->setCurrentIndex(indexAdherent);
        }
        conn.connClose();
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), qry.lastError().text());
    }

    ui->pushButton_delete->setEnabled(true);
    ui->pushButton_update->setEnabled(true);
    ui->pushButton_init->setEnabled(true);
}



void emprunts_dialog::on_comboBox_id_livre_currentIndexChanged(const QString &arg1)
{
    QString val = ui->comboBox_id_livre->currentText();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Livre where CodeLivre='"+val+"'");
    if (qry.exec())
    {
        while (qry.next())
        {
            ui->lineEdit_code->setText(qry.value(0).toString());
            ui->lineEdit_titre->setText(qry.value(1).toString());
            ui->lineEdit_nbrp->setText(qry.value(2).toString());
            ui->lineEdit_auteur->setText(qry.value(3).toString());
            ui->lineEdit_etat->setText(qry.value(4).toString());
        }
        conn.connClose();

    }
    else
    {
        qDebug() << "Error executing query: " << qry.lastError().text();
    }
}

void emprunts_dialog::on_comboBox_id_adr_currentIndexChanged(const QString &arg1)
{
    QString val = ui->comboBox_id_adr->currentText();
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from adherents where code_adhr='"+val+"'");
    if (qry.exec())
    {
        while (qry.next())
        {
            ui->lineEdit_code_adhr->setText(qry.value(0).toString());
            ui->lineEdit_nom_adr->setText(qry.value(1).toString());
            ui->lineEdit_nbrEmp_adr_2->setText(qry.value(2).toString());
        }
        conn.connClose();

    }
    else
    {
        qDebug() << "Error executing query: " << qry.lastError().text();
    }
}


