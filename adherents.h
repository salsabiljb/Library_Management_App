#ifndef ADHERENTS_H
#define ADHERENTS_H
#include <QString>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QFile>
#include<QTextStream>

#include"dbconnexion.h"
#include"ui_adherentsdialog.h"
#include"adherentsdialog.h"


class adherents
{
private:
    int n_code_adhr , n_nbrEmp_adr;
    QString n_nom_adr;
public:
    adherents();
    ~adherents();
    int get_code_adhr();
    QString get_nom_adr();
    int get_nbrEmp_adr();

    void set_code_adhr(int i);
    void set_nom_adr(QString n);
    void set_nbrEmp_adr(int j);

   void Ajouter();
   void Supprimer();
   void Modifier();
   QSqlQueryModel * Load();

};

#endif // ADHERENTS_H
