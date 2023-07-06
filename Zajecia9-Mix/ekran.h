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
    red,
    green,
    blue
};
enum WARSTWA
{
    WARSTWA1,
    WARSTWA2,
    WARSTWA3,
    WYNIKOWA,
    TEMP
};
enum TRYB
{
    NORMAL,
    MULTIPLY,
    SCREEN,
    OVERLAY,
    DARKEN
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    void update_warstw();
    void drawPixel(int x, int y, int red, int green, int blue)
    {
        int width=wynik.width();
        int height=wynik.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = wynik.scanLine(y); // dostęp do piksela
            pix[4 * x] = blue;
            pix[4 * x + 1] = green;
            pix[4 * x + 2] = red;
        }
    }
    void drawPixel_temp(int x, int y, int red, int green, int blue)
    {
        int width=wynik.width();
        int height=wynik.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = temp.scanLine(y); // dostęp do piksela
            pix[4 * x] = blue;
            pix[4 * x + 1] = green;
            pix[4 * x + 2] = red;
        }
    }
    int getColor(int x, int y, int warstwa_selected, int RGB)
    {
        int width=wynik.width();
        int height=wynik.height();
        uchar *pix = wynik.scanLine(y);
        if (warstwa_selected==WARSTWA1)
            pix = im0.scanLine(y); // dostęp do piksela
        else if (warstwa_selected==WARSTWA2)
            pix = im1.scanLine(y); // dostęp do piksela
        else if (warstwa_selected==WARSTWA3)
            pix = im2.scanLine(y); // dostęp do piksela
        else if (warstwa_selected==WYNIKOWA)
            pix = wynik.scanLine(y);
        else if (warstwa_selected==TEMP)
            pix = temp.scanLine(y);

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            if (RGB == red)
            {
                return pix[4 * x + 2];
            }
            if (RGB == green)
            {
                return pix[4 * x + 1];
            }
            if (RGB == blue)
            {
                return pix[4 * x];
            }
        }
        return 0;
    }
    void zmiana_alpha(int i)
    {
        double alpha = i / 100.0;
        for (int y = 0; y < WYSOKOSC; y++)
        {
            for (int x = 0; x < SZEROKOSC; x++)
            {
                int red_background = getColor(x, y, WYNIKOWA, red);
                int green_background = getColor(x, y, WYNIKOWA, green);
                int blue_background = getColor(x, y, WYNIKOWA, blue);

                int red_foreground = getColor(x, y, TEMP, red);
                int green_foreground = getColor(x, y, TEMP, green);
                int blue_foreground = getColor(x, y, TEMP, blue);

                int red = alpha * red_foreground + (1 - alpha) * red_background;
                int green = alpha * green_foreground + (1 - alpha) * green_background;
                int blue = alpha * blue_foreground + (1 - alpha) * blue_background;

                drawPixel(x, y, red, green, blue);
            }
        }
    }
   void normal_mode(int warstwa)
   {
       for (int y = 0; y < WYSOKOSC; y++)
       {
           for (int x = 0; x < SZEROKOSC; x++)
           {

               int red_foreground = getColor(x, y, warstwa, red);
               int green_foreground = getColor(x, y, warstwa, green);
               int blue_foreground = getColor(x, y, warstwa, blue);

               drawPixel_temp(x, y, red_foreground, green_foreground, blue_foreground);
           }
       }
   }

   void multiply_mode(int warstwa)
   {
       for (int y = 0; y < WYSOKOSC; y++)
       {
           for (int x = 0; x < SZEROKOSC; x++)
           {
               int red_background = getColor(x, y, WYNIKOWA, red);
               int green_background = getColor(x, y, WYNIKOWA, green);
               int blue_background = getColor(x, y, WYNIKOWA, blue);

               int red_foreground = getColor(x, y, warstwa, red);
               int green_foreground = getColor(x, y, warstwa, green);
               int blue_foreground = getColor(x, y, warstwa, blue);

               int red = (red_foreground * red_background)>>8;
               int green = (green_foreground * green_background)>>8;
               int blue = (blue_foreground * blue_background)>>8;

               drawPixel_temp(x, y, red, green, blue);
           }
       }
   }
   void screen_mode(int warstwa)
   {
       for (int y = 0; y < WYSOKOSC; y++)
       {
           for (int x = 0; x < SZEROKOSC; x++)
           {
               int red_background = getColor(x, y, WYNIKOWA, red);
               int green_background = getColor(x, y, WYNIKOWA, green);
               int blue_background = getColor(x, y, WYNIKOWA, blue);

               int red_foreground = getColor(x, y, warstwa, red);
               int green_foreground = getColor(x, y, warstwa, green);
               int blue_foreground = getColor(x, y, warstwa, blue);

               int red = 255 - (((255 - red_foreground) * (255 - red_background)) >> 8);
               int green = 255 - (((255 - green_foreground) * (255 - green_background)) >> 8);
               int blue = 255 - (((255 - blue_foreground) * (255 - blue_background)) >> 8);

               drawPixel_temp(x, y, red, green, blue);
           }
       }
   }

   void overlay_mode(int warstwa)
   {
       for (int y = 0; y < WYSOKOSC; y++)
       {
           for (int x = 0; x < SZEROKOSC; x++)
           {
               int red_background = getColor(x, y, WYNIKOWA, red);
               int green_background = getColor(x, y, WYNIKOWA, green);
               int blue_background = getColor(x, y, WYNIKOWA, blue);

               int red_foreground = getColor(x, y, warstwa, red);
               int green_foreground = getColor(x, y, warstwa, green);
               int blue_foreground = getColor(x, y, warstwa, blue);

               int red, green, blue;
               if (red_foreground < 128)
                   red =(red_background*red_foreground)>>7;
               else
                   red = 255 - (((255 - red_foreground) * (255 - red_background)) >> 7);

               if (green_foreground < 128)
                   green = (green_background*green_foreground)>>7;
               else
                   green = 255 - (((255 - green_foreground) * (255 - green_background)) >> 7);

               if (blue_foreground < 128)
                   blue = (blue_background*blue_foreground)>>7;
               else
                   blue = 255 - (((255 - blue_foreground) * (255 - blue_background)) >> 7);
               drawPixel_temp(x, y, red, green, blue);
           }
       }
   }

   void darken_mode(int warstwa)
   {
       for (int y = 0; y < WYSOKOSC; y++)
       {
           for (int x = 0; x < SZEROKOSC; x++)
           {
               int red_background = getColor(x, y, WYNIKOWA, red);
               int green_background = getColor(x, y, WYNIKOWA, green);
               int blue_background = getColor(x, y, WYNIKOWA, blue);

               int red_foreground = getColor(x, y, warstwa, red);
               int green_foreground = getColor(x, y, warstwa, green);
               int blue_foreground = getColor(x, y, warstwa, blue);

               int red,green, blue;

               if (red_foreground < red_background)
                   red = red_foreground;
               else
                   red = red_background;
               if (green_foreground < green_background)
                   green = green_foreground;
               else
                   green = green_background;
               if (blue_foreground < blue_background)
                   blue = blue_foreground;
               else
                   blue = blue_background;
                


               drawPixel_temp(x, y, red, green, blue);
           }
       }
   }
    explicit Ekran(QWidget *parent = nullptr);

public slots:
    void wybrana_warstwa1();
    void wybrana_warstwa2();
    void wybrana_warstwa3();
    void alpha_set(int i);
    void normal_set();
    void multiply_set();
    void screen_set();
    void overlay_set();
    void darken_set();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:
private:
//    QImage im1;
//    QImage im2;
//    QImage im;
    //QImage obrazy[3];
    QImage im0, im1, im2;
    QImage wynik, temp;

};

#endif // EKRAN_H
