#include "Fondo.h"

Fondo::Fondo(const char* rutaImagen, int posX, int velocidad) {
    QPixmap pixMap(rutaImagen);
    setPixmap(pixMap);

    this->velocidadX = velocidad;
    this->anchoImagen = pixMap.width();

    setPos(posX, 0);
    setZValue(-1);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Fondo::actualizarMovimiento);
    timerMovimiento->start(16);
}

void Fondo::detener() {
    if (timerMovimiento->isActive()) {
        timerMovimiento->stop();
    }
}

void Fondo::reanudar() {
    if (!timerMovimiento->isActive()) {
        timerMovimiento->start(16);
    }
}

void Fondo::actualizarMovimiento() {
    setPos(x() - velocidadX, y());

    if (x() <= -anchoImagen) {
        setPos(x() + (anchoImagen * 2), y());
    }
}