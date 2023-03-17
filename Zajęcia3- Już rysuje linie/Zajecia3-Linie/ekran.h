#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <algorithm>
#include <cmath>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);

    int **narysowane_linie; // tablica dynamiczna w ktorej bedziemy przechowywac piksele lini gdzie jest juz narysowana linia

    void tablica_zapisanych_lini() // alokowanie dynamicznej tablicy
    {

        int width = im.width();
        int height = im.height();

        narysowane_linie = new int*[height];
        for (int i=0; i<=height; i++)
        {
            narysowane_linie[i] = new int [width];
        }

        for (int i=0; i<height; i++)
        {
            for (int j=0; j< width; j++)
                narysowane_linie[i][j]=0;
        }
    }
    void drawPixel(int x, int y, int flag)
    {

        //legenda flag
        // 0 - rysujemy tymczasowa linie
        // 1 - rysujemy finalna linie
        // 2 - rysujemy czarny piskel
        int width = im.width();
        int height = im.height();

        //qDebug("%d %d", width, height);


        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela?
            if (flag == 2)
            {
                pix[4 * x] = 0;            // blue
                pix[4 * x + 1] = 0;        // green
                pix[4 * x + 2] = 0;
                narysowane_linie[x][y]=0;
            }
            else
            {
                pix[4 * x] = 255;            // blue
                pix[4 * x + 1] = 255;        // green
                pix[4 * x + 2] = 255;        // red
                if (flag == 1)
                {
                    narysowane_linie[x][y] = 1;
                }
            }

        }
    }
    void clearPixel(int x, int y)
    {
        int width = im.width();
        int height = im.height();
        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela?
            if (narysowane_linie[x][y] == 0)
            {
                pix[4 * x] = 0;              // blue
                pix[4 * x + 1] = 0;          // green
                pix[4 * x + 2] = 0;          // red
            }
        }
    }
    void drawLine(int x0, int y0, int x1, int y1, int flag)
    {
        //legenda flag
        // 0 - rysuje tymczasowa linie
        // 1 - usuwa tymczasowa linie
        // 2 - rysuje finalna linie
        bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
        if (steep)
        { // jeśli linia jest "stroma", zamień współrzędne x i y
            std::swap(x0, y0);
            std::swap(x1, y1);
        }

        if (x0 > x1)
        { // jeśli punkt startowy jest po prawej stronie punktu końcowego, zamień je miejscami
            std::swap(x0, x1);
            std::swap(y0, y1);
        }

        int dx = x1 - x0;
        int dy = std::abs(y1 - y0);
        int error = dx / 2;             // zmienna pomocnicza używana do obliczenia błędu przy wyznaczaniu kolejnych punktów na linii
        int ystep = (y0 < y1) ? 1 : -1; // ustal kierunek rysowania linii
        int y = y0;
        for (int x = x0; x <= x1; x++)
        {
            if (steep)
            { // jeśli linia jest "stroma", narysuj punkt o współrzędnych zamienionych miejscami
                if (flag == 0)
                    drawPixel(y, x, 0);
                else if (flag == 2)
                    drawPixel(y, x, 1);
                else
                    clearPixel(y, x);
            }
            else
            {
                if (flag == 0)
                    drawPixel(x, y, 0);
                else if (flag == 2)
                    drawPixel(x, y, 1);
                else
                    clearPixel(x, y);
            }
            error -= dy;
            if (error < 0)
            {
                y += ystep; // jeśli błąd jest mniejszy niż 0, przesuń się do kolejnego punktu na linii
                error += dx;
            }
        }
    }

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
private:
    QImage im;
};


#endif // EKRAN_H
