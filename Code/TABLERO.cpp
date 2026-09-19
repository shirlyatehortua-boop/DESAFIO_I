//Ya de este tenia la logica lista para crear, por eso monto todo seguido
//Desde esta parte sigo trabajando y estudiando la logica con la que se arma el juego
//Hasta aquí todo esta funcionando bien


#include "Tablero.h"
#include <cstdlib>
#include <iostream>

unsigned char* crearTablero(int ancho, int alto)
{
    int cantidadBits = ancho * alto * 3;

    int cantidadBytes = (cantidadBits + 7) / 8;

    unsigned char* tablero = new unsigned char[cantidadBytes];

    return tablero;
}

void inicializarTablero(unsigned char* tablero, int ancho, int alto)
{
    int cantidadBits = ancho * alto * 3;

    int cantidadBytes = (cantidadBits + 7) / 8;

    for (int i = 0; i < cantidadBytes; i++)
    {
        tablero[i] = 0;
    }
}

int generarFicha()
{
    return rand() % 6 + 1;
}

void llenarTablero(unsigned char* tablero, int ancho, int alto)
{
    for (int fila = 0; fila < alto; fila++)
    {
        for (int columna = 0; columna < ancho; columna++)
        {
            int ficha = generarFicha();

            modificarFicha(tablero, ancho, fila, columna, ficha);
        }
    }
}

int obtenerFicha(unsigned char* tablero, int ancho, int fila, int columna)
{
    int indice = fila * ancho + columna;

    int bitInicial = indice * 3;

    int byte = bitInicial / 8;

    int desplazamiento = bitInicial % 8;

    int valor = 0;

    if (desplazamiento <= 5)
    {
        valor = (tablero[byte] >> desplazamiento) & 7;
    }
    else
    {
        int bitsPrimerByte = 8 - desplazamiento;

        int bitsSegundoByte = 3 - bitsPrimerByte;

        int parte1 = tablero[byte] >> desplazamiento;

        int parte2 = tablero[byte + 1] & ((1 << bitsSegundoByte) - 1);

        valor = parte1 | (parte2 << bitsPrimerByte);
    }

    return valor;
}

void modificarFicha(unsigned char* tablero,
                    int ancho,
                    int fila,
                    int columna,
                    int ficha)
{
    int indice = fila * ancho + columna;

    int bitInicial = indice * 3;

    int byte = bitInicial / 8;

    int desplazamiento = bitInicial % 8;

    if (desplazamiento <= 5)
    {
        unsigned char mascara = 7 << desplazamiento;

        tablero[byte] = tablero[byte] & ~mascara;

        tablero[byte] =
            tablero[byte] | ((ficha & 7) << desplazamiento);
    }
    else
    {
        int bitsPrimerByte = 8 - desplazamiento;

        int bitsSegundoByte = 3 - bitsPrimerByte;

        unsigned char mascaraPrimerByte =
            ((1 << bitsPrimerByte) - 1) << desplazamiento;

        tablero[byte] =
            tablero[byte] & ~mascaraPrimerByte;

        tablero[byte] =
            tablero[byte] |
            ((ficha & ((1 << bitsPrimerByte) - 1)) << desplazamiento);

        unsigned char mascaraSegundoByte =
            (1 << bitsSegundoByte) - 1;

        tablero[byte + 1] =
            tablero[byte + 1] & ~mascaraSegundoByte;

        tablero[byte + 1] =
            tablero[byte + 1] |
            ((ficha >> bitsPrimerByte) & mascaraSegundoByte);
    }
}

void mostrarTablero(unsigned char* tablero, int ancho, int alto)
{
    for (int fila = 0; fila < alto; fila++)
    {
        for (int columna = 0; columna < ancho; columna++)
        {
            std::cout << obtenerFicha(tablero, ancho, fila, columna) << " ";
        }

        std::cout << std::endl;
    }
}

void aplicarGravedad(unsigned char* tablero, int ancho, int alto)
{
    for (int columna = 0; columna < ancho; columna++)
    {
        int posicionLibre = alto - 1;

        for (int fila = alto - 1; fila >= 0; fila--)
        {
            int ficha = obtenerFicha(tablero, ancho, fila, columna);

            if (ficha != 0)
            {
                modificarFicha(tablero,
                               ancho,
                               posicionLibre,
                               columna,
                               ficha);

                if (posicionLibre != fila)
                {
                    modificarFicha(tablero,
                                   ancho,
                                   fila,
                                   columna,
                                   0);
                }

                posicionLibre--;
            }
        }
    }
}

void rellenarTablero(unsigned char* tablero, int ancho, int alto)
{
    for (int fila = 0; fila < alto; fila++)
    {
        for (int columna = 0; columna < ancho; columna++)
        {
            int ficha = obtenerFicha(tablero, ancho, fila, columna);

            if (ficha == 0)
            {
                modificarFicha(tablero,
                               ancho,
                               fila,
                               columna,
                               generarFicha());
            }
        }
    }
}

void liberarTablero(unsigned char* tablero)
{
    delete[] tablero;
}


unsigned char* agregarFila(unsigned char* tablero,
                           int ancho,
                           int alto,
                           int posicion)
{
    int nuevoAlto = alto + 1;

    int cantidadBits = ancho * nuevoAlto * 3;
    int cantidadBytes = (cantidadBits + 7) / 8;

    unsigned char* nuevoTablero =
        new unsigned char[cantidadBytes];

    inicializarTablero(nuevoTablero,
                       ancho,
                       nuevoAlto);

    for (int fila = 0; fila < nuevoAlto; fila++)
    {
        for (int columna = 0; columna < ancho; columna++)
        {
            if (fila < posicion)
            {
                int ficha = obtenerFicha(tablero,
                                         ancho,
                                         fila,
                                         columna);

                modificarFicha(nuevoTablero,
                               ancho,
                               fila,
                               columna,
                               ficha);
            }
            else if (fila == posicion)
            {
                modificarFicha(nuevoTablero,
                               ancho,
                               fila,
                               columna,
                               generarFicha());
            }
            else
            {
                int ficha = obtenerFicha(tablero,
                                         ancho,
                                         fila - 1,
                                         columna);

                modificarFicha(nuevoTablero,
                               ancho,
                               fila,
                               columna,
                               ficha);
            }
        }
    }

    liberarTablero(tablero);

    return nuevoTablero;
}
