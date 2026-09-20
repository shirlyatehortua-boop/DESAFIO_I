#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Tablero.h"
#include "Combinaciones.h"

using namespace std;

int main()
{
    int ancho;
    int alto;
    int opcion;

    // Estadisticas
    int eliminacionesUsuario = 0;
    int fichasEliminadas = 0;
    int combinacionesDetectadas = 0;
    int cascadasUltimaEliminacion = 0;
    int puntuacion = 0;

    srand(time(0));

    cout << "========== SWEET CRUSH ==========" << endl;

    cout << "Ingrese el ancho del tablero: ";
    cin >> ancho;

    cout << "Ingrese el alto del tablero: ";
    cin >> alto;

    if (ancho <= 0 || alto <= 0)
    {
        cout << "Dimensiones invalidas." << endl;
        return 1;
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
        crearMarcador(ancho, alto);

    do
    {
        cout << endl;
        cout << "========== MENU ==========" << endl;
        cout << "1. Mostrar tablero" << endl;
        cout << "2. Seleccionar y eliminar ficha" << endl;
        cout << "3. Agregar fila" << endl;
        cout << "4. Eliminar fila" << endl;
        cout << "5. Agregar columna" << endl;
        cout << "6. Eliminar columna" << endl;
        cout << "7. Mostrar estadisticas" << endl;
        cout << "8. Salir" << endl;
        cout << "==========================" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // --------------------------------------------------
        // OPCION 1
        // --------------------------------------------------

        if (opcion == 1)
        {
            cout << endl;
            cout << "========== TABLERO =========="
                 << endl;

            mostrarTablero(tablero,
                           ancho,
                           alto);
        }

        // --------------------------------------------------
        // OPCION 2
        // --------------------------------------------------

        else if (opcion == 2)
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

            if (fila < 0 || fila >= alto ||
                columna < 0 || columna >= ancho)
            {
                cout << endl;
                cout << "Posicion invalida."
                     << endl;
            }
            else
            {
                int ficha =
                    obtenerFicha(tablero,
                                 ancho,
                                 fila,
                                 columna);

                if (ficha == 0)
                {
                    cout << endl;
                    cout << "No hay una ficha en esa posicion."
                         << endl;
                }
                else
                {
                    cout << endl;
                    cout << "Ficha seleccionada: "
                         << ficha
                         << endl;

                    modificarFicha(tablero,
                                   ancho,
                                   fila,
                                   columna,
                                   0);

                    eliminacionesUsuario++;
                    fichasEliminadas++;

                    // Puntos por eliminacion manual
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

                    // Puntuacion por combinaciones y cascadas
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
                }
            }
        }

        // --------------------------------------------------
        // OPCION 3
        // --------------------------------------------------

        else if (opcion == 3)
        {
            int posicion;

            cout << endl;
            cout << "=== AGREGAR FILA ==="
                 << endl;

            cout << "Ingrese la posicion de la nueva fila (0 - "
                 << alto
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion > alto)
            {
                cout << "Posicion invalida."
                     << endl;
            }
            else
            {
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

                cout << endl;
                cout << "Fila agregada correctamente."
                     << endl;

                cout << endl;
                cout << "Tablero actualizado:"
                     << endl;

                mostrarTablero(tablero,
                               ancho,
                               alto);
            }
        }

        // --------------------------------------------------
        // OPCION 4
        // --------------------------------------------------

        else if (opcion == 4)
        {
            int posicion;

            cout << endl;
            cout << "=== ELIMINAR FILA ==="
                 << endl;

            cout << "Ingrese la posicion de la fila (0 - "
                 << alto - 1
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion >= alto)
            {
                cout << "Posicion invalida."
                     << endl;
            }
            else if (alto <= 1)
            {
                cout << "No se puede eliminar la ultima fila."
                     << endl;
            }
            else
            {
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

                cout << endl;
                cout << "Fila eliminada correctamente."
                     << endl;

                cout << endl;
                cout << "Tablero actualizado:"
                     << endl;

                mostrarTablero(tablero,
                               ancho,
                               alto);
            }
        }

        // --------------------------------------------------
        // OPCION 5
        // --------------------------------------------------

        else if (opcion == 5)
        {
            int posicion;

            cout << endl;
            cout << "=== AGREGAR COLUMNA ==="
                 << endl;

            cout << "Ingrese la posicion de la nueva columna (0 - "
                 << ancho
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion > ancho)
            {
                cout << "Posicion invalida."
                     << endl;
            }
            else
            {
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

                cout << endl;
                cout << "Columna agregada correctamente."
                     << endl;

                cout << endl;
                cout << "Tablero actualizado:"
                     << endl;

                mostrarTablero(tablero,
                               ancho,
                               alto);
            }
        }

        // --------------------------------------------------
        // OPCION 6
        // --------------------------------------------------

        else if (opcion == 6)
        {
            int posicion;

            cout << endl;
            cout << "=== ELIMINAR COLUMNA ==="
                 << endl;

            cout << "Ingrese la posicion de la columna (0 - "
                 << ancho - 1
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion >= ancho)
            {
                cout << "Posicion invalida."
                     << endl;
            }
            else if (ancho <= 1)
            {
                cout << "No se puede eliminar la ultima columna."
                     << endl;
            }
            else
            {
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

                cout << endl;
                cout << "Columna eliminada correctamente."
                     << endl;

                cout << endl;
                cout << "Tablero actualizado:"
                     << endl;

                mostrarTablero(tablero,
                               ancho,
                               alto);
            }
        }

        // --------------------------------------------------
        // OPCION 7
        // --------------------------------------------------

        else if (opcion == 7)
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
        }

        // --------------------------------------------------
        // OPCION 8
        // --------------------------------------------------

        else if (opcion == 8)
        {
            cout << endl;
            cout << "Saliendo del juego..."
                 << endl;
        }

        else
        {
            cout << endl;
            cout << "Opcion invalida."
                 << endl;
        }

    } while (opcion != 8);

    liberarMarcador(eliminadas);
    liberarTablero(tablero);

    return 0;
}
