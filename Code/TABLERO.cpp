#include <iostream>
#include "tablero.h"

using namespace std;


unsigned char** crearTablero(int ancho, int alto)
{
    int bytesPorFila = ancho / 8;

    unsigned char** tablero = new unsigned char*[alto];

    for (int i = 0; i < alto; i++)
    {
        tablero[i] = new unsigned char[bytesPorFila];
    }

    return tablero;
}


void inicializarTablero(unsigned char** tablero, int ancho, int alto)
{
    int bytesPorFila = ancho / 8;

    for (int i = 0; i < alto; i++)
    {
        for (int j = 0; j < bytesPorFila; j++)
        {
            tablero[i][j] = 0;
        }
    }
}
