#include "DBConnexion.h"
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>



DBConnexion::DBConnexion()
{
}

DBConnexion::~DBConnexion()
{
}



QSqlDatabase DBConnexion:: get_mydb()
{

    return mydb;

}

void DBConnexion:: connClose()
{

    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);

}
bool DBConnexion:: connOpen()
{

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("./MP_sujet8.db");

    if (!mydb.open()){
        qDebug()<<("FAILED TO OPEN DATABASE");
        return false ;
    }
    else {
        qDebug()<<("MP_DataBase CONNECTED!");
        return true;
    }
}
