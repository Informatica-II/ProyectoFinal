#ifndef NIVEL1_H
#define NIVEL1_H

#include <QObject>
#include <QGraphicsScene>
#include "PersonajeNivel1.h"
#include "Fondo.h"
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class Nivel1 : public QObject {
    Q_OBJECT
private:
    QGraphicsScene* escenaActual;
    PersonajeNivel1* jugador;
    Fondo* fondo1;
    Fondo* fondo2;
    QTimer* timerGeneradorObstaculos;
    bool juegoActivo;
    QGraphicsTextItem* textoGameOver;
    QPushButton* botonReinicio;
    QGraphicsProxyWidget* proxyBotonReinicio;
    QGraphicsRectItem* barraFondo;
    QGraphicsRectItem* barraProgreso;
    QTimer* timerProgreso;
    int tiempoTranscurrido;
    int tiempoMeta;
    float anchoMaximoBarra;
    QGraphicsTextItem* textoVictoria;

    int dificultadActual;
    int intervaloSpawn;
    int velocidadObstaculos;
    int velocidadFondo;

    QGraphicsPixmapItem* fondoMenu;
    QGraphicsTextItem* textoDificultad;
    QGraphicsProxyWidget* proxyFacil;
    QGraphicsProxyWidget* proxyNormal;
    QGraphicsProxyWidget* proxyDificil;
    void configurarDificultad(int dif);

    QGraphicsPixmapItem* avalancha;
    QTimer* timerAtaqueAvalancha;
    int intervaloAtaqueAvalancha;
    float tiempoVueloEscombro;

private slots:
    void generarObstaculo();
    void lanzarEscombro();
    void ejecutarGameOver();
    void reiniciarNivel();
    void actualizarProgreso();
    void ejecutarVictoria();
    void comenzarPartida(int dif);

public:
    Nivel1(QGraphicsScene* escena);
    ~Nivel1();

    void iniciarNivel();
};

#endif // NIVEL1_H