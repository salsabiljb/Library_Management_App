#include "stat_dialog.h"
#include "ui_stat_dialog.h"

stat_dialog::stat_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_dialog)
{
    ui->setupUi(this);
    if (!conn.connOpen())
       { ui->label_stat_status->setText("Failed to connect to the database");}
    else
    {ui->label_stat_status->setText("Connected to database");}
}

stat_dialog::~stat_dialog()
{
    delete ui;
}

void stat_dialog::on_pushButton_stats_clicked()
{


    QVector<int> data_x;
    QVector<float> data_y;
    QVector<QString> x_labels;
    QString y_label = "Number of Books";
    QString title = "Number of Books per Author ";

    if (!conn.connOpen()) {
        qDebug() << "Failed to open database";
    } else {
        conn.connOpen();
        QSqlQuery qry;
        if (qry.exec("SELECT Auteur, COUNT(*) AS nbr_livre FROM Livre GROUP BY Auteur ORDER BY nbr_livre DESC")) {
            while (qry.next()) {
                data_x.append(qry.value(0).toInt()); // Nom auteur
                data_y.append(qry.value(1).toInt()); // nbr de livre total
                x_labels.append(qry.value(0).toString()); // Label du nom auteur
            }
            conn.connClose();
        }


        HistogramWidget *histogram = new HistogramWidget(this);
        histogram->setBarWidth(10);
        histogram->setBarSpacing(500);
        histogram->setMargins(30, 50, 10, 30);
        histogram->setXAxisLabels(x_labels);
        histogram->setYAxisLabel(y_label);
        histogram->setTitle(title);
        histogram->setData(data_x, data_y);
        histogram->show();
    }


}
