#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <algorithm>
#include <cmath>
#include <QPushButton>
#include <QStack>
#include <QtAlgorithms>
#include <QColorDialog>

#define WYSOKOSC 550
#define SZEROKOSC 550


enum RGB
{
    RED,
    GREEN,
    BLUE
};
enum WARSTWA
{
    KOLOR,
    CZARNY_BIALY,
    WYNIKOWA,
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    int promien=1;
    void drawPixel(int x, int y, int red, int green, int blue)
    {
        int width = im.width();
        int height = im.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela
            pix[4 * x] = blue;
            pix[4 * x + 1] = green;
            pix[4 * x + 2] = red;
        }
    }
    void drawPixel_oryginal(int x, int y, int red, int green, int blue)
    {
        int width = im.width();
        int height = im.height();


            if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = im_blackwhite_oryginal.scanLine(y); // dostęp do piksela
            pix[4 * x] = blue;
            pix[4 * x + 1] = green;
            pix[4 * x + 2] = red;
        }
    }
    int getColor(int x, int y, int WARSTWA, int RGB)
    {
        int width = im.width();
        int height = im.height();
        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            if (WARSTWA == KOLOR)
            {
                uchar *pix = im_kolor.scanLine(y); // dostęp do piksela
                if (RGB == RED)
                {
                    return pix[4 * x + 2];
                }
                else if (RGB == GREEN)
                {
                    return pix[4 * x + 1];
                }
                else if (RGB == BLUE)
                {
                    return pix[4 * x];
                }
            }
            if (WARSTWA == CZARNY_BIALY)
            {
                uchar *pix = im_blackwhite_oryginal.scanLine(y); // dostęp do piksela
                if (RGB == RED)
                {
                    return pix[4 * x + 2];
                }
                else if (RGB == GREEN)
                {
                    return pix[4 * x + 1];
                }
                else if (RGB == BLUE)
                {
                    return pix[4 * x];
                }
            }
            if (WARSTWA == WYNIKOWA)
            {
                uchar *pix = im.scanLine(y); // dostęp do piksela
                if (RGB == RED)
                {
                    return pix[4 * x + 2];
                }
                else if (RGB == GREEN)
                {
                    return pix[4 * x + 1];
                }
                else if (RGB == BLUE)
                {
                    return pix[4 * x];
                }
            }
        }
        return 0;
    }
    
    void color_to_blackwhite()
    {
       for (int y = 0; y < WYSOKOSC; y++)
        {
            for (int x = 0; x < SZEROKOSC; x++)
            {
                int red = getColor(x, y, KOLOR, RED);
                int green = getColor(x, y, KOLOR, GREEN);
                int blue = getColor(x, y, KOLOR, BLUE);
                int value = (red + green + blue) / 3;
                if (value > 127)
                {
                    value = 255;
                }
                else
                {
                    value = 0;
                }
                drawPixel(x, y, value, value, value);
                drawPixel_oryginal(x, y, value, value, value);
                
                //qDebug("%d", gray);
            }
        }
    }
    void dylatacja(int promien)
    {
        for (int y = 0; y < WYSOKOSC; y++)
        {
            for (int x = 0; x < SZEROKOSC; x++)
            {
                int wartosc = getColor(x, y, CZARNY_BIALY, RED);

                if (wartosc == 0)
                {
                    for (int i = -promien; i <= promien; i++)
                    {
                        for (int j = -promien; j <= promien; j++)
                        {
                            drawPixel(x + i, y + j, 0, 0, 0);
                        }
                    }
                }
            }
        }
    }
    void erozja(int promien)
    {
        for (int y = 0; y < WYSOKOSC; y++)
        {
            for (int x = 0; x < SZEROKOSC; x++)
            {
                int wartosc = getColor(x, y, CZARNY_BIALY, RED);

                if (wartosc == 255)
                {
                    for (int i = -promien; i <= promien; i++)
                    {
                        for (int j = -promien; j <= promien; j++)
                        {
                            drawPixel(x + i, y + j, 255, 255, 255);
                        }
                    }
                }
            }
        }
    }
    void copy_warstwa()
    {
        for (int y = 0; y < WYSOKOSC; y++)
        {
            for (int x = 0; x < SZEROKOSC; x++)
            {
                int wartosc = getColor(x, y, WYNIKOWA, RED);
                drawPixel_oryginal(x, y, wartosc, wartosc, wartosc);
            }
        }
    }

    explicit Ekran(QWidget *parent = nullptr);

public slots:
    void alpha_set(int i);
    void dylatacja_przycisk();
    void erozja_przycisk();
    void operacja3_przycisk();
    void operacja4_przycisk();


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:
private:
    QImage im_blackwhite_oryginal;
    QImage im_kolor;
    QImage im;

};

#endif // EKRAN_H
