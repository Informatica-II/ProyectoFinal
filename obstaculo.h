#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "personajenivel1.h"

class Obstaculo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int velocidadX;
    int carrilAsignado;
    QTimer* timerMovimiento;
    PersonajeNivel1* homero;

public:
    Obstaculo(int carrilY, int velocidad, PersonajeNivel1* jugador);
    void detener();
    ~Obstaculo();

signals:
    void jugadorGolpeado();

public slots:
    void mover();
};

#endif // OBSTACULO_H