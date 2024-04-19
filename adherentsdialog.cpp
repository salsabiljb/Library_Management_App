#include "adherentsdialog.h"
#include "ui_adherentsdialog.h"

#include<QMessageBox>
#include <QSqlQueryModel>

#include<QDebug>
#include"admin_dialog.h"
#include"DBConnexion.h"
#include"adherents.h"

adherentsdialog::adherentsdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adherentsdialog)
{
    ui->setupUi(this);
    if (!conn.connOpen())
        ui->label_status2->setText("Failed to connect to the database");
    else
        ui->label_status2->setText("Connected to database");
}

adherentsdialog::~adherentsdialog()
{
    delete ui;
}



void adherentsdialog::on_pushButton_save_clicked()
{
    adherents A;
    A.set_code_adhr(ui->lineEdit_code_adhr->text().toInt());
    A.set_nom_adr(ui->lineEdit_nom_adr->text());
    A.set_nbrEmp_adr(ui->lineEdit_nbrEmp_adr->text().toInt());
    A.Ajouter();
}

void adherentsdialog::on_pushButton_delete_clicked()
{
    adherents A;
    A.set_code_adhr(ui->lineEdit_code_adhr->text().toInt());
    A.set_nom_adr(ui->lineEdit_nom_adr->text());
    A.set_nbrEmp_adr(ui->lineEdit_nbrEmp_adr->text().toInt());
    A.Supprimer();
}

void adherentsdialog::on_pushButton_update_clicked()
{
    adherents A;
    A.set_code_adhr(ui->lineEdit_code_adhr->text().toInt());
    A.set_nom_adr(ui->lineEdit_nom_adr->text());
    A.set_nbrEmp_adr(ui->lineEdit_nbrEmp_adr->text().toInt());
    A.Modifier();
}

void adherentsdialog::on_pushButton_load_clicked()
{
    QSqlQueryModel * modal= new QSqlQueryModel();
    adherents A;
    modal = A.Load();
    ui->tableView->setModel(modal);
    qDebug() <<modal->rowCount();
}



void adherentsdialog::on_pushButton_init_clicked()
{
    ui->lineEdit_code_adhr->setText("");
    ui->lineEdit_nbrEmp_adr->setText("");
    ui->lineEdit_nom_adr->setText("");
    ui->pushButton_save->setEnabled(true);
}




void adherentsdialog::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    DBConnexion conn;
    if(!conn.connOpen())
    {
        qDebug() <<"Failed to connect to the database";
        return ;
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("select * from adherents where code_adhr=' "+val+" ' or nom_adr = ' "+val+ " ' or nbrEmp_adr= ' " +val+" ' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_code_adhr->setText(qry.value(0).toString());
            ui->lineEdit_nom_adr->setText(qry.value(1).toString());
            ui->lineEdit_nbrEmp_adr->setText(qry.value(2).toString());
        }
        conn.connClose();
    }
    else
    {
        qDebug() <<"Failed to connect to the database";
    }

    ui->pushButton_delete->setEnabled(true);
    ui->pushButton_init->setEnabled(true);
    ui->pushButton_update->setEnabled(true);
}

void adherentsdialog::on_pushButton_stats_adh_clicked()
{
    DBConnexion conn;

    if (conn.connOpen()) {
        QSqlQueryModel appelModel;
        appelModel.setQuery("SELECT nom_adr, COUNT(*) AS nbrEmp_adr FROM adherents GROUP BY nom_adr ORDER BY nbrEmp_adr DESC");

        if (appelModel.lastError().isValid()) {
            qDebug() << "Error executing SQL query:" << appelModel.lastError().text();
            conn.connClose();
            return;
        }

        // Prepare data for the histogram
        QVector<QString> xData;
        QVector<double> yData;

        for (int row = 0; row < appelModel.rowCount(); ++row) {
            QString nom_adr = appelModel.record(row).value("nom_adr").toString();
            int nbrEmp_adr = appelModel.record(row).value("nbrEmp_adr").toInt();

            // Add the data in descending order
            xData.append(nom_adr);
            yData.append(nbrEmp_adr);
        }

        if (xData.isEmpty() || yData.isEmpty()) {
            qDebug() << "No valid data for plotting.";
            conn.connClose();
            return; // Exit if there is no data to plot
        }

        // Clear any previous plots
        ui->customPlot->clearPlottables();

        // Create a histogram
        QCPBars *bars = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
        ui->customPlot->addPlottable(bars);

        // Set pen (border color) and brush (fill color) for the bars
        QPen pen;
        pen.setColor(QColor(0, 0, 0)); // Set color for the border
        bars->setPen(pen);

        // Set brush (fill color) for the bars
        bars->setBrush(QColor(248, 129, 88)); // Set color for the fill

        // Convert string x-data to numerical indices
        QVector<double> xNumericalData;
        for (int i = 0; i < xData.size(); ++i)
            xNumericalData.append(i);

        // Set data to the bars
        bars->setData(xNumericalData, yData);
        bars->setWidth(0.5); // Adjust the width of the bars

        // Set labels and title
        ui->customPlot->xAxis->setLabel("Les Adherents");
        ui->customPlot->yAxis->setLabel("Nombre d'emprunts");

        // Set up the axes
        ui->customPlot->xAxis->setRange(0, xData.size()); // Adjusted x-axis range
        ui->customPlot->yAxis->setRange(0, *std::max_element(yData.constBegin(), yData.constEnd()) + 1);

        // Show all data points on the x-axis
        ui->customPlot->xAxis->setAutoTicks(false);
        ui->customPlot->xAxis->setAutoTickLabels(false);
        ui->customPlot->xAxis->setAutoSubTicks(false);

        QVector<double> customTicks;
        QVector<QString> customTickLabels;

        for (int i = 0; i < xData.size(); ++i) {
            customTicks << i; // Use index as tick position
            customTickLabels << xData[i];
        }

        ui->customPlot->xAxis->setTickVector(customTicks);
        ui->customPlot->xAxis->setTickVectorLabels(customTickLabels);
        ui->customPlot->xAxis->setTickLabelRotation(0);

        // Set the y-axis ticks to integers
        ui->customPlot->yAxis->setTickVector(QVector<double>() << 0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10); // Example range, adjust as needed

        // Replot the graph
        ui->customPlot->replot();

        conn.connClose();
    } else {
        qDebug() << "Failed to open the database connection.";
    }
}
