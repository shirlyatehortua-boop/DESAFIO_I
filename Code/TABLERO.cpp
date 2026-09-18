//Ya de este tenia la logica lista para crear, por eso monto todo seguido
//Desde esta parte sigo trabajando y estudiando la logica con la que se arma el juego
//Hasta aquí todo esta funcionando bien


#include "Tablero.h"

unsigned char* crearTablero(int ancho, int alto)
{
    int cantidadBits = ancho * alto * 3;

    int cantidadBytes = (cantidadBits + 7) / 8;

    unsigned char* tablero = new unsigned char[cantidadBytes];

    return tablero;
}

void liberarTablero(unsigned char* tablero)
{
    delete[] tablero;
}
