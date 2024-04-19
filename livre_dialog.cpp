#include "livre_dialog.h"
#include "ui_livre_dialog.h"

#include <QMessageBox>
#include <QDebug>

livre_dialog::livre_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::livre_dialog)
{
    ui->setupUi(this);
    if (!conn.connOpen())
        ui->label_status_livre_bd->setText("FAILED TO OPEN DATABASE");
    else {
        ui->label_status_livre_bd->setText("MP_DataBase CONNECTED!");
    }
}

livre_dialog::~livre_dialog()
{
    delete ui;
}



void livre_dialog::on_pushButton_save_clicked()
{

     Livre lv;
     lv.set_titre(ui->lineEdit_titre->text());
     lv.set_nbr_pages(ui->lineEdit_nbrp->text().toInt());
     lv.set_auteur(ui->lineEdit_auteur->text());
     lv.set_etat(ui->lineEdit_etat->text());
     lv.Ajouter();
}

void livre_dialog::on_pushButton_edit_clicked()
{

    Livre lv;
    lv.set_titre(ui->lineEdit_titre->text());
    lv.set_code(ui->lineEdit_code->text().toInt());
    lv.set_nbr_pages(ui->lineEdit_nbrp->text().toInt());
    lv.set_auteur(ui->lineEdit_auteur->text());
    lv.set_etat(ui->lineEdit_etat->text());
    lv.Modifier();


}

void livre_dialog::on_pushButton_delete_clicked()
{

    Livre lv;
    lv.set_code(ui->lineEdit_code->text().toInt());
    lv.Supprimer();

}

void livre_dialog::on_pushButton_load_clicked()
{
    QSqlQueryModel * modal_l=new QSqlQueryModel();
    Livre lv;
    modal_l=lv.Load();
    ui->tableView->setModel(modal_l);
    qDebug()<<modal_l->rowCount();
}


void livre_dialog::on_pushButton_init_clicked()
{
    ui->lineEdit_auteur->setText("");
    ui->lineEdit_titre->setText("");
    ui->lineEdit_etat->setText("");
    ui->lineEdit_nbrp->setText("");
    ui->lineEdit_code->setText("");

    ui->pushButton_save->setEnabled(true);

}

void livre_dialog::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();

    DBConnexion conn ;
    if(!conn.connOpen())
    {
        qDebug()<<"FAILED TO OPEN DATABASE";
        return;

    }

    conn.connOpen();
    QSqlQuery qry ;
    qry.prepare("select * from Livre where CodeLivre='"+val+"' or Titre='"+val+"' or Nbr_pages='"+val+"' or Auteur='"+val+"' or Etat='"+val+"'");

    if(qry.exec( ))
    {
        while(qry.next())
        {
            ui->lineEdit_code->setText(qry.value(0).toString());
            ui->lineEdit_titre->setText(qry.value(1).toString());
            ui->lineEdit_nbrp->setText(qry.value(2).toString());
            ui->lineEdit_auteur->setText(qry.value(3).toString());
            ui->lineEdit_etat->setText(qry.value(4).toString());
        }
        conn.connClose();
    }

    else
    {

        QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }

    ui->pushButton_delete->setEnabled(true);
    ui->pushButton_edit->setEnabled(true);
    ui->pushButton_init->setEnabled(true);


}


void livre_dialog::on_pushButton_stats_livre_clicked()
{
    DBConnexion conn;

    if (conn.connOpen()) {
        QSqlQueryModel appelModel;
        appelModel.setQuery("SELECT Auteur, COUNT(*) AS nbr_livre FROM Livre GROUP BY Auteur ORDER BY nbr_livre DESC");

        if (appelModel.lastError().isValid()) {
            qDebug() << "Error executing SQL query:" << appelModel.lastError().text();
            conn.connClose();
            return;
        }

        // Prepare data for the histogram
        QVector<QString> xData;
        QVector<double> yData;

        for (int row = 0; row < appelModel.rowCount(); ++row) {
            QString auteur = appelModel.record(row).value("Auteur").toString();
            int nbr_livre = appelModel.record(row).value("nbr_livre").toInt();

            // Add the data in descending order
            xData.append(auteur);
            yData.append(nbr_livre);
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
        ui->customPlot->xAxis->setLabel("Les Auteurs");
        ui->customPlot->yAxis->setLabel("Nombre de livres");

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

        // Replot the graph
        ui->customPlot->replot();

        conn.connClose();
    } else {
        qDebug() << "Failed to open the database connection.";
    }
}

