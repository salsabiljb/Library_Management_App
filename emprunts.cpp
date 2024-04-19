#include "emprunts.h"

emprunts::emprunts()
{
     id=0;
     CodeLivre=0;
     code_adhr=0;
     date_Emp ="";
     date_retour="";
}


emprunts::~emprunts()
{}
int emprunts::get_id(){
    return id;
}
int emprunts::get_CodeLiv()
{
    return CodeLivre ;
}

int emprunts:: get_codeadhr()
{
    return code_adhr;
}
QString emprunts:: get_dateEmp()
{
    return date_Emp;
}
QString emprunts:: get_dateRet()
{
    return date_retour;
}

void emprunts:: set_id(int ident)
{
    id= ident;
}
void emprunts:: set_CodeLiv(int cl)
{
    CodeLivre=cl;
}
void emprunts:: set_codeadhr(int cd)
{
    code_adhr=cd;
}
void emprunts:: set_dateEmp(QString demp)
{
    date_Emp= demp;
}
void emprunts:: set_dateRet(QString dret)
{
    date_retour=dret;
}

void emprunts:: Ajouter()
{

    DBConnexion conn;

    conn.connOpen();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

else{
    QSqlQuery qry;
    qry.prepare("insert into emprunts (Codelivre,code_adhr,date_Emp,date_retour) values ('"+QString ::number(CodeLivre)+"','"+QString ::number(code_adhr)+"','"+date_Emp+"','"+date_retour+"')");

    if (qry.exec( ))
    {
        qDebug()<<"Saved";
        conn.connClose();

    }
    else
    {
           qDebug()<<qry.lastError().text();
    }
    }


}
void emprunts:: Modifier()
{
    DBConnexion conn;

    conn.connOpen();

    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

else{
    QSqlQuery qry;
    qry.prepare("update emprunts set id='"+QString ::number(id)+"',CodeLivre='"+QString ::number(CodeLivre)+"',code_adhr='"+QString ::number(code_adhr)+"',date_Emp='"+date_Emp+"',date_retour='"+date_retour+"' where id='"+QString ::number(id)+"'");

    if (qry.exec( ))
    {
        qDebug()<<"Updated!";
        conn.connClose();

    }
    else
    {
         qDebug()<<qry.lastError().text();
    }
    }
}
void emprunts:: Supprimer()
{
    DBConnexion conn;

    conn.connOpen();
    if(!conn.connOpen())
    {
        qDebug()<<"Failed to open the database";
        return;
    }

    else {
    QSqlQuery qry;
    qry.prepare("Delete from emprunts where id='"+QString ::number(id)+"'");

    if (qry.exec( ))
    {
         qDebug()<<"Deleted!";
        conn.connClose();

    }
    else
    {
         qDebug()<<qry.lastError().text();
    }
        }
}
QSqlQueryModel * emprunts:: Load()
{
    DBConnexion conn;
    conn.connOpen();
    QSqlQueryModel *modal_e = new QSqlQueryModel();

    QSqlQuery* qry = new QSqlQuery(conn.get_mydb());
    qry->prepare("SELECT * FROM emprunts");

    if(qry->exec())
    {
        modal_e->setQuery(*qry);
    }
    else
    {

        qDebug() << "Erreur lors de l'exécution de la requête SQL:" << qry->lastError().text();
    }

    conn.connClose();
    return modal_e;


}
