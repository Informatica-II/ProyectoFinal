#include "Nivel1.h"

Nivel1::Nivel1(QGraphicsScene* escena) : QObject() {
    this->escenaActual = escena;
    jugador = nullptr;
    fondo1 = nullptr;
    fondo2 = nullptr;
}

Nivel1::~Nivel1() {
    delete jugador;
    delete fondo1;
    delete fondo2;
}

void Nivel1::iniciarNivel() {
    const char* rutaFondo = ":/imagenes/FondoNivel1.jpg";

    fondo1 = new Fondo(rutaFondo, 0, 5);
    escenaActual->addItem(fondo1);

    int anchoFondo = fondo1->getAncho();

    fondo2 = new Fondo(rutaFondo, anchoFondo - 1, 5);
    escenaActual->addItem(fondo2);

    jugador = new PersonajeNivel1();
    escenaActual->addItem(jugador);

    jugador->setPos(150, 470);
    jugador->setFocus();
}