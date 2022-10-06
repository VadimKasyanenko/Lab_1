#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <math.h>
#include <string>
#include <QMessageBox>
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
    painter.drawEllipse(QRect(10,260,180,180));
    painter.setPen(color_2);
    painter.setBrush(color_2);
    painter.drawEllipse(QRect(310,260,180,180));
    painter.setPen(color_3);
    painter.setBrush(color_3);
    painter.drawEllipse(QRect(610,260,180,180));
}

void MainWindow::on_pushButton_clicked()
{
    QColor col = QColorDialog::getColor(color, this );
      if( col.isValid() )
      {
          col.getRgb(&picked_x,&picked_y,&picked_z);
          button = true;
          on_pushButton_3_clicked();
      }
}


//Other conversions
//-------------------------------------------//
double Lab_XYZ_function(double x)
{
    if(x>=0.008856)
    {
        return pow(x,1/3.0);
    }
    else
    {
        return 7.787*x+16/116.0;
    }
}
void Lab_XYZ(double x,double y, double z)
{
    double l,a,b;
    l=116*Lab_XYZ_function(y/100.0)-16;
    a=500*(Lab_XYZ_function(x/95.047)-Lab_XYZ_function(y/100.0));
    b=200*(Lab_XYZ_function(y/100.0)-Lab_XYZ_function(z/108.883));
}
double XYZ_Lab_function(double x)
{
    if(pow(x,3)>=0.008856)
    {
        return pow(x,3);
    }
    else
    {
        return (x-16/116.0)/7.787;
    }
}
void XYZ_Lab(float l,float a, float b)
{
    l=XYZ_Lab_function((l+16)/116.0)*95.047;
    a=XYZ_Lab_function(a/500.0+(l+16)/116.0)*100;
    b=XYZ_Lab_function((l+16)/116.0-b/200.0)*108.883;

}
//-------------------------------------------//



//RGB to other colors
//-------------------------------------------//
QColor CMYK_RGB(int r,int g, int b)
{
  QColor col;
  float c,m,y,k;
  k=std::min(std::min(1.0-r/255.0,1.0-g/255.0),1.0-b/255.0);
  c=(1.0-r/255.0-k)/(1.0-k);
  if(c<0){c=0;}
  m=(1.0-g/255.0-k)/(1.0-k);
   if(m<0){m=0;}
  y=(1.0-b/255.0-k)/(1.0-k);
   if(y<0){y=0;}
  col.setCmykF(c,m,y,k);
  return col;
}

QColor HSV_RGB(float r,float g, float b)
{
  QColor col;
  float h,s,v,CMax,CMin;
  r/=255.0;
  g/=255.0;
  b/=255.0;
  CMax=std::max(std::max(r,g),b);
  CMin=std::min(std::min(r,g),b);
  v=CMax;
  if(v==0)
  {
      s=0;
  }
  else
  {
      s = (CMax-CMin)/CMax;
  }
  if(CMax==CMin)
  {
      h=0;
  }
  else if(CMax==r && g>=b)
  {
      h = 60.0*((g-b)/(CMax-CMin));
  }
  else if(CMax==r && g<b)
  {
      h = 60.0*((g-b)/(CMax-CMin)) +360;
  }
  else if(CMax==g)
  {
      h = 60.0*((b-r)/(CMax-CMin))+120;
  }
  else if(CMax==b)
  {
      h = 60.0*((r-g)/(CMax-CMin))+240;
  }
  col.setHsvF(h/360.0,s,v);
  return col;

}

