#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Tablero.h"
#include "Combinaciones.h"

using namespace std;

int main()
{
    srand(time(0));

    int ancho;
    int alto;

    cout << "========== SWEET CRUSH =========="
         << endl;

    cout << endl;

    cout << "Ingrese el ancho del tablero: ";
    cin >> ancho;

    cout << "Ingrese el alto del tablero: ";
    cin >> alto;

    while (ancho <= 0 || alto <= 0)
    {
        cout << endl;

        cout << "Las dimensiones deben ser mayores que 0."
             << endl;

        cout << "Ingrese el ancho del tablero: ";
        cin >> ancho;

        cout << "Ingrese el alto del tablero: ";
        cin >> alto;
    }

    unsigned char* tablero =
        crearTablero(ancho, alto);

    inicializarTablero(tablero,
                       ancho,
                       alto);

    llenarTablero(tablero,
                  ancho,
                  alto);

    unsigned char* eliminadas =
        crearMarcador(ancho,
                      alto);

    inicializarMarcador(eliminadas,
                        ancho,
                        alto);

    int eliminacionesUsuario = 0;
    int fichasEliminadas = 0;
    int combinacionesDetectadas = 0;
    int cascadasUltimaEliminacion = 0;
    int puntuacion = 0;

    int opcion = 0;

    while (opcion != 8)
    {
        cout << endl;
        cout << "========== MENU =========="
             << endl;

        cout << "1. Mostrar tablero" << endl;
        cout << "2. Seleccionar y eliminar ficha" << endl;
        cout << "3. Agregar fila" << endl;
        cout << "4. Eliminar fila" << endl;
        cout << "5. Agregar columna" << endl;
        cout << "6. Eliminar columna" << endl;
        cout << "7. Mostrar estadisticas" << endl;
        cout << "8. Salir" << endl;

        cout << "=========================="
             << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            cout << endl;

            cout << "========== TABLERO =========="
                 << endl;

            cout << endl;

            cout << "TABLERO EN DECIMAL:"
                 << endl;

            mostrarTablero(tablero,
                           ancho,
                           alto);

            cout << endl;

            cout << "TABLERO EN BINARIO:"
                 << endl;

            mostrarTableroBinario(tablero,
                                  ancho,
                                  alto);

            cout << endl;

            cout << "============================="
                 << endl;

            break;
        }

        case 2:
        {
            int fila;
            int columna;

            cout << endl;

            cout << "=== SELECCIONAR FICHA ==="
                 << endl;

            cout << "Ingrese la fila (0 - "
                 << alto - 1
                 << "): ";

            cin >> fila;

            cout << "Ingrese la columna (0 - "
                 << ancho - 1
                 << "): ";

            cin >> columna;

            if (fila < 0 ||
                fila >= alto ||
                columna < 0 ||
                columna >= ancho)
            {
                cout << endl;

                cout << "Posicion invalida."
                     << endl;

                break;
            }

            int fichaSeleccionada =
                obtenerFicha(tablero,
                             ancho,
                             fila,
                             columna);

            if (fichaSeleccionada == 0)
            {
                cout << endl;

                cout << "No hay una ficha en esa posicion."
                     << endl;

                break;
            }

            cout << endl;

            cout << "Ficha seleccionada: "
                 << fichaSeleccionada
                 << endl;

            modificarFicha(tablero,
                           ancho,
                           fila,
                           columna,
                           0);

            eliminacionesUsuario++;
            fichasEliminadas++;

            // Sistema de puntuacion:
            // 10 puntos por cada eliminacion realizada
            // por el usuario.
            // 10 puntos por cada ficha eliminada
            // por combinaciones.
            // 20 puntos por cada combinacion detectada.
            // 30 puntos por cada cascada procesada.

            puntuacion += 10;

            aplicarGravedad(tablero,
                            ancho,
                            alto);

            rellenarTablero(tablero,
                            ancho,
                            alto);

            int fichasDeCombinaciones = 0;
            int combinacionesMovimiento = 0;

            cascadasUltimaEliminacion =
                procesarCascadas(tablero,
                                 eliminadas,
                                 ancho,
                                 alto,
                                 &fichasDeCombinaciones,
                                 &combinacionesMovimiento);

            fichasEliminadas +=
                fichasDeCombinaciones;

            combinacionesDetectadas +=
                combinacionesMovimiento;

            puntuacion +=
                fichasDeCombinaciones * 10;

            puntuacion +=
                combinacionesMovimiento * 20;

            puntuacion +=
                cascadasUltimaEliminacion * 30;

            cout << endl;

            cout << "Ficha eliminada correctamente."
                 << endl;

            cout << "Cascadas procesadas: "
                 << cascadasUltimaEliminacion
                 << endl;

            cout << endl;

            cout << "Tablero despues del movimiento:"
                 << endl;

            mostrarTablero(tablero,
                           ancho,
                           alto);

            break;
        }

        case 3:
        {
            int posicion;

            cout << endl;

            cout << "=== AGREGAR FILA ==="
                 << endl;

            cout << "Ingrese la posicion de la nueva fila "
                 << "(0 - "
                 << alto
                 << "): ";

            cin >> posicion;

            if (posicion < 0 ||
                posicion > alto)
            {
                cout << endl;

                cout << "Posicion invalida."
                     << endl;

                break;
            }

            tablero =
                agregarFila(tablero,
                            ancho,
                            alto,
                            posicion);

            alto++;

            liberarMarcador(eliminadas);

            eliminadas =
                crearMarcador(ancho,
                              alto);

            inicializarMarcador(eliminadas,
                                ancho,
                                alto);

            cout << endl;

            cout << "Fila agregada correctamente."
                 << endl;

            cout << "Nuevo tablero: "
                 << ancho
                 << " x "
                 << alto
                 << endl;

            break;
        }

        case 4:
        {
            int posicion;

            if (alto <= 1)
            {
                cout << endl;

                cout << "No se puede eliminar la ultima fila."
                     << endl;

                break;
            }

            cout << endl;

            cout << "=== ELIMINAR FILA ==="
                 << endl;

            cout << "Ingrese la posicion de la fila "
                 << "(0 - "
                 << alto - 1
                 << "): ";

            cin >> posicion;

            if (posicion < 0 ||
                posicion >= alto)
            {
                cout << endl;

                cout << "Posicion invalida."
                     << endl;

                break;
            }

            tablero =
                eliminarFila(tablero,
                             ancho,
                             alto,
                             posicion);

            alto--;

            liberarMarcador(eliminadas);

            eliminadas =
                crearMarcador(ancho,
                              alto);

            inicializarMarcador(eliminadas,
                                ancho,
                                alto);

            cout << endl;

            cout << "Fila eliminada correctamente."
                 << endl;

            cout << "Nuevo tablero: "
                 << ancho
                 << " x "
                 << alto
                 << endl;

            break;
        }

        case 5:
        {
            int posicion;

            cout << endl;

            cout << "=== AGREGAR COLUMNA ==="
                 << endl;

            cout << "Ingrese la posicion de la nueva columna "
                 << "(0 - "
                 << ancho
                 << "): ";

            cin >> posicion;

            if (posicion < 0 ||
                posicion > ancho)
            {
                cout << endl;

                cout << "Posicion invalida."
                     << endl;

                break;
            }

            tablero =
                agregarColumna(tablero,
                               ancho,
                               alto,
                               posicion);

            ancho++;

            liberarMarcador(eliminadas);

            eliminadas =
                crearMarcador(ancho,
                              alto);

            inicializarMarcador(eliminadas,
                                ancho,
                                alto);

            cout << endl;

            cout << "Columna agregada correctamente."
                 << endl;

            cout << "Nuevo tablero: "
                 << ancho
                 << " x "
                 << alto
                 << endl;

            break;
        }

        case 6:
        {
            int posicion;

            if (ancho <= 1)
            {
                cout << endl;

                cout << "No se puede eliminar la ultima columna."
                     << endl;

                break;
            }

            cout << endl;

            cout << "=== ELIMINAR COLUMNA ==="
                 << endl;

            cout << "Ingrese la posicion de la columna "
                 << "(0 - "
                 << ancho - 1
                 << "): ";

            cin >> posicion;

            if (posicion < 0 ||
                posicion >= ancho)
            {
                cout << endl;

                cout << "Posicion invalida."
                     << endl;

                break;
            }

            tablero =
                eliminarColumna(tablero,
                                ancho,
                                alto,
                                posicion);

            ancho--;

            liberarMarcador(eliminadas);

            eliminadas =
                crearMarcador(ancho,
                              alto);

            inicializarMarcador(eliminadas,
                                ancho,
                                alto);

            cout << endl;

            cout << "Columna eliminada correctamente."
                 << endl;

            cout << "Nuevo tablero: "
                 << ancho
                 << " x "
                 << alto
                 << endl;

            break;
        }

        case 7:
        {
            cout << endl;

            cout << "========== ESTADISTICAS =========="
                 << endl;

            cout << "Ancho actual: "
                 << ancho
                 << endl;

            cout << "Alto actual: "
                 << alto
                 << endl;

            cout << "Eliminaciones realizadas por el usuario: "
                 << eliminacionesUsuario
                 << endl;

            cout << "Fichas eliminadas: "
                 << fichasEliminadas
                 << endl;

            cout << "Combinaciones detectadas: "
                 << combinacionesDetectadas
                 << endl;

            cout << "Cascadas de la ultima eliminacion: "
                 << cascadasUltimaEliminacion
                 << endl;

            cout << "Puntuacion: "
                 << puntuacion
                 << endl;

            cout << "================================="
                 << endl;

            break;
        }

        case 8:
        {
            cout << endl;

            cout << "Saliendo de Sweet Crush..."
                 << endl;

            break;
        }

        default:
        {
            cout << endl;

            cout << "Opcion invalida."
                 << endl;

            break;
        }
        }
    }

    liberarMarcador(eliminadas);

    liberarTablero(tablero);

    return 0;
}
