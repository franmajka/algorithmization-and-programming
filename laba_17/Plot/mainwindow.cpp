#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->xMinBox->setMinimum(-1e4);
    ui->xMaxBox->setMinimum(-1e4);
    ui->xMinBox->setMaximum(1e4);
    ui->xMaxBox->setMaximum(1e4);

    ui->plotWidget->setData(-3, 3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    painter.setPen(QPen(Qt::black, 14));
//    QVector<QLine> vec = {{0, 0, 0, 0}};
//    for (int i = 0; i < 10; i++) {
//        vec.push_back({vec.last().x2(), vec.last().y2(), rand() % 600, rand() % 600});
//    }
//    painter.drawLines(vec);
}



void MainWindow::on_drawBtn_clicked()
{
    ui->plotWidget->setData(ui->xMinBox->value(), ui->xMaxBox->value());
}