QColor HSL_RGB(float r,float g, float b)
{
    QColor col;
    float h,s,l,CMax,CMin;
    r/=255.0;
    g/=255.0;
    b/=255.0;
    CMax=std::max(std::max(r,g),b);
    CMin=std::min(std::min(r,g),b);
    l=(CMax+CMin)/2.0;
    if(l==0 || CMax==CMin)
    {
        s=0;
    }
    else if(l>0 && l<=0.5)
    {
        s = (CMax-CMin)/(2*l);
    }
    else if(l>0.5)
    {
        s = (CMax-CMin)/(2-2*l);
    }
    if(CMax==CMin)
    {
        h=0;
    }
    else if(CMax==r && g>=b)
    {
        h = 60.0*((g-b)/(CMax-CMin));
    }
    else if(CMax==r && g<b)
    {
        h = 60.0*((g-b)/(CMax-CMin)) +360;
    }
    else if(CMax==g)
    {
        h = 60.0*((b-r)/(CMax-CMin))+120;
    }
    else if(CMax==b)
    {
        h = 60.0*((r-g)/(CMax-CMin))+240;
    }
  col.setHslF(h/360.0,s,l);
  return col;
}
//-------------------------------------------//



//CMYK to other colors
//-------------------------------------------//
QColor RGB_CMYK(int c,int m, int y, int k)
{
  QColor col;
  int r,g,b;
  r=255*(1-c/255.0)*(1-k/255.0);
  g=255*(1-m/255.0)*(1-k/255.0);
  b=255*(1-y/255.0)*(1-k/255.0);
  col.setRgb(r,g,b);
  return  col;
}
//-------------------------------------------//



//HSV to other colors
//-------------------------------------------//
QColor HSL_HSV(float h,float s, float v)
{
    QColor col;
    float l;
    l=v*(1-s/2);
    if (l==0 || l==1)
    {
        s=0;
    }
    else
    {
        s=(v-l)/std::min(l,1-l);
    }
    col.setHslF(h,s,l);
    return  col;
}
QColor RGB_HSV(float h,float s,float v)
{
    QColor col;
    float r,g,b;
    h *=6;
    float c = v*s;
    float mod = h/2;
    mod = mod - (int)mod;
    float x= c*(1-(abs(mod -1)));
    float m = v - c;
    if (h>=0 || h<1)
    {
        r=c;
        g=x;
        b=0;
    }
    if (h>=1 || h<2)
    {
        r=x;
        g=c;
        b=0;
    }
    if (h>=2 || h<3)
    {
        r=0;
        g=c;
        b=x;
    }
    if (h>=3 || h<4)
    {
        r=0;
        g=x;
        b=c;
    }
    if (h>=4 || h<5)
    {
        r=x;
        g=0;
        b=c;
    }
    if (h>=5 || h<6)
    {
        r=c;
        g=0;
        b=x;
    }
    col.setRgbF(r+m,g+m,b+m);
    return col;
}
//-------------------------------------------//



//HSL to other colors
//-------------------------------------------//
QColor RGB_HSL(float h,float s,float l)
{
    QColor col;
    float r,g,b;
    h *=6;
    float c = ((1-abs(2*l-1))*s);
    float mod = h/2;
    mod = mod - (int)mod;
    float x= c*(1-(abs(mod -1)));
    float m = l - c/2;
    if (h>=0 || h<1)
    {
        r=c;
        g=x;
        b=0;
    }
    if (h>=1 || h<2)
    {
        r=x;
        g=c;
        b=0;
    }
    if (h>=2 || h<3)
    {
        r=0;
        g=c;
        b=x;
    }
    if (h>=3 || h<4)
    {
        r=0;
        g=x;
        b=c;
    }
    if (h>=4 || h<5)
    {
        r=x;
        g=0;
        b=c;
    }
    if (h>=5 || h<6)
    {
        r=c;
        g=0;
        b=x;
    }
    col.setRgbF(r+m,g+m,b+m);
    return col;
}
QColor HSV_HSL(float h,float s, float l)
{
    QColor col;
    float v;
    v=l+s*std::min(l,1-l);
    if(v==0)
    {
        s=0;
    }
    else
    {
        s=2*(1-l/v);
    }
    col.setHsvF(h,s,v);
    return  col;
}
//-------------------------------------------//



//XYZ to other colors
//-------------------------------------------//
float convert(float num){
    if(num >=0.0031308)
    {
        return 1.055*pow(num,1/2.4) - 0.055;
    }
    else{
        return 12.96*num;
    }
}
QColor RGB_XYZ(float x,float y, float z)
{
    QColor col;
    float r,g,b;
    r =  3.2406*x - 1.5372*y - 0.4986*z;
    g = -0.9689*x + 1.8758*y + 0.0415*z;
    b =  0.0557*x - 0.2040*y + 1.0570*z;
    col.setRgbF(convert(r),convert(g),convert(b));
    return col;
}
//-------------------------------------------//


