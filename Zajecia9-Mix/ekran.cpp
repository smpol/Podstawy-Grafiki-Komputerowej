#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>



#define wysokosc 550
#define szerokosc 550

int wybrana_warstwa=2;
int alpha_value[3]={100, 100, 100};
int tryb_value[3]={NORMAL, NORMAL, NORMAL};

//bool started=false;

Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im0= QImage(550, 550, QImage::Format_RGB32);
    im1= QImage(550, 550, QImage::Format_RGB32);
    im2= QImage(550, 550, QImage::Format_RGB32);

    wynik= QImage(550, 550, QImage::Format_RGB32);
    temp= QImage(550, 550, QImage::Format_RGB32);
    
    //wynik.fill(0);
    wynik.fill(Qt::white);
    //obrazy[0].load("/Users/michal/Documents/Qt/grafika komp/Zajecia9-Mix/Resources/kosmonauta.jpeg");
    //obrazy[1].load("/Users/michal/Documents/Qt/grafika komp/Zajecia9-Mix/Resources/wydzial.jpeg");
    //obrazy[2].load("/Users/michal/Documents/Qt/grafika komp/Zajecia9-Mix/Resources/smiech.jpeg");




    // im.fill(0);
     im0.load("/Users/michal/Documents/Qt/grafika komp/Zajecia9-Mix/Resources/kosmonauta.jpeg");
     im1.load("/Users/michal/Documents/Qt/grafika komp/Zajecia9-Mix/Resources/wydzial.jpeg");
     im2.load("/Users/michal/Documents/Qt/grafika komp/Zajecia9-Mix/Resources/smiech.jpeg");

    

    update_warstw();
}

void Ekran::update_warstw()
{
    wynik.fill(Qt::white);
    for (int i=0; i<3; i++)
    {
        if (tryb_value[i]==NORMAL)
            normal_mode(i);
        else if (tryb_value[i]==MULTIPLY)
            multiply_mode(i);
        else if (tryb_value[i]==SCREEN)
            screen_mode(i);
        else if (tryb_value[i]==OVERLAY)
            overlay_mode(i);
        else if (tryb_value[i]==DARKEN)
            darken_mode(i);
        zmiana_alpha(alpha_value[i]);
    }
    update();
}

void Ekran::wybrana_warstwa1()
{
    wybrana_warstwa=0;
    qDebug("Wybrana warstwa %d, wartosc alpha %d", wybrana_warstwa+1, alpha_value[wybrana_warstwa]);
}

void Ekran::wybrana_warstwa2()
{
    wybrana_warstwa=1;
    qDebug("Wybrana warstwa %d, wartosc alpha %d", wybrana_warstwa+1, alpha_value[wybrana_warstwa]);
}

void Ekran::wybrana_warstwa3()
{
    wybrana_warstwa=2;
    qDebug("Wybrana warstwa %d, wartosc alpha %d", wybrana_warstwa+1, alpha_value[wybrana_warstwa]);
}


void Ekran::alpha_set(int i)
{
    if (wybrana_warstwa==0)
        alpha_value[0]=i;
    else if (wybrana_warstwa==1)
        alpha_value[1]=i;
    else if (wybrana_warstwa==2)
        alpha_value[2]=i;

    qDebug("Wybrana warstwa %d, alpha %d", wybrana_warstwa+1, alpha_value[wybrana_warstwa]);
    update_warstw();
}

void Ekran::normal_set()
{
    if (wybrana_warstwa==0)
        tryb_value[0]=NORMAL;
    else if (wybrana_warstwa==1)
        tryb_value[1]=NORMAL;
    else if (wybrana_warstwa==2)
        tryb_value[2]=NORMAL;
    update_warstw();
}
void Ekran::multiply_set()
{
    if (wybrana_warstwa==0)
        tryb_value[0]=MULTIPLY;
    else if (wybrana_warstwa==1)
        tryb_value[1]=MULTIPLY;
    else if (wybrana_warstwa==2)
        tryb_value[2]=MULTIPLY;
    update_warstw();
}

void Ekran::screen_set()
{
    if (wybrana_warstwa==0)
        tryb_value[0]=SCREEN;
    else if (wybrana_warstwa==1)
        tryb_value[1]=SCREEN;
    else if (wybrana_warstwa==2)
        tryb_value[2]=SCREEN;
    update_warstw();
}
void Ekran::overlay_set()
{
    if (wybrana_warstwa==0)
        tryb_value[0]=OVERLAY;
    else if (wybrana_warstwa==1)
        tryb_value[1]=OVERLAY;
    else if (wybrana_warstwa==2)
        tryb_value[2]=OVERLAY;
    update_warstw();
}

void Ekran::darken_set()
{
    if (wybrana_warstwa==0)
        tryb_value[0]=DARKEN;
    else if (wybrana_warstwa==1)
        tryb_value[1]=DARKEN;
    else if (wybrana_warstwa==2)
        tryb_value[2]=DARKEN;
    update_warstw();
}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, wynik);
}


void Ekran::mousePressEvent(QMouseEvent *)
{

}

void Ekran::mouseMoveEvent(QMouseEvent *)
{

}

