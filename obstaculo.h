#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>
#include "PersonajeNivel1.h"

class Obstaculo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int velocidadX;
    int carrilAsignado;
    QTimer* timerMovimiento;
    PersonajeNivel1* homero;

    bool esParabolico;
    QGraphicsEllipseItem* marcaImpacto;
    float x0, y0;
    float vx, vy0;
    float gravedad;
    float tiempoActual;
    float tiempoVuelo;
    float anguloRotacion;

public:
    Obstaculo(int carrilY, int velocidad, PersonajeNivel1* jugador);
    Obstaculo(int carrilY, float duracionVuelo, PersonajeNivel1* jugador, QGraphicsScene* escena);
    void detener();
    ~Obstaculo();

signals:
    void jugadorGolpeado();

public slots:
    void mover();
};

#endif // OBSTACULO_H