//LAB to other colors
//-------------------------------------------//
QColor RGB_LAB(float l,float a,float b){
    QColor col;
   // XYZ_Lab(&l,&a,&b);
    float x,y,z;
    y=XYZ_Lab_function((l+16)/116.0)*95.047;
    x=XYZ_Lab_function(a/500.0+(l+16)/116.0)*100;
    z=XYZ_Lab_function((l+16)/116.0-b/200.0)*108.883;
    col= RGB_XYZ(x/100.0,y/100.0,z/100.0);
    return col;
}
//-------------------------------------------//



void MainWindow::on_pushButton_3_clicked()//from rgb
{
    int x,y,z;
    QString str;
    if (!button) {
    str = ui->lineEdit->text();
    x = str.toInt();
    str = ui->lineEdit_2->text();
    y = str.toInt();
    str = ui->lineEdit_3->text();
    z = str.toInt();
    }
    else {
        x=picked_x;
        y=picked_y;
        z=picked_z;
        button = false;
    }
    if (x > 255 || y > 255 || z > 255 || x<0 || y<0 || z<0)
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Out of range");
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Out of range");
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Out of range");
    }
    else{
    str = (ui->comboBox->currentText());
    if (str=="RGB")
    {
        color.setRgb(x,y,z);
        ui->label_26->setText("");
    }
    if (str=="CMYK")
    {
        color = CMYK_RGB(x,y,z);
        ui->label_26->setText("");
    }
    if (str=="HSV")
    {
    color = HSV_RGB(x,y,z);
    ui->label_26->setText("");
    }
    if (str=="HSL")
    {
    color = HSL_RGB(x,y,z);
    ui->label_26->setText("");
    }
    QString str_2 = (ui->comboBox_2->currentText());
    if (str_2=="RGB")
    {
        color_2.setRgb(x,y,z);
        ui->label_27->setText("");
    }
    if (str_2=="CMYK")
    {
        color_2 = CMYK_RGB(x,y,z);
        ui->label_27->setText("");
    }
    if (str_2=="HSV")
    {
    color_2 = HSV_RGB(x,y,z);
    ui->label_27->setText("");
    }
    if (str_2=="HSL")
    {
        color_2 = HSL_RGB(x,y,z);
        ui->label_27->setText("");
    }
    QString str_3 = (ui->comboBox_3->currentText());
    if (str_3=="RGB")
    {
        color_3.setRgb(x,y,z);
        ui->label_28->setText("");
    }
    if (str_3=="CMYK")
    {
        color_3 = CMYK_RGB(x,y,z);
        ui->label_28->setText("");
    }
    if (str_3=="HSV")
    {
    color_3 = HSV_RGB(x,y,z);
    ui->label_28->setText("");
    }
    if (str_3=="HSL")
    {
        color_3 = HSL_RGB(x,y,z);
        ui->label_28->setText("");
    }
    }
     update();
}

