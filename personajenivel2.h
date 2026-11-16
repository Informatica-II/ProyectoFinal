#ifndef PERSONAJENIVEL2_H
#define PERSONAJENIVEL2_H

#include "PersonajeBase.h"

class PersonajeNivel2 : public PersonajeBase {
private:
    float velocidadActual;

public:
    PersonajeNivel2();

    void actualizarMovimiento() override;
    void actualizarAnimacion() override;
};

#endif // PERSONAJENIVEL2_H