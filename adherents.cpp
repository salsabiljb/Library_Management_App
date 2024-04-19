#include "adherents.h"
#include"DBConnexion.h"
#include<QString>
#include<QTextStream>
#include<QDebug>
#include<QSqlDatabase>
#include<QSqlQuery>

adherents::adherents()
{
    n_code_adhr=0;
    n_nom_adr="";
    n_nbrEmp_adr=0;
}

adherents::~adherents()
{
}

int adherents::get_code_adhr()
{
    return n_code_adhr;
}

QString adherents::get_nom_adr()
{
    return n_nom_adr;
}

int adherents::get_nbrEmp_adr()
{
    return n_nbrEmp_adr;
}


void adherents::set_code_adhr(int i)
{
    n_code_adhr=i;
}

void adherents::set_nom_adr(QString n)
{
    n_nom_adr=n;
}

void adherents::set_nbrEmp_adr(int j)
{
    n_nbrEmp_adr=j;
}



void adherents::Ajouter()
{
    DBConnexion conn;
    conn.connOpen();
    if(!conn.connOpen())
        {
            qDebug()<<"Failed to open the database";
            return;
        }
    else
    {
        QSqlQuery qry;
        qry.prepare("insert into adherents (nom_adr,nbrEmp_adr) values ('"+n_nom_adr+"','"+QString::number(n_nbrEmp_adr)+"')");
        if(qry.exec())
        {
            qDebug()<<"Data added successfully to the database";
            conn.connClose();
        }
        else
        {
            qDebug()<<"An error has occured";
        }
    }

}


void adherents::Modifier()
{
    DBConnexion conn;
    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update adherents set nom_adr='"+n_nom_adr+"',nbrEmp_adr='"+QString::number(n_nbrEmp_adr)+"' where code_adhr='"+QString::number(n_code_adhr)+"'");
    if(qry.exec())
    {
        qDebug()<<"Data updated successfully";
        conn.connClose();
    }
    else
    {
        qDebug()<<"An error has occured";
        }
}


void adherents::Supprimer()
{
    DBConnexion conn;
    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("delete from adherents where code_adhr='"+QString::number(n_code_adhr)+"'");
    if(qry.exec())
    {
        qDebug()<<"Data deleted successfully from the database";
        conn.connClose();
    }
    else
    {
        qDebug()<<"An error has occured";
        }
}


QSqlQueryModel * adherents::Load()
{
    DBConnexion conn;
    conn.connOpen();
    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(conn.get_mydb());
    qry->prepare("select * from adherents");
    if (qry->exec())
    {
        modal->setQuery(*qry);
    }
    else
    {
        qDebug() <<"An error has occured" << qry->lastError().text();
    }

    conn.connClose();
    return modal;


}
