//En este archivo se declararan las funciones relacionadas
//Con la deteccion de combinaciones de fichas.

//Se trabajara con un marcador auxiliar para identificar
//Las fichas que deben ser eliminadas.

//12:35 de la noche

#ifndef COMBINACIONES_H
#define COMBINACIONES_H

unsigned char* crearMarcador(int ancho, int alto);

void inicializarMarcador(unsigned char* eliminadas, int ancho, int alto);

void detectarCombinaciones(unsigned char* tablero,
                           unsigned char* eliminadas,
                           int ancho,
                           int alto);

void eliminarCombinaciones(unsigned char* tablero,
                           unsigned char* eliminadas,
                           int ancho,
                           int alto);

void liberarMarcador(unsigned char* eliminadas);

#endif
