#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Tablero.h"
#include "Combinaciones.h"

using namespace std;

int main()
{
    int ancho = 6;
    int alto = 6;

    srand(time(0));

    unsigned char* tablero = crearTablero(ancho, alto);

    inicializarTablero(tablero, ancho, alto);

    llenarTablero(tablero, ancho, alto);

    // Creamos una combinacion cruzada
    modificarFicha(tablero, ancho, 0, 2, 4);
    modificarFicha(tablero, ancho, 1, 2, 4);

    modificarFicha(tablero, ancho, 2, 0, 4);
    modificarFicha(tablero, ancho, 2, 1, 4);
    modificarFicha(tablero, ancho, 2, 2, 4);
    modificarFicha(tablero, ancho, 2, 3, 4);
    modificarFicha(tablero, ancho, 2, 4, 4);

    unsigned char* eliminadas = crearMarcador(ancho, alto);

    inicializarMarcador(eliminadas, ancho, alto);

    detectarCombinaciones(tablero, eliminadas, ancho, alto);

    cout << "Tablero:" << endl;

    mostrarTablero(tablero, ancho, alto);

    cout << endl;

    cout << "Marcador:" << endl;

    for (int fila = 0; fila < alto; fila++)
    {
        for (int columna = 0; columna < ancho; columna++)
        {
            cout << (int)eliminadas[fila * ancho + columna] << " ";
        }

        cout << endl;
    }

    liberarMarcador(eliminadas);

    liberarTablero(tablero);

    return 0;
}
