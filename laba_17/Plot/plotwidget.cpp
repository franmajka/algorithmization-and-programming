#include "plotwidget.h"

#include <QPainter>
#include <QMessageBox>
#include <qmath.h>

#define SECTION_STEP 50
#define QUALITY 10000

#define MAX(a, b) ((a) > (b) ? (a) : (b))

PlotWidget::PlotWidget(QWidget *parent) : QWidget(parent)
{

}

void PlotWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));

    // An ratios that'll help us to make chart expanded to the box sizes
    double ratio = static_cast<double>(height()) / (yMax - yMin);

    int posXCenter, posYCenter;
    int shiftX = 0, shiftY = 0;
    if (xMin * xMax >= 0) { // Same sign
        if (xMax <= 0) {
            // So we're setting an Y axis to the right out of sceen
            posXCenter = width() - 1;

            // To show chart properly we have to think that the right
            // border of the box is equal -xMax on the coordinates
            // So shiftX is literally distance from real Y axis to the right border

            // Example if xMin = -3 and xMax = -1
            // When we're gonna draw the chart we're gonna shift every x by 1
            shiftX = -xMax;
        } else {
            // Exactly the same but in other direction
            posXCenter = 0;
            shiftX = -xMin;
        }
    } else {
        posXCenter = -xMin * static_cast<double>(width()) / (xMax - xMin);
    }

    if (yMin * yMax >= 0) { // Same sign
        if (yMin >= 0) {
            posYCenter = height() - 1;
            shiftY = -yMin;
        } else {
            posYCenter = 0;
            shiftY = -yMax;
        }
    } else {
        posYCenter = yMax * ratio;
    }

    QPoint center = {posXCenter, posYCenter};

    QVector<QLine> axes = {
        {center.x(), 0, center.x(), height()},
        {0, center.y(), width(), center.y()},
    };

    painter.drawLines(axes);

//    QVector<QLine> sections;

//    for (int i = height() - SECTION_STEP; i >= 0; i -= SECTION_STEP) {
//        sections.push_back({posXCenter - 5, i, posXCenter + 5, i});
//    }

//    for (int i = SECTION_STEP; i < width(); i += SECTION_STEP) {
//        sections.push_back({i, posYCenter + 5, i, posYCenter - 5});
//    }

//    painter.drawLines(sections);

    if (pVec.empty()) return;

    painter.setPen(QPen(Qt::black, 3));
    QVector<QLine> chart;

    QPointF pPrev = pVec.first();

    for (auto it = pVec.begin() + 1; it != pVec.end(); ++it) {
        chart.push_back({
            center.x() + static_cast<int>((pPrev.x() + shiftX) * ratio),
            center.y() - static_cast<int>((pPrev.y() + shiftY) * ratio),
            center.x() + static_cast<int>((it->x() + shiftX) * ratio),
            center.y() - static_cast<int>((it->y() + shiftY) * ratio),
        });
        pPrev = *it;
    }

    painter.drawLines(chart);
}

double func(double x) {
//    return log(sqrt(x));
    return x * x * x;
}

void PlotWidget::setData(double axMin, double axMax)
{
    if (axMax <= axMin) {
        QMessageBox::critical(
                    this,
                    "Проблема с графиком",
                    "Максимальное значение х меньше чем минимальное"
        );
        return;
    }

//    if (axMax <= 0) {
//        QMessageBox::critical(
//                    this,
//                    "Проблема с графиком",
//                    "Указанный промежуток не входит в область опрееделения"
//        );
//        return;
//    }

//    xMin = MAX(0, axMin);
    xMin = axMin;
    xMax = axMax;
//    yMin = axMin;
//    yMax = axMax;

    pVec.clear();
    pVec.push_back({xMin, func(xMin)});

    yMin = pVec.first().y();
    yMax = yMin;

    double plotStep = static_cast<double>(xMax - xMin) / QUALITY;

    for (double x = pVec.first().x() + plotStep; x < xMax; x += plotStep) {

        double y = func(x);
        if (y > yMax) yMax = y;
        if (y < yMin) yMin = y;

        pVec.push_back({x, y});
    }

    repaint();
}
