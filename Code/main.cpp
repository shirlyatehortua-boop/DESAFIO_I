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

    cout << "Tablero creado correctamente." << endl;

    liberarTablero(tablero);

    cout << "Memoria liberada correctamente." << endl;

    return 0;
}
