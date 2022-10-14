#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QColorDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void paintEvent(QPaintEvent *e);
QColor color=Qt::white;
QColor color_2=Qt::white;
QColor color_3=Qt::white;
bool button = false;
int picked_x,picked_y,picked_z;
private slots:
void on_pushButton_clicked();

void on_pushButton_3_clicked();

void on_pushButton_4_clicked();

void on_pushButton_5_clicked();

void on_pushButton_6_clicked();

void on_pushButton_7_clicked();

void on_pushButton_8_clicked();

void on_pushButton_2_clicked();


void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
