#include "PersonajeBase.h"

PersonajeBase::PersonajeBase() {
    setFlag(QGraphicsItem::ItemIsFocusable);

    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &PersonajeBase::tickPrincipal);
    timerJuego->start(16);
}

void PersonajeBase::tickPrincipal() {
    actualizarMovimiento();
    actualizarAnimacion();
}

PersonajeBase::~PersonajeBase() {}
