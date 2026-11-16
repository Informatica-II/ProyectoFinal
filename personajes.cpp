#include "personajes.h"

Personajes::Personajes(QObject *parent): QObject{parent}
{
    timer = new QTimer();

    columna = 0;

    pixmap = new QPixmap(":/imagenes/Run_Back_Homero-removebg-preview.png");
    ancho = 100;

    timer->start(100);

    connect(timer, &QTimer::timeout, this, &Personajes::actualizar);

}

void Personajes::actualizar()
{
    columna += 100;
    if(columna >= 1400){
        columna = 0;
    }
    this ->update(-ancho/2,-100/2,ancho,100);
}

QRectF Personajes::boundingRect() const
{
    return QRectF(-ancho/2,-100/2,ancho,100);
}

void Personajes::pain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-100/2,*pixmap,columna,0,ancho,100);
}