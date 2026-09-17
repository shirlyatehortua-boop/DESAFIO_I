#ifndef TABLERO_H
#define TABLERO_H
unsigned char** crearTablero(int ancho, int alto);

void inicializarTablero(unsigned char** tablero, int ancho, int alto);

void mostrarTablero(unsigned char** tablero, int ancho, int alto);

void liberarTablero(unsigned char** tablero, int alto);

#endif
