#include "Nivel1.h"
#include <QRandomGenerator>
#include "Obstaculo.h"
#include <QFont>

Nivel1::Nivel1(QGraphicsScene* escena) : QObject() {
    this->escenaActual = escena;
    juegoActivo = false;

    jugador = nullptr;
    fondo1 = nullptr;
    fondo2 = nullptr;
    timerGeneradorObstaculos = nullptr;
    textoGameOver = nullptr;
    botonReinicio = nullptr;
    proxyBotonReinicio = nullptr;
    barraFondo = nullptr;
    barraProgreso = nullptr;
    timerProgreso = nullptr;
    textoVictoria = nullptr;

    fondoMenu = nullptr;
    textoDificultad = nullptr;
    proxyFacil = nullptr;
    proxyNormal = nullptr;
    proxyDificil = nullptr;

    avalancha = nullptr;
    timerAtaqueAvalancha = nullptr;
}

void Nivel1::configurarDificultad(int dif) {
    dificultadActual = dif;

    switch (dif) {
    case 1:
        intervaloSpawn = 2400;
        velocidadObstaculos = 5;
        velocidadFondo = 4;
        tiempoMeta = 25000;
        intervaloAtaqueAvalancha = 4000;
        tiempoVueloEscombro = 1.5f;
        break;
    case 3:
        intervaloSpawn = 1200;
        velocidadObstaculos = 10;
        velocidadFondo = 7;
        tiempoMeta = 45000;
        intervaloAtaqueAvalancha = 2000;
        tiempoVueloEscombro = 0.95f;
        break;
    default:
        intervaloSpawn = 1800;
        velocidadObstaculos = 7;
        velocidadFondo = 5;
        tiempoMeta = 35000;
        intervaloAtaqueAvalancha = 3000;
        tiempoVueloEscombro = 1.2f;
        break;
    }
}

void Nivel1::iniciarNivel() {
    fondoMenu = new QGraphicsPixmapItem(QPixmap(":/imagenes/FondoNivel1.jpg"));
    fondoMenu->setZValue(0);
    escenaActual->addItem(fondoMenu);

    textoDificultad = new QGraphicsTextItem("SELECCIONA LA DIFICULTAD");
    textoDificultad->setFont(QFont("Arial", 36, QFont::Bold));
    textoDificultad->setDefaultTextColor(Qt::white);
    textoDificultad->setPos(355, 200);
    textoDificultad->setZValue(2);
    escenaActual->addItem(textoDificultad);

    QPushButton* btnFacil = new QPushButton("Fácil");
    QPushButton* btnNormal = new QPushButton("Normal");
    QPushButton* btnDificil = new QPushButton("Difícil");

    btnFacil->setFixedSize(180, 60);
    btnNormal->setFixedSize(180, 60);
    btnDificil->setFixedSize(180, 60);

    btnFacil->setStyleSheet(
        "QPushButton { background-color: #2ecc71; color: white; font-size: 22px; font-weight: bold; border-radius: 10px; }"
        "QPushButton:hover { background-color: #27ae60; }"
        );
    btnNormal->setStyleSheet(
        "QPushButton { background-color: #f39c12; color: white; font-size: 22px; font-weight: bold; border-radius: 10px; }"
        "QPushButton:hover { background-color: #d68910; }"
        );
    btnDificil->setStyleSheet(
        "QPushButton { background-color: #e74c3c; color: white; font-size: 22px; font-weight: bold; border-radius: 10px; }"
        "QPushButton:hover { background-color: #c0392b; }"
        );

    connect(btnFacil,   &QPushButton::clicked, this, [this]() { comenzarPartida(1); });
    connect(btnNormal,  &QPushButton::clicked, this, [this]() { comenzarPartida(2); });
    connect(btnDificil, &QPushButton::clicked, this, [this]() { comenzarPartida(3); });

    proxyFacil   = escenaActual->addWidget(btnFacil);
    proxyNormal  = escenaActual->addWidget(btnNormal);
    proxyDificil = escenaActual->addWidget(btnDificil);

    proxyFacil->setPos(378, 330);
    proxyNormal->setPos(598, 330);
    proxyDificil->setPos(818, 330);

    proxyFacil->setZValue(3);
    proxyNormal->setZValue(3);
    proxyDificil->setZValue(3);
}

