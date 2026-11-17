#include "PersonajeNivel1.h"

PersonajeNivel1::PersonajeNivel1() : PersonajeBase() {
    gravedad = 0.8f;
    velocidadY = 0.0f;
    enElSuelo = false;
    limiteSueloY = 540.0f;

    anchoFrame = 100;
    altoFrame = 100;

    posicionesCarriles[0] = 400.0f;
    posicionesCarriles[1] = 470.0f;
    posicionesCarriles[2] = 540.0f;

    carrilActual = 1;
    limiteSueloY = posicionesCarriles[carrilActual];

    spriteCorrer.load(":/imagenes/correr__1_-removebg-preview.png");
    maxFramesCorrer = 16;

    spriteSalto.load(":/imagenes/salto__1_-removebg-preview.png");
    maxFramesSalto = 22;

    frameActual = 0;
    contadorAnimacion = 0;

    setPixmap(spriteCorrer.copy(0, 0, anchoFrame, altoFrame));
}

void PersonajeNivel1::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;

    if (!timerJuego->isActive()) {
        event->ignore();
        return;
    }

    if (event->key() == Qt::Key_Space) {
        if (enElSuelo) {
            velocidadY = -15.0f;
            enElSuelo = false;
            frameActual = 0;
        }
    }
    else if (event->key() == Qt::Key_W) {
        if (carrilActual > 0) {
            carrilActual--;
            limiteSueloY = posicionesCarriles[carrilActual];
        }
    }
    else if (event->key() == Qt::Key_S) {
        if (carrilActual < 2) {
            carrilActual++;
            limiteSueloY = posicionesCarriles[carrilActual];
        }
    }
}

void PersonajeNivel1::actualizarMovimiento() {
    velocidadY += gravedad;

    float nuevaPosY;
    if (!enElSuelo) {
        nuevaPosY = y() + velocidadY;
    } else {
        nuevaPosY = limiteSueloY;
    }

    if (nuevaPosY >= limiteSueloY) {
        if (!enElSuelo) frameActual = 0;
        nuevaPosY = limiteSueloY;
        velocidadY = 0.0f;
        enElSuelo = true;
    } else {
        enElSuelo = false;
    }

    setZValue(10 + carrilActual);

    setPos(x(), nuevaPosY);
}

void PersonajeNivel1::actualizarAnimacion() {
    contadorAnimacion++;

    if (enElSuelo) {
        if (contadorAnimacion >= 2) {
            contadorAnimacion = 0;
            frameActual++;
            if (frameActual >= maxFramesCorrer) frameActual = 0;

            setPixmap(spriteCorrer.copy(frameActual * anchoFrame, 0, anchoFrame, altoFrame));
        }
    } else {
        if (contadorAnimacion >= 2) {
            contadorAnimacion = 0;
            frameActual++;
            if (frameActual >= maxFramesSalto) frameActual = maxFramesSalto - 1;

            setPixmap(spriteSalto.copy(frameActual * anchoFrame, 0, anchoFrame, altoFrame));
        }
    }
}

void PersonajeNivel1::resetearPosicion() {
    carrilActual = 1;
    limiteSueloY = posicionesCarriles[carrilActual];

    setPos(150, limiteSueloY);
}