#ifndef NIVEL1_H
#define NIVEL1_H

#include <QObject>
#include <QGraphicsScene>
#include "PersonajeNivel1.h"
#include "Fondo.h"

class Nivel1 : public QObject {
    Q_OBJECT
private:
    QGraphicsScene* escenaActual;
    PersonajeNivel1* jugador;
    Fondo* fondo1;
    Fondo* fondo2;

public:
    Nivel1(QGraphicsScene* escena);
    ~Nivel1();

    void iniciarNivel();
};

#endif // NIVEL1_H