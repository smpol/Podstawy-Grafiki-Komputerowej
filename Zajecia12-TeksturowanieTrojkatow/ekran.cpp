#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>

#define wysokosc 1000
#define szerokosc 1000



Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{


    im=QImage(wysokosc, szerokosc, QImage::Format_RGB32);
    obraz=QImage(1000,1000, QImage::Format_RGB32);;

    im.fill(0);
    obraz.load("/Users/michal/Documents/Qt/grafika komp/Zajecia12-TeksturowanieTrojkatow/img/pan.jpg");

    update();
}


void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
    p.drawImage(500,0,obraz);
}


void Ekran::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (e->pos().x() < szerokosc/2)
        {
            if (punkty_lewo.size() < 3)
            {
                punkty_lewo.push_back(e->pos());
                drawPixel(e->pos().x(), e->pos().y(), 255, 0, 0, LEWO);
                qDebug("Lewo: %d %d", e->pos().x(), e->pos().y());
            }

        }
        else
        {
            if (punkty_prawo.size() < 3)
            {
                punkty_prawo.push_back(e->pos());
                drawPixel(e->pos().x(), e->pos().y(), 255, 0, 0, PRAWO);
                qDebug("Prawo: %d %d", e->pos().x(), e->pos().y());
            }
        }

    }
    if (punkty_prawo.size()==3)
    {
        for (int i=0; i<3; i++)
        {
            drawLine_prawo(punkty_prawo[i].x(), punkty_prawo[i].y(), punkty_prawo[(i+1)%3].x(), punkty_prawo[(i+1)%3].y());
        }
    }
    if (punkty_lewo.size()==3)
    {
        for (int i=0; i<3; i++)
        {
            drawLine_lewo(punkty_lewo[i].x(), punkty_lewo[i].y(), punkty_lewo[(i+1)%3].x(), punkty_lewo[(i+1)%3].y());
        }
    }
    rysuj();
    update();
}

void Ekran::rysuj()
{
    if (punkty_prawo.size()==3 && punkty_lewo.size()==3)
    {
        im.fill(0);
        obraz.load("/Users/michal/Documents/Qt/grafika komp/Zajecia12-TeksturowanieTrojkatow/img/pan.jpg");
        Teksturowanie();
        for (int i=0; i<3; i++)
        {
            drawLine_lewo(punkty_lewo[i].x(), punkty_lewo[i].y(), punkty_lewo[(i+1)%3].x(), punkty_lewo[(i+1)%3].y());
            drawLine_prawo(punkty_prawo[i].x(), punkty_prawo[i].y(), punkty_prawo[(i+1)%3].x(), punkty_prawo[(i+1)%3].y());
        }
    }
}

void Ekran::mouseMoveEvent(QMouseEvent *)
{

}

void Ekran::reset()
{
    punkty_lewo.clear();
    punkty_prawo.clear();
    im.fill(0);
    obraz.load("/Users/michal/Documents/Qt/grafika komp/Zajecia12-TeksturowanieTrojkatow/img/pan.jpg");
    update();
}

void Ekran::interpolacja_change()
{
    if (interpolacja_status==false)
        interpolacja_status=true;
    else
        interpolacja_status=false;
    rysuj();

}

