#ifndef FONDO_H
#define FONDO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPixmap>

class Fondo : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
private:
    int velocidadX;
    int anchoImagen;
    QTimer* timerMovimiento;

public:
    Fondo(const char* rutaImagen, int posX, int velocidad);
    void detener();
    void reanudar();
    int getAncho() const { return anchoImagen; }

public slots:
    void actualizarMovimiento();
};

#endif // FONDO_H