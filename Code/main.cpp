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

    // Crear tablero
    unsigned char* tablero = crearTablero(ancho, alto);

    // Inicializar tablero
    inicializarTablero(tablero, ancho, alto);

    // Llenar tablero con fichas aleatorias
    llenarTablero(tablero, ancho, alto);

    // Crear marcador
    unsigned char* eliminadas = crearMarcador(ancho, alto);

    // -------------------------------------------------
    // PRUEBA CONTROLADA DE COMBINACIONES
    // -------------------------------------------------

    // Combinacion vertical de fichas 4
    modificarFicha(tablero, ancho, 0, 2, 4);
    modificarFicha(tablero, ancho, 1, 2, 4);
    modificarFicha(tablero, ancho, 2, 2, 4);

    // Combinacion horizontal de fichas 4
    modificarFicha(tablero, ancho, 2, 0, 4);
    modificarFicha(tablero, ancho, 2, 1, 4);
    modificarFicha(tablero, ancho, 2, 2, 4);
    modificarFicha(tablero, ancho, 2, 3, 4);
    modificarFicha(tablero, ancho, 2, 4, 4);

    cout << "Tablero inicial:" << endl;
    mostrarTablero(tablero, ancho, alto);

    // -------------------------------------------------
    // PRUEBA DE CASCADAS
    // -------------------------------------------------

    inicializarMarcador(eliminadas, ancho, alto);

    int cantidadCascadas = procesarCascadas(tablero,
                                            eliminadas,
                                            ancho,
                                            alto);

    cout << endl;
    cout << "Cantidad de cascadas: "
         << cantidadCascadas << endl;

    cout << endl;
    cout << "Tablero despues de las cascadas:" << endl;
    mostrarTablero(tablero, ancho, alto);

    // -------------------------------------------------
    // LIBERAR MEMORIA
    // -------------------------------------------------

    liberarMarcador(eliminadas);
    liberarTablero(tablero);

    return 0;
}
