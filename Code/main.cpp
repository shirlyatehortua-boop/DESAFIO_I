#include <iostream>
#include "Tablero.h"

using namespace std;

int main()
{
    int ancho;
    int alto;

    cout << "Ingrese el ancho del tablero: ";
    cin >> ancho;

    cout << "Ingrese el alto del tablero: ";
    cin >> alto;

    unsigned char* tablero = crearTablero(ancho, alto);

    inicializarTablero(tablero, ancho, alto);

    cout << "Tablero creado e inicializado correctamente." << endl;

    liberarTablero(tablero);

    return 0;
}
