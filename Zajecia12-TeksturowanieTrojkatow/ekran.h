#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QPushButton>

#define WYSOKOSC 1000
#define SZEROKOSC 1000

enum STRONA
{
    LEWO,
    PRAWO
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    QVector<QPoint> punkty_lewo;
    QVector<QPoint> punkty_prawo;
    bool interpolacja_status=false;
//    int promien=1;
    void drawPixel(int x, int y, int red, int green, int blue, int strona)
    {
        int width = im.width();
        int height = im.height();

        if ((x >= 0) && (x <= width) && (y >= 0) && (y <= height))
        {
            if (strona==LEWO)
            {
                uchar *pix = im.scanLine(y); // dostęp do piksela
                pix[4 * x] = blue;              // blue
                pix[4 * x + 1] = green;          // green
                pix[4 * x + 2] = red;          // red
            }
            else
            {
                uchar *pix2 = obraz.scanLine(y); // dostęp do piksela
                pix2[4 * x] = blue;               // blue
                pix2[4 * x + 1] = green;           // green
                pix2[4 * x + 2] = red;           // red
            }
        }
    }
    void drawLine_lewo(int x0, int y0, int x1, int y1)
        {
            double m = 0;
            if (x1 == x0 && y1 == y0)
            {
                drawPixel(x1, y1, 0, 0, 255, LEWO);
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
                        drawPixel(x, (int)floor(y + 0.5), 0, 0, 255, LEWO);
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
                        drawPixel((int)floor(x + 0.5), y, 0, 0, 255, LEWO);
                    }
                }
            }
        }
    void drawLine_prawo(int x0, int y0, int x1, int y1)
        {
            double m = 0;
            if (x1 == x0 && y1 == y0)
            {
                drawPixel(x1, y1, 0, 0, 255, PRAWO);
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
                        drawPixel(x, (int)floor(y + 0.5), 0, 0, 255, PRAWO);
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
                        drawPixel((int)floor(x + 0.5), y, 0, 0, 255, PRAWO);
                    }
                }
            }
        }
    void Teksturowanie()
        {
            QColor color;
            int najnizszy = punkty_lewo[0].y();
            int najwyzej = punkty_lewo[0].y();
            int najbardziejNaLewo = punkty_lewo[0].x();
            int najbardziejNaPrawo = punkty_lewo[0].x();

            for (int i = 1; i < (int)punkty_lewo.size(); i++)
            {
                if (punkty_lewo[i].y() < najnizszy)
                    najnizszy = punkty_lewo[i].y();
                if (punkty_lewo[i].y() > najwyzej)
                    najwyzej = punkty_lewo[i].y();
                if (punkty_lewo[i].x() < najbardziejNaLewo)
                    najbardziejNaLewo = punkty_lewo[i].x();
                if (punkty_lewo[i].x() > najbardziejNaPrawo)
                    najbardziejNaPrawo = punkty_lewo[i].x();
            }

            double wyznaczik = (punkty_lewo[0].y() - punkty_lewo[1].y()) * (punkty_lewo[2].x() - punkty_lewo[1].x()) + (punkty_lewo[1].x() - punkty_lewo[0].x()) * (punkty_lewo[2].y() - punkty_lewo[1].y());
            for (int y = najnizszy; y < najwyzej; y++)
            {
                for (int x = najbardziejNaLewo; x < najbardziejNaPrawo; x++)
                {
                    // wspolrzednych barycentrycznych
                    double w = ((punkty_lewo[1].y() - punkty_lewo[2].y()) * (x - punkty_lewo[2].x()) + (punkty_lewo[2].x() - punkty_lewo[1].x()) * (y - punkty_lewo[2].y())) / wyznaczik;
                    double v = ((punkty_lewo[2].y() - punkty_lewo[0].y()) * (x - punkty_lewo[2].x()) + (punkty_lewo[0].x() - punkty_lewo[2].x()) * (y - punkty_lewo[2].y())) / wyznaczik;
                    double u = 1.0 - w - v;

                    // sprawdzenie czy punkt lezy w trojkacie
                    if (u >= 0 && u < 1 && v >= 0 && v < 1 && w >= 0 && w < 1)
                    {
                        double Punkt_x = u * punkty_prawo[2].x() + v * punkty_prawo[1].x() + w * punkty_prawo[0].x();
                        double Punkt_y = u * punkty_prawo[2].y() + v * punkty_prawo[1].y() + w * punkty_prawo[0].y();

                        color = obraz.pixelColor(Punkt_x-500, Punkt_y);

                        if (interpolacja_status == true)
                            color = InterpolacjaDwuliniowa(&obraz, Punkt_x-500, Punkt_y); // obraz - obrazek oryginalny

                        drawPixel(x, y, color.red(), color.green(), color.blue(), LEWO);
                        update();
                    }
                }
            }
        }
        QColor InterpolacjaDwuliniowa(QImage *im, double x, double y)
        {
            if (floor(x) >= 0 && ceil(x) <= 500 && floor(y) >= 0 && ceil(y) <= 1000)
            {
                unsigned char *pix;
                pix = im->bits();

                int red, green, blue;
                double a = x - floor(x);
                double b = y - floor(y);
                red = (1-b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 500 * floor(y)) + 2)] + a * (double)pix[(int)(4 * (ceil(x) + 500 * floor(y)) + 2)])
                        +  (b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 500 * ceil(y)) + 2)] + a * (double)pix[(int)(4 * (ceil(x) + 500 * ceil(y)) + 2)]);
                green = (1-b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 500 * floor(y)) + 1)] + a * (double)pix[(int)(4 * (ceil(x) + 500 * floor(y)) + 1)])
                        + (b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 500 * ceil(y)) + 1)] + a * (double)pix[(int)(4 * (ceil(x) + 500 * ceil(y)) + 1)]);
                blue = (1-b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 500 * floor(y)) + 0)] + a * (double)pix[(int)(4 * (ceil(x) + 500 * floor(y)) + 0)])
                        + (b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 500 * ceil(y)) + 0)] + a * (double)pix[(int)(4 * (ceil(x) + 500 * ceil(y)) + 0)]);
                        
                return QColor(red, green, blue);
            }
            else
                return QColor(0, 0, 0);
        }

    explicit Ekran(QWidget *parent = nullptr);

public slots:
    void reset();
    void interpolacja_change();
    void rysuj();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *);
signals:

private:
    QImage obraz;
    QImage im;

};

#endif // EKRAN_H