void MainWindow::on_pushButton_4_clicked()//from hsv
{
    float h,s,v;
    QString str = ui->lineEdit_9->text();
    h = str.toFloat();
    str = ui->lineEdit_4->text();
    s = str.toFloat();
    str = ui->lineEdit_10->text();
    v = str.toFloat();
    if (h > 1 || s > 1 || v > 1 || h<0 || s<0 || v<0)
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Out of range");
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Out of range");
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Out of range");
    }
    else {
    str = (ui->comboBox->currentText());
    if (str=="RGB")
    {
        color = RGB_HSV(h,s,v);
        ui->label_26->setText("");
    }
    if (str=="CMYK")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");

    }
    if (str=="HSV")
    {
    color.setHsvF(h,s,v);
    ui->label_26->setText("");
    }
    if (str=="HSL")
    {
    color = HSL_HSV(h,s,v);
    ui->label_26->setText("");
    }
    QString str_2 = (ui->comboBox_2->currentText());
    if (str_2=="RGB")
    {
        color_2 = RGB_HSV(h,s,v);
        ui->label_27->setText("");
    }
    if (str_2=="CMYK")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    if (str_2=="HSV")
    {
    color_2.setHsvF(h,s,v);
    ui->label_27->setText("");
    }
    if (str_2=="HSL")
    {
        color_2 = HSL_HSV(h,s,v);
        ui->label_27->setText("");
    }
    QString str_3 = (ui->comboBox_3->currentText());
    if (str_3=="RGB")
    {
        color_3 = RGB_HSV(h,s,v);
        ui->label_28->setText("");
    }
    if (str_3=="CMYK")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    if (str_3=="HSV")
    {
    color_3.setHsvF(h,s,v);
    ui->label_28->setText("");
    }
    if (str_3=="HSL")
    {
        color_3 = HSL_HSV(h,s,v);
        ui->label_28->setText("");
    }
    }
     update();
}

void MainWindow::on_pushButton_5_clicked()//from hsl
{
    float h,s,l;
    QString str = ui->lineEdit_11->text();
    h = str.toFloat();
    str = ui->lineEdit_12->text();
    s = str.toFloat();
    str = ui->lineEdit_13->text();
    l = str.toFloat();
    if (h > 1 || s > 1 || l > 1 || h<0 || s<0 || l<0)
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Out of range");
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Out of range");
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Out of range");
    }
    else{
    str = (ui->comboBox->currentText());
    if (str=="RGB")
    {
        color = RGB_HSL(h,s,l);
        ui->label_26->setText("");
    }
    if (str=="CMYK")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    if (str=="HSV")
    {
        color = HSV_HSL(h,s,l);
        ui->label_26->setText("");
    }
    if (str=="HSL")
    {
        color.setHslF(h,s,l);
        ui->label_26->setText("");
    }
    QString str_2 = (ui->comboBox_2->currentText());
    if (str_2=="RGB")
    {
        color_2 = RGB_HSL(h,s,l);
        ui->label_27->setText("");
    }
    if (str_2=="CMYK")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    if (str_2=="HSV")
    {
        color_2 = HSV_HSL(h,s,l);
        ui->label_27->setText("");
    }
    if (str_2=="HSL")
    {
        color_2.setHslF(h,s,l);
        ui->label_27->setText("");
    }
    QString str_3 = (ui->comboBox_3->currentText());
    if (str_3=="RGB")
    {
        color_3 = RGB_HSL(h,s,l);
        ui->label_28->setText("");
    }
    if (str_3=="CMYK")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    if (str_3=="HSV")
    {
        color_3 = HSV_HSL(h,s,l);
        ui->label_28->setText("");
    }
    if (str_3=="HSL")
    {
        color_3.setHslF(h,s,l);
        ui->label_28->setText("");
    }
    }
     update();
}

void MainWindow::on_pushButton_6_clicked()//from xyz
{
    float x,y,z;
    QString str = ui->lineEdit_14->text();
    x = str.toFloat();
    str = ui->lineEdit_15->text();
    y = str.toFloat();
    str = ui->lineEdit_16->text();
    z = str.toFloat();
    if (x > 1 || y > 1 || z > 1 || x<0 || y<0 || z<0)
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Out of range");
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Out of range");
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Out of range");
    }
    else{
    str = (ui->comboBox->currentText());
    if (str=="RGB")
    {
        color = RGB_XYZ(x,y,z);
        ui->label_26->setText("");
    }
    if (str=="CMYK")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    if (str=="HSV")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    if (str=="HSL")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    QString str_2 = (ui->comboBox_2->currentText());
    if (str_2=="RGB")
    {
        color_2 = RGB_XYZ(x,y,z);
        ui->label_27->setText("");
    }
    if (str_2=="CMYK")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    if (str_2=="HSV")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    if (str_2=="HSL")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    QString str_3 = (ui->comboBox_3->currentText());
    if (str_3=="RGB")
    {
        color_3 = RGB_XYZ(x,y,z);
        ui->label_28->setText("");
    }
    if (str_3=="CMYK")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    if (str_3=="HSV")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    if (str_3=="HSL")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    }
     update();
}

