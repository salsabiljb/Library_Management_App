#ifndef EMPRUNTS_H
#define EMPRUNTS_H
#include <QString>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include "DBConnexion.h"
#include<QTextStream>
#include<emprunts_dialog.h>

class emprunts
{
private:
    int id;
    int CodeLivre;
    int code_adhr;
    QString date_Emp, date_retour ;

public:
    emprunts();
    ~emprunts();
    int get_id();
    int get_CodeLiv();
    int get_codeadhr();
    QString get_dateEmp();
    QString get_dateRet();

    void set_id(int);
    void set_CodeLiv(int);
    void set_codeadhr(int);
    void set_dateEmp(QString);
    void set_dateRet(QString);


    void Ajouter();
    void Modifier();
    void Supprimer();
    QSqlQueryModel * Load();
};

#endif // EMPRUNTS_H
