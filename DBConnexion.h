#ifndef DBCONNEXION_H
#define DBCONNEXION_H


#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>

class DBConnexion
{

    QSqlDatabase mydb;

public:
    DBConnexion();
    ~DBConnexion();
    void connClose();
    bool connOpen();

    QSqlDatabase get_mydb();
};

#endif // DBCONNEXION_H
