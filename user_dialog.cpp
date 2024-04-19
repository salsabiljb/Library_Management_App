#include "user_dialog.h"
#include "ui_user_dialog.h"
#include <QPixmap>
#include <QMessageBox>


user_dialog::user_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_dialog)
{
    ui->setupUi(this);
    if (!conn.connOpen())
       { ui->label_user_status->setText("Failed to connect to the database");}
    else
    {ui->label_user_status->setText("Connected to database");}
    connect(ui->pushButton_search, &QPushButton::clicked, this, &user_dialog::on_pushButton_search_clicked);



}

user_dialog::~user_dialog()
{
    delete ui;
}

void user_dialog::on_pushButton_load_user_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();

    Livre L;
    modal = L.Load();

    ui->tableView_user->setModel(modal);

    conn.connOpen();
    QSqlQueryModel * modale= new QSqlQueryModel();
    QSqlQuery *qry =new QSqlQuery(conn.get_mydb());
    qry->prepare("select DISTINCT Auteur from Livre ");
    qry->exec();
    modale->setQuery(*qry);
    ui->comboBox_auteur->setModel(modale);

    conn.connClose();


    qDebug() <<modal->rowCount();
    qDebug() <<modale->rowCount();


}



void user_dialog::on_tableView_user_activated(const QModelIndex &index)
{
    QString val=ui->tableView_user->model()->data(index).toString();


    if(!conn.connOpen())
    {
        qDebug() <<"Failed to connect to the database";
        return ;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from Livre where Titre=' "+val+" ' or Nbr_pages = ' "+val+ " ' or Auteur= ' " +val+" ' ");
    if(qry.exec())
    {

        conn.connClose();
    }
    else
    {
        qDebug() <<"Failed to connect to the database";
    }

}



void user_dialog::on_comboBox_auteur_currentIndexChanged(const QString &arg1)
{
    QString Auteur= ui->comboBox_auteur->currentText();
    conn.connOpen();
    QSqlQuery qry;
   qry.prepare("select * from Livre where Auteur='"+Auteur+"'");


    if (qry.exec())
    {
       while (qry.next()) {

                    ui->lineEdit_auteur->setText(qry.value(3).toString());
}
        conn.connClose();

    }
    else
    {
        qDebug() << "Error executing query: " << qry.lastError().text();
    }
}



void user_dialog::on_pushButton_search_clicked()
{
    conn.connOpen();


    QString etat;

    if (ui->checkBox_emprunte->isChecked())
    {
            qDebug()<<"etat emprunt";
            etat="emprunte";
    }
    else if (ui->checkBox_non_emprunte->isChecked())
    {
            qDebug()<<"etat non emprunt";
            etat="non emprunte";
    }

    QString filter_auteur=ui->lineEdit_auteur->text();
    QString filter_nbrsup=ui->lineEdit_maxpages->text();
    QString filter_nbrinf=ui->lineEdit_minpages->text();
    QString filter_etat=etat;
    QString filter_titre=ui->lineEdit_titre->text();



    QString queryStr = "SELECT * FROM Livre WHERE 1=1";

    if (!filter_titre.isEmpty())
    {
        queryStr += " AND Titre = '" + filter_titre + "'";
    }
    if (!filter_auteur.isEmpty())
    {
        queryStr += " AND Auteur = '" + filter_auteur + "'";
    }
    if (!filter_nbrinf.isEmpty() && filter_nbrsup.isEmpty())
    {
        queryStr += " AND Nbr_pages >= " + filter_nbrinf;
    }

    if (!filter_nbrsup.isEmpty() && filter_nbrinf.isEmpty())
    {
        queryStr += " AND Nbr_pages <= " + filter_nbrsup;
    }

    if (!filter_nbrsup.isEmpty() && !filter_nbrinf.isEmpty())
    {
        queryStr += " AND Nbr_pages BETWEEN " + filter_nbrinf + " AND " + filter_nbrsup;
    }

    if (!filter_etat.isEmpty())
    {
        queryStr += " AND Etat = '" + etat + "'";
    }

    QSqlQueryModel* modal = new QSqlQueryModel();
    modal->setQuery(queryStr);

    ui->tableView_user->setModel(modal);

    conn.connClose();
}

void user_dialog::on_pushButton_init_clicked()
{
    ui->lineEdit_auteur->clear();
    ui->lineEdit_maxpages->clear();
    ui->lineEdit_minpages->clear();
    ui->comboBox_auteur->clear();
    ui->lineEdit_titre->clear();
    ui->checkBox_emprunte->setChecked(false);
    ui->checkBox_non_emprunte->setChecked(false);
}

void user_dialog::on_pushButton_stat_clicked()
{
    StatDialog = new stat_dialog(this);
    StatDialog->show();
}


