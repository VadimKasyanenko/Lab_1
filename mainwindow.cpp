#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(color);
    painter.setBrush(color);
    painter.drawEllipse(QRect(10,200,180,180));
     painter.drawEllipse(QRect(310,200,180,180));
      painter.drawEllipse(QRect(610,200,180,180));
}

void MainWindow::on_pushButton_clicked()
{
    color = QColorDialog::getColor(Qt::yellow, this );
      if( color.isValid() )
      {
      update();
      }
}
