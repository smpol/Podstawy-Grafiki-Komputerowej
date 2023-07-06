#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <QThread>
#include <QPushButton>
#include <QWidget>

#define wysokosc 690
#define szerokosc 1000

Ekran::Ekran(QWidget *parent)    : QWidget{parent}
{
    im = QImage (szerokosc, wysokosc, QImage::Format_RGB32);
    obraz = QImage(QString::fromStdString("/Users/michal/Documents/Qt/grafika komp/ZajeciaOstatnie-3D/images1.jpg"));
    punkty_pocz.append({250,180,0});
    punkty_pocz.append({250,180,200});
    punkty_pocz.append({450,180,0});
    punkty_pocz.append({450,180,200});
    punkty_pocz.append({250,350,0});
    punkty_pocz.append({250,350,200});
    punkty_pocz.append({450,350,0});
    punkty_pocz.append({450,350,200});
    im.fill(0);
    przeksztalcenia();

}
void Ekran::aktualizuj()
{
    im.fill(0);
    przeksztalcenia();
    update();
}
void Ekran::moveX(int i)
{
    qDebug("wartość X %d", i);
    tX=i;
    aktualizuj();
}
void Ekran::moveY(int i)
{
    qDebug("wartość Y %d", i);
    tY=i;
    aktualizuj();
}
void Ekran::moveZ(int i)
{
    qDebug("wartość Z %d", i);
    tZ=i;
    aktualizuj();
}
void Ekran::set_sX(int i)
{
    qDebug ("Wartosc sX %d", i);
    sX=(float)i/100;
    aktualizuj();
}
void Ekran::set_sY(int i)
{
    qDebug ("Wartosc sY %d", i);
    sY=(float)i/100;
    aktualizuj();
}
void Ekran::set_sZ(int i)
{
    qDebug ("Wartosc sZ %d", i);
    sZ=(float)i/100;
    aktualizuj();
}
void Ekran::set_obrotX(int i)
{
    qDebug ("Wartosc obrotu %d", i);
    rotacja_x=i;
    aktualizuj();
}
void Ekran::set_obrotY(int i)
{
    qDebug ("Wartosc obrotu %d", i);
    rotacja_y=i;
    aktualizuj();
}
void Ekran::set_obrotZ(int i)
{
    qDebug ("Wartosc obrotu %d", i);
    rotacja_z=i;
    aktualizuj();
}

void Ekran::ukrywanie_scian(bool i)
{
    if (i==true)
        ukrycie_scian=true;
    else
        ukrycie_scian=false;
    aktualizuj();
}
void Ekran::teksturowanie(bool i)
{
    if (i==true)
        teskturowanie_scian=true;
    else
        teskturowanie_scian=false;
    aktualizuj();
}
void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0, 0, im);
    aktualizuj();
}

