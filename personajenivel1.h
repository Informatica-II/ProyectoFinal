#ifndef PERSONAJENIVEL1_H
#define PERSONAJENIVEL1_H

#include "PersonajeBase.h"
#include <QPixmap>

class PersonajeNivel1 : public PersonajeBase {
private:
    float velocidadY;
    float gravedad;
    bool enElSuelo;
    float limiteSueloY;

    int carrilActual;
    float posicionesCarriles[3];

    QPixmap spriteCorrer;
    QPixmap spriteSalto;

    int maxFramesCorrer;
    int maxFramesSalto;
    int anchoFrame;
    int altoFrame;
    int frameActual;
    int contadorAnimacion;

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    PersonajeNivel1();

    void actualizarMovimiento() override;
    void actualizarAnimacion() override;
    float getSueloActual() const { return limiteSueloY; }
    void resetearPosicion();
};

#endif // PERSONAJENIVEL1_H