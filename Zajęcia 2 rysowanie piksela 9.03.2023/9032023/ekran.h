#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    void drawPixel(int x, int y, int r, int g, int b)
    {
        int width=im.width();
        int height=im.height();
        if ((x>=0) && (x<=width) && (y>=0) && (y<=height))
        {
            uchar *pix = im.scanLine(y); // dostęp do piksela?
            pix[4*x]=b; // blue
            pix[4*x+1]=g; //green
            pix[4*x+2]=r; //red
        }

    }
    //void clear(int r=0, int g=0; int b=0)


protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *);
signals:
private:
    QImage im;
};

#endif // EKRAN_H
