#include "Livre.h"




Livre::Livre()
{

    CodeLivre=0;
    Nbr_pages=0;
    Titre="";
    Auteur="";
    Etat="";


}


Livre::~Livre()
{}

int Livre:: get_code()
{
    return CodeLivre;
}

int Livre:: get_nbr_pages()
{
    return Nbr_pages;
}
QString Livre:: get_titre()
{
    return Titre ;
}
QString Livre:: get_auteur()
{
    return Auteur ;
}
QString Livre:: get_etat()
{
    return Etat;
}


void Livre:: set_code(int c)
{
    CodeLivre=c;
}
void Livre:: set_nbr_pages(int n)
{
    Nbr_pages=n;
}
void Livre:: set_titre(QString titre)
{
    Titre =titre;
}
void Livre:: set_auteur(QString auteur)
{
    Auteur=auteur;
}
void Livre:: set_etat(QString etat)
{
    Etat=etat;
}


void Livre:: Ajouter()
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
    qry.prepare("insert into Livre (Titre,Nbr_pages,Auteur,Etat) values ('"+Titre+"','"+QString ::number(Nbr_pages)+"','"+Auteur+"','"+Etat+"')");

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
void Livre:: Modifier()
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
    qry.prepare("update Livre set Titre='"+Titre+"',Nbr_pages='"+QString ::number(Nbr_pages)+"',Auteur='"+Auteur+"',Etat='"+Etat+"' where CodeLivre='"+QString ::number(CodeLivre)+"'");

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
void  Livre:: Supprimer()
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
    qry.prepare("Delete from Livre where CodeLivre='"+QString ::number(CodeLivre)+"'");

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
QSqlQueryModel* Livre:: Load()
{

        DBConnexion conn;
        conn.connOpen();
        QSqlQueryModel *modal_l = new QSqlQueryModel();

        QSqlQuery* qry = new QSqlQuery(conn.get_mydb());
        qry->prepare("SELECT * FROM Livre");

        if(qry->exec())
        {
            modal_l->setQuery(*qry);
        }
        else
        {

            qDebug() << "Erreur lors de l'exécution de la requête SQL:" << qry->lastError().text();
        }

        conn.connClose();

        return modal_l;


}


