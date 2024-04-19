#ifndef STAT_DIALOG_H
#define STAT_DIALOG_H

#include <QDialog>
#include <QtWidgets>
#include "DBConnexion.h"
#include <QString>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QTextStream>
#include "HistogramWidget.h"
#include<QMessageBox>


namespace Ui {
class stat_dialog;
}

class stat_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit stat_dialog(QWidget *parent = 0);
    ~stat_dialog();
    DBConnexion conn;


private slots:
    void on_pushButton_stats_clicked();

private:
    Ui::stat_dialog *ui;
};

#endif // STAT_DIALOG_H
