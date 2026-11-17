#include "Nivel1.h"
#include <QRandomGenerator>
#include "Obstaculo.h"
#include <QFont>

Nivel1::Nivel1(QGraphicsScene* escena) : QObject() {
    this->escenaActual = escena;
    juegoActivo = true;
    jugador = nullptr;
    fondo1 = nullptr;
    fondo2 = nullptr;
}

void Nivel1::iniciarNivel() {
    const char* rutaFondo = ":/imagenes/FondoNivel1.jpg";

    fondo1 = new Fondo(rutaFondo, 0, 5);
    escenaActual->addItem(fondo1);

    int anchoFondo = fondo1->getAncho();

    fondo2 = new Fondo(rutaFondo, anchoFondo, 5);
    escenaActual->addItem(fondo2);

    jugador = new PersonajeNivel1();
    escenaActual->addItem(jugador);

    jugador->setPos(150, 470);
    jugador->setFocus();

    timerGeneradorObstaculos = new QTimer(this);
    connect(timerGeneradorObstaculos, &QTimer::timeout, this, &Nivel1::generarObstaculo);

    timerGeneradorObstaculos->start(2000);
}

void Nivel1::generarObstaculo() {
    int carrilAleatorio = QRandomGenerator::global()->bounded(3);
    int coordY = 0;

    if (carrilAleatorio == 0) coordY = 400;
    else if (carrilAleatorio == 1) coordY = 470;
    else if (carrilAleatorio == 2) coordY = 540;

    Obstaculo* nuevoObstaculo = new Obstaculo(coordY, 7, jugador);

    connect(nuevoObstaculo, &Obstaculo::jugadorGolpeado, this, &Nivel1::ejecutarGameOver);

    escenaActual->addItem(nuevoObstaculo);
}

void Nivel1::ejecutarGameOver() {
    if (!juegoActivo) return;
    juegoActivo = false;

    timerGeneradorObstaculos->stop();

    jugador->morir();
    fondo1->detener();
    fondo2->detener();

    for (QGraphicsItem* item : escenaActual->items()) {
        Obstaculo* rocaEnPantalla = dynamic_cast<Obstaculo*>(item);
        if (rocaEnPantalla) {
            rocaEnPantalla->detener();
        }
    }

    textoGameOver = new QGraphicsTextItem("GAME OVER");
    textoGameOver->setFont(QFont("Arial", 40, QFont::Bold));
    textoGameOver->setDefaultTextColor(Qt::red);
    textoGameOver->setPos(500, 250);
    textoGameOver->setZValue(100);
    escenaActual->addItem(textoGameOver);

    botonReinicio = new QPushButton("Reiniciar Nivel");

    botonReinicio->setFixedSize(200, 50);
    botonReinicio->setStyleSheet(
        "QPushButton {"
        "  background-color: #ff4c4c; color: white;"
        "  font-size: 20px; font-weight: bold;"
        "  border-radius: 10px; border: 2px solid #990000;"
        "}"
        "QPushButton:hover { background-color: #ff1c1c; }"
        );

    connect(botonReinicio, &QPushButton::clicked, this, &Nivel1::reiniciarNivel);

    proxyBotonReinicio = escenaActual->addWidget(botonReinicio);

    proxyBotonReinicio->setPos(588, 350);
    proxyBotonReinicio->setZValue(101);
}

void Nivel1::reiniciarNivel() {
    if (textoGameOver) {
        escenaActual->removeItem(textoGameOver);
        delete textoGameOver;
        textoGameOver = nullptr;
    }

    if (proxyBotonReinicio) {
        escenaActual->removeItem(proxyBotonReinicio);
        delete proxyBotonReinicio;
        proxyBotonReinicio = nullptr;
    }

    QList<QGraphicsItem*> elementos = escenaActual->items();
    for (QGraphicsItem* item : elementos) {
        Obstaculo* roca = dynamic_cast<Obstaculo*>(item);
        if (roca) {
            escenaActual->removeItem(roca);
            delete roca;
        }
    }

    fondo1->setPos(0, 5);
    fondo2->setPos(1376, 5);

    jugador->resetearPosicion();

    fondo1->reanudar();
    fondo2->reanudar();
    jugador->revivir();
    timerGeneradorObstaculos->start(2000);

    juegoActivo = true;

    if (jugador) {
        jugador->setFocus();
    }
}

Nivel1::~Nivel1() {
    delete jugador;
    delete fondo1;
    delete fondo2;
}