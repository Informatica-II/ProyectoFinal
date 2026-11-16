#ifndef PERSONAJEBASE_H
#define PERSONAJEBASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>

class PersonajeBase : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    PersonajeBase();
    virtual ~PersonajeBase();

    virtual void actualizarMovimiento() = 0;
    virtual void actualizarAnimacion() = 0;

public slots:
    void tickPrincipal();

protected:
    QTimer* timerJuego;
};

#endif // PERSONAJEBASE_H