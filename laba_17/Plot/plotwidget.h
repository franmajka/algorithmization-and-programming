#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include <QWidget>

class PlotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlotWidget(QWidget *parent = nullptr);

    double xMax = 0;
    double xMin = 0;
    double yMax = 0;
    double yMin = 0;

    QVector<QPointF> pVec;
    QVector<QLine> plotLines;

    bool isCentered = true;

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void setData(double axMin, double axMax);

signals:

};

#endif // PLOTWIDGET_H