void Nivel1::comenzarPartida(int dif) {
    if (jugador != nullptr) return;

    if (fondoMenu)      { escenaActual->removeItem(fondoMenu);      delete fondoMenu;      fondoMenu = nullptr; }
    if (textoDificultad){ escenaActual->removeItem(textoDificultad);delete textoDificultad;textoDificultad = nullptr; }

    if (proxyFacil)     { escenaActual->removeItem(proxyFacil);     proxyFacil->deleteLater();   proxyFacil = nullptr; }
    if (proxyNormal)    { escenaActual->removeItem(proxyNormal);    proxyNormal->deleteLater();  proxyNormal = nullptr; }
    if (proxyDificil)   { escenaActual->removeItem(proxyDificil);   proxyDificil->deleteLater(); proxyDificil = nullptr; }

    configurarDificultad(dif);
    juegoActivo = true;

    const char* rutaFondo = ":/imagenes/FondoNivel1.jpg";
    fondo1 = new Fondo(rutaFondo, 0, velocidadFondo);
    escenaActual->addItem(fondo1);

    int anchoFondo = fondo1->getAncho();
    fondo2 = new Fondo(rutaFondo, anchoFondo, velocidadFondo);
    escenaActual->addItem(fondo2);

    jugador = new PersonajeNivel1();
    escenaActual->addItem(jugador);
    jugador->setPos(150, 470);
    jugador->setFocus();

    anchoMaximoBarra = 400.0f;
    tiempoTranscurrido = 0;

    barraFondo = new QGraphicsRectItem(0, 0, anchoMaximoBarra, 25);
    barraFondo->setPos(488, 25);
    barraFondo->setBrush(QBrush(QColor(40, 40, 40, 200)));
    barraFondo->setPen(QPen(Qt::white, 2));
    barraFondo->setZValue(99);
    escenaActual->addItem(barraFondo);

    barraProgreso = new QGraphicsRectItem(0, 0, 0, 25);
    barraProgreso->setPos(488, 25);
    barraProgreso->setBrush(QBrush(QColor(46, 204, 113)));
    barraProgreso->setPen(Qt::NoPen);
    barraProgreso->setZValue(100);
    escenaActual->addItem(barraProgreso);

    QPixmap spriteAvalancha(":/imagenes/avalancha.png");
    avalancha = new QGraphicsPixmapItem(
        spriteAvalancha.scaled(160, 440, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)
        );
    avalancha->setPos(-25, 250);
    avalancha->setZValue(50);
    escenaActual->addItem(avalancha);

    timerAtaqueAvalancha = new QTimer(this);
    connect(timerAtaqueAvalancha, &QTimer::timeout, this, &Nivel1::lanzarEscombro);
    timerAtaqueAvalancha->start(intervaloAtaqueAvalancha);

    timerProgreso = new QTimer(this);
    connect(timerProgreso, &QTimer::timeout, this, &Nivel1::actualizarProgreso);
    timerProgreso->start(50);

    timerGeneradorObstaculos = new QTimer(this);
    connect(timerGeneradorObstaculos, &QTimer::timeout, this, &Nivel1::generarObstaculo);
    timerGeneradorObstaculos->start(intervaloSpawn);
}

void Nivel1::generarObstaculo() {
    if (!juegoActivo) return;

    int carrilAleatorio = QRandomGenerator::global()->bounded(3);
    int coordY = 0;

    if (carrilAleatorio == 0) coordY = 400;
    else if (carrilAleatorio == 1) coordY = 470;
    else if (carrilAleatorio == 2) coordY = 540;

    Obstaculo* nuevoObstaculo = new Obstaculo(coordY, velocidadObstaculos, jugador);

    connect(nuevoObstaculo, &Obstaculo::jugadorGolpeado, this, &Nivel1::ejecutarGameOver);

    escenaActual->addItem(nuevoObstaculo);
}

void Nivel1::lanzarEscombro() {
    if (!juegoActivo) return;

    int carrilAleatorio = QRandomGenerator::global()->bounded(3);
    int coordY = 470;
    if (carrilAleatorio == 0) coordY = 400;
    else if (carrilAleatorio == 2) coordY = 540;

    Obstaculo* escombro = new Obstaculo(coordY, tiempoVueloEscombro, jugador, escenaActual);
    connect(escombro, &Obstaculo::jugadorGolpeado, this, &Nivel1::ejecutarGameOver);
    escenaActual->addItem(escombro);
}

