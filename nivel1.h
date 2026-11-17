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

private slots:
    void generarObstaculo();
    void ejecutarGameOver();
    void reiniciarNivel();

public:
    Nivel1(QGraphicsScene* escena);
    ~Nivel1();

    void iniciarNivel();
};

#endif // NIVEL1_H