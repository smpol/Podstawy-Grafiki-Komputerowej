#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <algorithm>
#include <cmath>
#include <QPushButton>
#include <QStack>
#include <QtAlgorithms>
#include <QColorDialog>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
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

    QColor InterpolacjaDwuliniowa(QImage* im, double x, double y)
    {
        if (floor(x) >= 0 && ceil(x) <= 400 && floor(y) >= 0 && ceil(y) <= 400)
        {
            unsigned char* pix;
            pix = im->bits();

            int red, green, blue;
            double a = x - floor(x);
            double b = y - floor(y);

            red = b * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 400 * ceil(y)) + 2)] + a * (double)pix[(int)(4 * (ceil(x) + 400 * ceil(y)) + 2)])
                    + (1.0 - b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 400 * floor(y)) + 2)] + a * (double)pix[(int)(4 * (ceil(x) + 400 * floor(y)) + 2)]);
            green = b * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 400 * ceil(y)) + 1)] + a * (double)pix[(int)(4 * (ceil(x) + 400 * ceil(y)) + 1)])
                    + (1.0 - b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 400 * floor(y)) + 1)] + a * (double)pix[(int)(4 * (ceil(x) + 400 * floor(y)) + 1)]);
            blue = b * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 400 * ceil(y)) + 0)] + a * (double)pix[(int)(4 * (ceil(x) + 400 * ceil(y)) + 0)])
                    + (1.0 - b) * ((1.0 - a) * (double)pix[(int)(4 * (floor(x) + 400 * floor(y)) + 0)] + a * (double)pix[(int)(4 * (ceil(x) + 400 * floor(y)) + 0)]);

            return QColor(red, green, blue);
        }
        else
        {
            return QColor(0, 0, 0); //kolor tla
        }
    }
    void przeksztalcenia2d(double move_x, double move_y, double sX, double sY, double stopnie, double shX, double shY, bool interpolacja)
    {
        double M1[3][3] = {{1, 0, 200},
                           {0, 1, 200},
                           {0, 0, 1}}; // srodek obrazka zrodlowego (bo ma wymiary 400x400)

        double M2[3][3] = {{1, 0, -270},
                           {0, 1, -270},
                           {0, 0, 1}}; // przesuniecie obrazka na srodek

        double Mxy[3][3] = {{1, 0, -move_x},
                            {0, 1, -move_y},
                            {0, 0, 1}};

        double rad = stopnie * (M_PI / 180); // stopnie na radiany

        double R[3][3] = {{cos(-rad), -sin(-rad), 0},
                          {sin(-rad), cos(-rad), 0},
                          {0, 0, 1}}; // macierz obrotu

        double S[3][3] = {{1/sX, 0, 0},
                          {0, 1/sY, 0},
                          {0, 0, 1}}; // macierz skalowania

        double Sh_x[3][3] = {{1, shX, 0},
                             {0, 1, 0},
                             {0, 0, 1}}; //macierz sharing

        double Sh_y[3][3] = {{1, 0, 0},
                             {shY, 1, 0},
                             {0, 0, 1}}; //macierz sharing

        double Macierz_wynikowa[3][3];

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                Macierz_wynikowa[i][j] = 0;
                for (int k = 0; k < 3; k++)
                {
                    Macierz_wynikowa[i][j] += M1[i][k] * R[k][j];
                }
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                double sum = 0;
                for (int k = 0; k < 3; k++)
                {
                    sum += Macierz_wynikowa[i][k] * S[k][j];
                }
                Macierz_wynikowa[i][j] = sum;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                double sum = 0;
                for (int k = 0; k < 3; k++)
                {
                    sum += Macierz_wynikowa[i][k] * Sh_y[k][j];
                }
                Macierz_wynikowa[i][j] = sum;
            }
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                double sum = 0;
                for (int k = 0; k < 3; k++)
                {
                    sum += Macierz_wynikowa[i][k] * Sh_x[k][j];
                }
                Macierz_wynikowa[i][j] = sum;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                double sum = 0;
                for (int k = 0; k < 3; k++)
                {
                    sum += Macierz_wynikowa[i][k] * Mxy[k][j];
                }
                Macierz_wynikowa[i][j] = sum;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                double sum = 0;
                for (int k = 0; k < 3; k++)
                {
                    sum += Macierz_wynikowa[i][k] * M2[k][j];
                }
                Macierz_wynikowa[i][j] = sum;
            }
        }

        for (int i = 0; i < im.width(); i++)
        {
            for (int j = 0; j < im.height(); j++)
            {
                double P[3][1] = {{(double)i}, {(double)j}, {1}}; // punkt
                double P_przeksztalcone[3][1]; // punkt po przeksztalceniu
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 1; j++)
                    {
                        P_przeksztalcone[i][j] = 0;
                        for (int k = 0; k < 3; k++)
                        {
                            P_przeksztalcone[i][j] += Macierz_wynikowa[i][k] * P[k][j];
                        }
                    }
                }
                if (P_przeksztalcone[0][0] >= 0 && P_przeksztalcone[0][0] < 400 && P_przeksztalcone[1][0] >= 0 && P_przeksztalcone[1][0] < 400)
                {
                    int red = qRed(obraz_zrodlo.pixel(P_przeksztalcone[0][0], P_przeksztalcone[1][0]));
                    int green = qGreen(obraz_zrodlo.pixel(P_przeksztalcone[0][0], P_przeksztalcone[1][0]));
                    int blue = qBlue(obraz_zrodlo.pixel(P_przeksztalcone[0][0], P_przeksztalcone[1][0]));
                    if (!interpolacja)
                    {
                        drawPixel(i, j, red, green, blue);
                    }
                    else
                    {
                        QColor temp = InterpolacjaDwuliniowa(&obraz_zrodlo, P_przeksztalcone[0][0], P_przeksztalcone[1][0]);
                        drawPixel(i, j, temp.red(), temp.green(), temp.blue());
                    }
                }
            }
        }
    }

public slots:
    void moveX(int);
    void moveY(int);
    void set_sX(int);
    void set_sY(int);
    void set_obrot(int);
    void interpelacja_set(bool);
    void update_draw();
    void set_shX(int);
    void set_shY(int);

protected:
    void paintEvent(QPaintEvent *event);
signals:
private:
    QImage im;
    QImage im_copy;
    QImage obraz_zrodlo;
};

#endif // EKRAN_H
