//En este archivo se implementaran las funciones encargadas
//de detectar las combinaciones horizontales y verticales.

//Tambien se implementara el manejo del marcador auxiliar
//Para identificar las fichas que forman combinaciones.

#include "Combinaciones.h"
#include "Tablero.h"

unsigned char* crearMarcador(int ancho, int alto)
{
    unsigned char* eliminadas =
        new unsigned char[ancho * alto];

    return eliminadas;
}

void inicializarMarcador(unsigned char* eliminadas,
                         int ancho,
                         int alto)
{
    int cantidad =
        ancho * alto;

    for (int i = 0;
         i < cantidad;
         i++)
    {
        eliminadas[i] = 0;
    }
}

int detectarCombinaciones(unsigned char* tablero,
                          unsigned char* eliminadas,
                          int ancho,
                          int alto)
{
    int cantidadCombinaciones = 0;

    // COMBINACIONES HORIZONTALES
    for (int fila = 0;
         fila < alto;
         fila++)
    {
        for (int columna = 0;
             columna < ancho - 2;
             columna++)
        {
            int ficha =
                obtenerFicha(tablero,
                             ancho,
                             fila,
                             columna);

            if (ficha != 0 &&
                ficha ==
                    obtenerFicha(tablero,
                                 ancho,
                                 fila,
                                 columna + 1) &&
                ficha ==
                    obtenerFicha(tablero,
                                 ancho,
                                 fila,
                                 columna + 2))
            {
                eliminadas[
                    fila * ancho + columna] = 1;

                eliminadas[
                    fila * ancho + columna + 1] = 1;

                eliminadas[
                    fila * ancho + columna + 2] = 1;

                cantidadCombinaciones++;
            }
        }
    }

    // COMBINACIONES VERTICALES
    for (int fila = 0;
         fila < alto - 2;
         fila++)
    {
        for (int columna = 0;
             columna < ancho;
             columna++)
        {
            int ficha =
                obtenerFicha(tablero,
                             ancho,
                             fila,
                             columna);

            if (ficha != 0 &&
                ficha ==
                    obtenerFicha(tablero,
                                 ancho,
                                 fila + 1,
                                 columna) &&
                ficha ==
                    obtenerFicha(tablero,
                                 ancho,
                                 fila + 2,
                                 columna))
            {
                eliminadas[
                    fila * ancho + columna] = 1;

                eliminadas[
                    (fila + 1) * ancho + columna] = 1;

                eliminadas[
                    (fila + 2) * ancho + columna] = 1;

                cantidadCombinaciones++;
            }
        }
    }

    return cantidadCombinaciones;
}

// Sistema de puntuacion:
// 10 puntos por cada eliminacion realizada por el usuario.
// 10 puntos por cada ficha eliminada por combinaciones.
// 20 puntos por cada combinacion detectada.
// 30 puntos por cada cascada procesada.


int eliminarCombinaciones(unsigned char* tablero,
                          unsigned char* eliminadas,
                          int ancho,
                          int alto)
{
    int cantidadEliminadas = 0;

    for (int fila = 0;
         fila < alto;
         fila++)
    {
        for (int columna = 0;
             columna < ancho;
             columna++)
        {
            int posicion =
                fila * ancho + columna;

            if (eliminadas[posicion] == 1)
            {
                modificarFicha(tablero,
                               ancho,
                               fila,
                               columna,
                               0);

                cantidadEliminadas++;
            }
        }
    }

    return cantidadEliminadas;
}

int procesarCascadas(unsigned char* tablero,
                     unsigned char* eliminadas,
                     int ancho,
                     int alto,
                     int* fichasEliminadas,
                     int* combinaciones)
{
    int hayCombinacion = 1;

    int cantidadCascadas = 0;

    *fichasEliminadas = 0;
    *combinaciones = 0;

    while (hayCombinacion == 1)
    {
        inicializarMarcador(eliminadas,
                            ancho,
                            alto);

        int cantidadCombinaciones =
            detectarCombinaciones(tablero,
                                  eliminadas,
                                  ancho,
                                  alto);

        if (cantidadCombinaciones > 0)
        {
            hayCombinacion = 1;

            cantidadCascadas++;

            *combinaciones +=
                cantidadCombinaciones;

            int cantidadEliminadas =
                eliminarCombinaciones(tablero,
                                      eliminadas,
                                      ancho,
                                      alto);

            *fichasEliminadas +=
                cantidadEliminadas;

            aplicarGravedad(tablero,
                            ancho,
                            alto);

            rellenarTablero(tablero,
                            ancho,
                            alto);
        }
        else
        {
            hayCombinacion = 0;
        }
    }

    return cantidadCascadas;
}

void liberarMarcador(unsigned char* eliminadas)
{
    delete[] eliminadas;
}
