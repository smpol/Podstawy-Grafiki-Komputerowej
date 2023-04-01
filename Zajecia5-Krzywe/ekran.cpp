#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>
#include <vector>

#define wysokosc 1000
#define szerokosc 1000
int temp=100;
bool elipsa=false;

QVector<QPointF> points;
//std::vector<vector<int>> points_2d;
//QVector<QVector<int>> points_2d;


Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    im.fill(0);

    //im_copy=QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    //im_copy.fill(0);

}

void Ekran::wartosc(int n)
{
    temp=n;
}

void Ekran::czysc()
{
    im.fill(0);
    points.clear();
    update();
}

void Ekran::tryb_elipsa()
{
    elipsa=true;
}
void Ekran::tryb_kolo()
{
    elipsa=false;
}


void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
}

// zmienne przechowujace koordynaty 1 punktu
int startX=0;
int startY=0;
//bool elipsa=false;

void Ekran::mousePressEvent(QMouseEvent *e)
{
    int startX=e->position().x();
    int startY=e->position().y();
    points<<QPointF(startX, startY);
    if (points.size() >=4 && points.size()%3==1)
    {
        im.fill(0);
        qDebug("Wykonano, ilosc %d", (int)points.size());
        drawBezier(points, 1000);
    }

    update(); // odświeżanie okna
}

void Ekran::mouseMoveEvent(QMouseEvent *)
{

    //im=im_copy;


    update();

}

