#include "Obstaculo.h"
#include <QGraphicsScene>

Obstaculo::Obstaculo(int carrilY, int velocidad, PersonajeNivel1* jugador) {
    QPixmap pixmapObstaculo(":/imagenes/Roca.png");
    setPixmap(pixmapObstaculo);

    this->velocidadX = velocidad;
    this->carrilAsignado = carrilY;
    this->homero = jugador;

    setPos(1376, carrilY + 40);

    int capaZ = 10;
    if (carrilY == 470) capaZ = 11;
    if (carrilY == 540) capaZ = 12;
    setZValue(capaZ);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Obstaculo::mover);
    timerMovimiento->start(16);
}

void Obstaculo::mover() {
    setPos(x() - velocidadX, y());

    if (this->collidesWithItem(homero)) {
        if (this->carrilAsignado == homero->getSueloActual()) {

            float alturaDelSalto = homero->getSueloActual() - homero->y();

            if (alturaDelSalto < 50) {
                emit jugadorGolpeado();
                return;
            }
        }
    }

    if (x() < -100) {
        if (scene()) scene()->removeItem(this);
        delete this;
    }
}

void Obstaculo::detener() {
    if (timerMovimiento->isActive()) {
        timerMovimiento->stop();
    }
}

Obstaculo::~Obstaculo() {
}