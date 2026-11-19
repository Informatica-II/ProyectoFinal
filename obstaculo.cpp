#include "Obstaculo.h"
#include <QGraphicsScene>
#include <QBrush>
#include <QPen>

Obstaculo::Obstaculo(int carrilY, int velocidad, PersonajeNivel1* jugador) {
    QPixmap pixmapObstaculo(":/imagenes/Roca.png");
    setPixmap(pixmapObstaculo);

    esParabolico = false;
    marcaImpacto = nullptr;

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

Obstaculo::Obstaculo(int carrilY, float duracionVuelo, PersonajeNivel1* jugador, QGraphicsScene* escena)
    : QObject(), QGraphicsPixmapItem() {

    this->esParabolico = true;
    this->carrilAsignado = carrilY;
    this->homero = jugador;
    this->tiempoVuelo = duracionVuelo;
    this->tiempoActual = 0.0f;
    this->anguloRotacion = 0.0f;
    this->gravedad = 950.0f;

    QPixmap sprite(":/imagenes/Roca.png");
    setPixmap(sprite.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(boundingRect().center());
    setZValue(60);

    x0 = 40.0f;
    y0 = 380.0f;
    float xDestino = 165.0f;
    float yDestino = static_cast<float>(carrilY) + 20.0f;

    vx = (xDestino - x0) / tiempoVuelo;
    vy0 = (yDestino - y0 - 0.5f * gravedad * tiempoVuelo * tiempoVuelo) / tiempoVuelo;
    setPos(x0, y0);

    float centroX = xDestino + boundingRect().width() / 2.0f;
    float baseY = yDestino + boundingRect().height();

    marcaImpacto = new QGraphicsEllipseItem(0, 0, 70, 30);
    marcaImpacto->setPos(centroX - 35.0f, baseY - 15.0f);
    marcaImpacto->setBrush(QBrush(QColor(231, 76, 60, 120)));
    marcaImpacto->setPen(QPen(Qt::red, 2));
    marcaImpacto->setZValue(5);
    if (escena) {
        escena->addItem(marcaImpacto);
    }

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Obstaculo::mover);
    timerMovimiento->start(16);
}

void Obstaculo::mover() { 
    if (esParabolico) {
        tiempoActual += 0.016f;

        float nuevaX = x0 + vx * tiempoActual;
        float nuevaY = y0 + vy0 * tiempoActual + 0.5f * gravedad * tiempoActual * tiempoActual;
        setPos(nuevaX, nuevaY);

        anguloRotacion += 12.0f;
        setRotation(anguloRotacion);

        if (tiempoActual >= tiempoVuelo) {
            timerMovimiento->stop();

            if (homero && static_cast<int>(homero->getSueloActual()) == carrilAsignado) {
                emit jugadorGolpeado();
                return;
            }

            if (marcaImpacto) {
                if (marcaImpacto->scene()) marcaImpacto->scene()->removeItem(marcaImpacto);
                delete marcaImpacto;
                marcaImpacto = nullptr;
            }

            if (scene()) scene()->removeItem(this);
            deleteLater();
        }
        return;
    }

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
        timerMovimiento->stop();
        if (scene()) scene()->removeItem(this);
        deleteLater();
    }
}

void Obstaculo::detener() {
    if (timerMovimiento && timerMovimiento->isActive()) {
        timerMovimiento->stop();
    }
}

Obstaculo::~Obstaculo() {
    if (timerMovimiento) {
        timerMovimiento->stop();
    }
    if (marcaImpacto) {
        if (marcaImpacto->scene()) marcaImpacto->scene()->removeItem(marcaImpacto);
        delete marcaImpacto;
        marcaImpacto = nullptr;
    }
}