void Nivel1::actualizarProgreso() {
    if (!juegoActivo) return;

    tiempoTranscurrido += 50;

    float porcentaje = static_cast<float>(tiempoTranscurrido) / tiempoMeta;
    if (porcentaje > 1.0f) porcentaje = 1.0f;

    barraProgreso->setRect(0, 0, anchoMaximoBarra * porcentaje, 25);

    if (tiempoTranscurrido >= tiempoMeta) {
        ejecutarVictoria();
    }
}

void Nivel1::ejecutarVictoria() {
    if (!juegoActivo) return;
    juegoActivo = false;

    timerProgreso->stop();
    timerGeneradorObstaculos->stop();
    if (timerAtaqueAvalancha) timerAtaqueAvalancha->stop();

    jugador->morir();
    fondo1->detener();
    fondo2->detener();

    for (QGraphicsItem* item : escenaActual->items()) {
        Obstaculo* roca = dynamic_cast<Obstaculo*>(item);
        if (roca) {
            roca->detener();
        }
    }

    textoVictoria = new QGraphicsTextItem("¡NIVEL COMPLETADO!");
    textoVictoria->setFont(QFont("Arial", 45, QFont::Bold));
    textoVictoria->setDefaultTextColor(QColor(46, 204, 113));
    textoVictoria->setPos(390, 250);
    textoVictoria->setZValue(101);
    escenaActual->addItem(textoVictoria);
}

void Nivel1::ejecutarGameOver() {
    if (!juegoActivo) return;
    juegoActivo = false;

    timerGeneradorObstaculos->stop();
    if (timerProgreso) timerProgreso->stop();
    if (timerAtaqueAvalancha) timerAtaqueAvalancha->stop();

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
        proxyBotonReinicio->deleteLater();
        proxyBotonReinicio = nullptr;
        botonReinicio = nullptr;
    }

    QList<Obstaculo*> rocasParaBorrar;
    for (QGraphicsItem* item : escenaActual->items()) {
        if (Obstaculo* roca = dynamic_cast<Obstaculo*>(item)) {
            rocasParaBorrar.append(roca);
        }
    }
    for (Obstaculo* roca : rocasParaBorrar) {
        escenaActual->removeItem(roca);
        delete roca;
    }

    fondo1->setPos(0, 0);
    fondo2->setPos(fondo1->getAncho(), 0);

    jugador->resetearPosicion();

    fondo1->reanudar();
    fondo2->reanudar();
    jugador->revivir();
    timerGeneradorObstaculos->start(intervaloSpawn);

    juegoActivo = true;

    if (jugador) {
        jugador->setFocus();
    }

    if (textoVictoria) {
        escenaActual->removeItem(textoVictoria);
        delete textoVictoria;
        textoVictoria = nullptr;
    }

    tiempoTranscurrido = 0;
    if (barraProgreso) {
        barraProgreso->setRect(0, 0, 0, 25);
    }
    if (timerProgreso) {
        timerProgreso->start(50);
    }
    if (timerAtaqueAvalancha){
        timerAtaqueAvalancha->start(intervaloAtaqueAvalancha);
    }
}

Nivel1::~Nivel1() {
    if (timerGeneradorObstaculos) timerGeneradorObstaculos->stop();
    if (timerProgreso) timerProgreso->stop();
    if (timerAtaqueAvalancha) timerAtaqueAvalancha->stop();

    if (escenaActual) {
        QList<Obstaculo*> rocasParaBorrar;
        for (QGraphicsItem* item : escenaActual->items()) {
            if (Obstaculo* roca = dynamic_cast<Obstaculo*>(item)) {
                rocasParaBorrar.append(roca);
            }
        }
        for (Obstaculo* roca : rocasParaBorrar) {
            escenaActual->removeItem(roca);
            delete roca;
        }
    }

    delete jugador;
    delete avalancha;
    delete fondo1;
    delete fondo2;
    delete barraFondo;
    delete barraProgreso;

    delete fondoMenu;
    delete textoDificultad;
    delete textoGameOver;
    delete textoVictoria;

    delete proxyFacil;
    delete proxyNormal;
    delete proxyDificil;
    delete proxyBotonReinicio;
}