void MainWindow::on_pushButton_7_clicked()//from lab
{
    float l,a,b;
    QString str = ui->lineEdit_17->text();
    l = str.toFloat();
    str = ui->lineEdit_18->text();
    a = str.toFloat();
    str = ui->lineEdit_19->text();
    b = str.toFloat();
    if (l > 0 || a > -128 || b > -128 || l<100 || a<128 || b<128)
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Out of range");
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Out of range");
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Out of range");
    }
    else {
    str = (ui->comboBox->currentText());
    if (str=="RGB")
    {
        color = RGB_LAB(l,a,b);
        ui->label_26->setText("");
    }
    if (str=="CMYK")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    if (str=="HSV")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    if (str=="HSL")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    QString str_2 = (ui->comboBox_2->currentText());
    if (str_2=="RGB")
    {
        color_2 = RGB_LAB(l,a,b);
        ui->label_27->setText("");
    }
    if (str_2=="CMYK")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    if (str_2=="HSV")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    if (str_2=="HSL")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    QString str_3 = (ui->comboBox_3->currentText());
    if (str_3=="RGB")
    {
        color_3 = RGB_LAB(l,a,b);
        ui->label_28->setText("");
    }
    if (str_3=="CMYK")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    if (str_3=="HSV")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    if (str_3=="HSL")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    }
     update();
}

void MainWindow::on_pushButton_8_clicked()//from cmyk
{
    int c,m,y,k;
    QString str = ui->lineEdit_20->text();
    c = str.toInt();
    str = ui->lineEdit_21->text();
    m = str.toInt();
    str = ui->lineEdit_22->text();
    y = str.toInt();
    str = ui->lineEdit_23->text();
    k = str.toInt();
    if (c > 255 || m > 255 || y > 255 || k > 255|| c<0 || m<0 || y<0 || k<0)
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Out of range");
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Out of range");
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Out of range");
    }
    else{
    str = (ui->comboBox->currentText());
    if (str=="RGB")
    {
        color = RGB_CMYK(c,m,y,k);
        ui->label_26->setText("");
    }
    if (str=="CMYK")
    {
        color.setCmyk(c,m,y,k);
        ui->label_26->setText("");
    }
    if (str=="HSV")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    if (str=="HSL")
    {
        color.setRgb(255,255,255);
        ui->label_26->setText("Wrong conversion!");
    }
    QString str_2 = (ui->comboBox_2->currentText());
    if (str_2=="RGB")
    {
        color_2 = RGB_CMYK(c,m,y,k);
        ui->label_27->setText("");
    }
    if (str_2=="CMYK")
    {
        color_2.setCmyk(c,m,y,k);
        ui->label_27->setText("");
    }
    if (str_2=="HSV")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    if (str_2=="HSL")
    {
        color_2.setRgb(255,255,255);
        ui->label_27->setText("Wrong conversion!");
    }
    QString str_3 = (ui->comboBox_3->currentText());
    if (str_3=="RGB")
    {
        color_3 = RGB_CMYK(c,m,y,k);
        ui->label_28->setText("");
    }
    if (str_3=="CMYK")
    {
        color_3.setCmyk(c,m,y,k);
        ui->label_28->setText("");
    }
    if (str_3=="HSV")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    if (str_3=="HSL")
    {
        color_3.setRgb(255,255,255);
        ui->label_28->setText("Wrong conversion!");
    }
    }
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    QMessageBox::information(this,"Information about conversions","RGB receive 3 values from 0 to 255 \n \n HSV recieve 3 values from 0.0 to 1.0 \n \n HSL recieve 3 values from 0.0 to 1.0 \n \n XYZ recieve 3 values from 0.0 to 1.0 \n \n Lab recieve L from 0 to 100 value and A B from -128 to 128 values \n \n CMYK recieve 4 values from 0 to 255 \n \n All colors are converted according to derived formulas");
}
