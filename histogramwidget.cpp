#include "HistogramWidget.h"
#include <QPainter>
#include <algorithm>

HistogramWidget::HistogramWidget(QWidget *parent) : QWidget(parent),
    m_barWidth(20),
    m_barSpacing(5),
    m_marginLeft(60),
    m_marginTop(80),
    m_marginRight(10),
    m_marginBottom(100),
    m_axisFont("Arial", 11),
    m_titleFont("Arial", 5)
{
    setMinimumSize(1000,600);
}
void HistogramWidget::setData(const QVector<int> &labels, const QVector<float> &data) {
    m_labels = labels;
    m_data = data;
    update();
}

void HistogramWidget::setBarWidth(int width) {
    m_barWidth = width;
    update();
}

void HistogramWidget::setBarSpacing(int spacing) {
    m_barSpacing = spacing;
    update();
}

void HistogramWidget::setMargins(int left, int top, int right, int bottom) {
    m_marginLeft = left;
    m_marginTop = top;
    m_marginRight = right;
    m_marginBottom = bottom;
    update();
}

void HistogramWidget::setXAxisLabels(const QVector<QString> &labels) {
    m_xAxisLabels = labels;
    update();
}

void HistogramWidget::setYAxisLabel(const QString &label) {
    m_yAxisLabel = label;
    update();
}

void HistogramWidget::setTitle(const QString &title) {
    m_title = title;
    update();
}
void HistogramWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_data.isEmpty() || m_labels.isEmpty()) return;

    int totalWidth = width() - m_marginLeft - m_marginRight;
    int totalHeight = height() - m_marginTop - m_marginBottom;


    m_barWidth = totalWidth / (m_data.size() + 5);
    m_barSpacing = m_barWidth / 10;


    m_axisFont.setPointSize(totalHeight / 40);
    m_titleFont.setPointSize(totalHeight / 20);

    int maxDataValue = *std::max_element(m_data.constBegin(), m_data.constEnd());


    for (int i = 0; i < m_data.size(); ++i) {
        int barHeight = (static_cast<int>(totalHeight * (static_cast<float>(m_data[i]) / maxDataValue)))/2;

        QRect barRect(m_marginLeft + i * (m_barWidth + m_barSpacing),
                      height() - m_marginBottom - barHeight,
                      m_barWidth,
                      barHeight);

        painter.fillRect(barRect, Qt::blue);

        painter.setPen(Qt::black);
        painter.drawText(barRect, Qt::AlignTop | Qt::AlignHCenter, QString::number(m_data[i]));

    }


    painter.setPen(Qt::black);
    for (int i = 0; i < m_xAxisLabels.size(); ++i) {
        int x = m_marginLeft + i * (m_barWidth + m_barSpacing) + m_barWidth / 2;
        int y = height() - m_marginBottom + 15;
        painter.drawText(QRect(x-30, y-15, m_barWidth, 20), Qt::AlignCenter, m_xAxisLabels[i]);
    }





      painter.setPen(QColor(100, 100, 100));
      for (int i = 0; i < m_data.size(); ++i) {
          int x = m_marginLeft + i * (m_barWidth + m_barSpacing) + m_barWidth / 2;
          painter.drawLine(x, height() - m_marginBottom, x, m_marginTop/0.25);
      }

      int numDivisions = 10;
      int divisionHeight = (totalHeight) / numDivisions;
      for (int i =3; i <= numDivisions; ++i) {
          int y = m_marginTop + i * divisionHeight;
          painter.drawLine(m_marginLeft, y, (width() - m_marginRight)/1.4, y);
      }

      painter.setRenderHint(QPainter::Antialiasing);

        m_titleFont.setPointSize(20);

        painter.setFont(m_titleFont);


      int titleX = width() / 80 ;
      int titleY = 150;

      painter.drawText(QRect(titleX-150, titleY, width() / 1, 50), Qt::AlignCenter, m_title);
      QFont titleFont = painter.font();
          titleFont.setPointSize(10);
          painter.setFont(titleFont);


          QString yAxisTitle = "Number of Books";
           titleX = m_marginLeft / 2;
           titleY = m_marginTop ;
          painter.save();
          painter.translate(titleX+10, titleY+400);
          painter.rotate(-90);
          painter.drawText(0, 0, yAxisTitle);
          painter.restore();

}

