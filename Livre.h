#ifndef LIVRE_H
#define LIVRE_H
#include <QString>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include "DBConnexion.h"
#include<QTextStream>
#include<livre_dialog.h>


class Livre
{
private:

    int CodeLivre;
    int Nbr_pages;
    QString Titre;
    QString Auteur;
    QString Etat ;



public:

    Livre();
    ~Livre();
    int get_code();
    int get_nbr_pages();
    QString get_titre();
    QString get_auteur();
    QString get_etat();


    void  set_code(int);
    void set_nbr_pages(int);
    void  set_titre(QString);
    void set_auteur(QString);
    void set_etat(QString);


    void Ajouter();
    void Modifier();
    void Supprimer();
    QSqlQueryModel * Load();




};

#endif // LIVRE_H
