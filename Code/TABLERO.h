#ifndef TABLERO_H
#define TABLERO_H

//Se inicia de nuevo por motivo de error en guia
// Estaba haciendo el proyecto del semestre pasado
//Entonces para seguir con el orden de los commits retomo nuevamente con los codigos

unsigned char* crearTablero(int ancho, int alto);

void inicializarTablero(unsigned char* tablero, int ancho, int alto);

int generarFicha();

void llenarTablero(unsigned char* tablero, int ancho, int alto);

int obtenerFicha(unsigned char* tablero, int ancho, int fila, int columna);

void modificarFicha(unsigned char* tablero, int ancho, int fila, int columna, int ficha);

void mostrarTablero(unsigned char* tablero, int ancho, int alto);

void aplicarGravedad(unsigned char* tablero, int ancho, int alto);

void rellenarTablero(unsigned char* tablero, int ancho, int alto);

void liberarTablero(unsigned char* tablero);

#endif
