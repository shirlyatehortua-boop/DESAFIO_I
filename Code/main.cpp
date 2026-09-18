#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tablero.h"

using namespace std;

int main()
{
    int ancho = 6;
    int alto = 6;

    srand(time(0));

    unsigned char* tablero = crearTablero(ancho, alto);

    inicializarTablero(tablero, ancho, alto);

    llenarTablero(tablero, ancho, alto);

    mostrarTablero(tablero, ancho, alto);

    liberarTablero(tablero);

    return 0;
}
    //11:33 de la noche, estudiando la siguiente parte
