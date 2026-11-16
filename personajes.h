#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>

class Personajes : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Personajes(QObject *parent = nullptr);

    QTimer *timer;
    QPixmap *pixmap;

    int columna;
    int ancho;

    QRectF boundingRect() const;
    void pain(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:
    void actualizar();
};

#endif // PERSONAJES_H
