#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>
#include <QVector>
#include <QFont>

class HistogramWidget : public QWidget {
    Q_OBJECT
public:
    explicit HistogramWidget(QWidget *parent = 0);
    void setData(const QVector<int> &labels, const QVector<float> &data);

    void setBarWidth(int width);
    void setBarSpacing(int spacing);
    void setMargins(int left, int top, int right, int bottom);


    void setXAxisLabels(const QVector<QString> &labels);
    void setYAxisLabel(const QString &label);
    void setTitle(const QString &title);

protected:
   void paintEvent(QPaintEvent *event) override;

private:
    QVector<float> m_data;
    QVector<int> m_labels;
    QVector<QString> m_xAxisLabels;
    QString m_yAxisLabel;
    QString m_title;

    int m_barWidth;
    int m_barSpacing;
    int m_marginLeft;
    int m_marginTop;
    int m_marginRight;
    int m_marginBottom;

    QFont m_axisFont;
    QFont m_titleFont;
};

#endif // HISTOGRAMWIDGET_H
