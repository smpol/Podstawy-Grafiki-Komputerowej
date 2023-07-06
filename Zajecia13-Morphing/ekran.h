#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QPushButton>

#define WYSOKOSC 600
#define SZEROKOSC 900

enum OBRAZ
{
    OBRAZ1,
    OBRAZ2,
    OBRAZ_PODLGLAD,
    WYNIKOWA
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QVector<QPoint> obraz_1;
    QVector<QPoint> obraz_2;
    QVector<QPoint> wynik;
    void drawPixel(int x, int y, int red, int green, int blue, int warstwa)
    {
        int width = im.width();
        int height = im.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            if (warstwa == OBRAZ_PODLGLAD)
            {
                uchar *pix = obraz.scanLine(y); // dostęp do piksela
                pix[4 * x] = blue;              // blue
                pix[4 * x + 1] = green;         // green
                pix[4 * x + 2] = red;           // red
            }
            else if (warstwa == WYNIKOWA)
            {
                uchar *pix = im.scanLine(y); // dostęp do piksela
                pix[4 * x] = blue;           // blue
                pix[4 * x + 1] = green;      // green
                pix[4 * x + 2] = red;
            }
        }
    }
    void drawLine(int x0, int y0, int x1, int y1)
    {
        double m = 0;
        if (x1 == x0 && y1 == y0)
        {
            drawPixel(x1, y1, 0, 0, 255, OBRAZ_PODLGLAD);
        }
        else
        {
            if (abs(x1 - x0) >= abs(y1 - y0))
            {
                if (x0 > x1)
                {
                    std::swap(y0, y1);
                    std::swap(x0, x1);
                }
                m = (double)(y1 - y0) / (x1 - x0);
                for (int x = x0; x <= x1; x++)
                {
                    int y = m * (x - x0) + y0;
                    drawPixel(x, (int)floor(y + 0.5), 0, 0, 255, OBRAZ_PODLGLAD);
                }
            }
            else
            {
                if (y0 > y1)
                {
                    std::swap(x0, x1);
                    std::swap(y0, y1);
                }
                m = (double)(x1 - x0) / (y1 - y0);
                for (int y = y0; y <= y1; y++)
                {
                    int x = m * (y - y0) + x0;
                    drawPixel((int)floor(x + 0.5), y, 0, 0, 255, OBRAZ_PODLGLAD);
                }
            }
        }
    }
    void drawLine_wynikowa(int x0, int y0, int x1, int y1)
    {
        double m = 0;
        if (x1 == x0 && y1 == y0)
        {
            drawPixel(x1, y1, 0, 0, 255, WYNIKOWA);
        }
        else
        {
            if (abs(x1 - x0) >= abs(y1 - y0))
            {
                if (x0 > x1)
                {
                    std::swap(y0, y1);
                    std::swap(x0, x1);
                }
                m = (double)(y1 - y0) / (x1 - x0);
                for (int x = x0; x <= x1; x++)
                {
                    int y = m * (x - x0) + y0;
                    drawPixel(x, (int)floor(y + 0.5), 0, 0, 255, WYNIKOWA);
                }
            }
            else
            {
                if (y0 > y1)
                {
                    std::swap(x0, x1);
                    std::swap(y0, y1);
                }
                m = (double)(x1 - x0) / (y1 - y0);
                for (int y = y0; y <= y1; y++)
                {
                    int x = m * (y - y0) + x0;
                    drawPixel((int)floor(x + 0.5), y, 0, 0, 255, WYNIKOWA);
                }
            }
        }
    }

    void punkty(int stopien)
    {
        wynik.clear();
        im.fill(0);
        for (int i = 0; i < 3; i++)
        {
            float x, y;
            x = (1.0f - stopien / 100.0f) * obraz_1[i].x() + (stopien / 100.0f) * obraz_2[i].x();
            y = (1.0f - stopien / 100.0f) * obraz_1[i].y() + (stopien / 100.0f) * obraz_2[i].y();
            wynik.push_back(QPoint(x, y));
        }
    }
    void morphing(int stopien)
    {
        if (wynik.size() < 2)
            return;
        int y_min = wynik[0].y();
        int y_max = wynik[0].y();

        for (int i = 0; i < wynik.size(); i++)
        {
            if (wynik[i].y() > y_max)
                y_max = wynik[i].y();
            if (wynik[i].y() < y_min)
                y_min = wynik[i].y();
        }

        for (int y = y_min; y <= y_max; y++)
        {
            int min_x = WYSOKOSC + 1;
            int max_x = 0;

            for (int i = 0; i < wynik.size(); i++)
            {
                int p1 = i, p2 = (i + 1) % wynik.size(); // Dla każdej pary punktów 0,1 1,2 2,0

                if (wynik[p1].y() > wynik[p2].y()) // Sprawdzenie, który punkt jest wyżej (dla uproszczenia obliczeń)
                    std::swap(p1, p2);             // Zamiana miejscami p1 i p2

                if (y >= wynik[p1].y() && y < wynik[p2].y() && wynik[p1].y() != wynik[p2].y()) // Sprawdzenie, czy y przecina się z linią między punktami p1 i p2
                {
                    int x = wynik[p1].x() + (y - wynik[p1].y()) * (wynik[p2].x() - wynik[p1].x()) / (wynik[p2].y() - wynik[p1].y()); // Obliczenie x na podstawie równania linii

                    if (x < min_x) // Sprawdzenie, czy x jest mniejsze niż dotychczasowe najmniejsze x
                        min_x = x;

                    if (x > max_x) // Sprawdzenie, czy x jest większe niż dotychczasowe największe x
                        max_x = x;
                }
            }

            if (min_x < max_x)
            {
                double alpha = stopien / (double)100.0;
                QPoint A = wynik[0];
                QPoint B = wynik[1];
                QPoint C = wynik[2];

                double wyznacznik = (B.x() - A.x()) * (C.y() - A.y()) - (B.y() - A.y()) * (C.x() - A.x());
                for (int x = min_x; x < max_x; x++)
                {
                    double v = ((double)x - A.x()) * (C.y() - A.y()) - ((double)y - A.y()) * (C.x() - A.x());
                    double w = (B.x() - A.x()) * ((double)y - A.y()) - (B.y() - A.y()) * ((double)x - A.x());

                    v /= wyznacznik;
                    w /= wyznacznik;

                    double u = 1 - v - w;

                    QPoint P = obraz_1[0];
                    QPoint Q = obraz_1[1];
                    QPoint R = obraz_1[2];

                    double obraz1_x = u * P.x() + v * Q.x() + w * R.x();
                    double obraz1_y = u * P.y() + v * Q.y() + w * R.y();

                    uchar *pix1 = obraz1.scanLine((int)obraz1_y) + 4 * (int)obraz1_x;

                    QPoint Pprim = obraz_2[0];
                    QPoint Qprim = obraz_2[1];
                    QPoint Rprim = obraz_2[2];

                    double obraz2_x = u * Pprim.x() + v * Qprim.x() + w * Rprim.x();
                    double obraz2_y = u * Pprim.y() + v * Qprim.y() + w * Rprim.y();

                    uchar *pix2 = obraz2.scanLine((int)obraz2_y) + 4 * (int)obraz2_x;

                    int red = (int)(alpha * pix2[2] + (1 - alpha) * pix1[2]);
                    int green = (int)(alpha * pix2[1] + (1 - alpha) * pix1[1]);
                    int blue = (int)(alpha * pix2[0] + (1 - alpha) * pix1[0]);

                    drawPixel(x, y, red, green, blue, WYNIKOWA);
                }
            }
        }

        for (int i = 0; i < 3; i++)
        {
            drawLine_wynikowa(wynik[i].x(), wynik[i].y(), wynik[(i + 1) % 3].x(), wynik[(i + 1) % 3].y());
        }
    }

    explicit Ekran(QWidget *parent = nullptr);

public slots:
    void zmianaObrazka1();
    void zmianaObrazka2();
    void updateObrazka();
    void zmiana_suwak(int);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *);
signals:

private:
    QImage obraz;
    QImage obraz1;
    QImage obraz2;
    QImage im;
};

#endif // EKRAN_H
