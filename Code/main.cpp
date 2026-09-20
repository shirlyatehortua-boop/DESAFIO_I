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

    srand(time(0));

    // -----------------------------------------
    // CREAR TABLERO
    // -----------------------------------------

    cout << "========== SWEET CRUSH ==========" << endl;

    cout << "Ingrese el ancho del tablero: ";
    cin >> ancho;

    cout << "Ingrese el alto del tablero: ";
    cin >> alto;

    // Validar dimensiones
    if (ancho <= 0 || alto <= 0)
    {
        cout << "Dimensiones invalidas." << endl;
        return 1;
    }

    unsigned char* tablero = crearTablero(ancho, alto);

    inicializarTablero(tablero,
                       ancho,
                       alto);

    llenarTablero(tablero,
                  ancho,
                  alto);

    unsigned char* eliminadas =
        crearMarcador(ancho, alto);

    // -----------------------------------------
    // MENU PRINCIPAL
    // -----------------------------------------

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

        // -------------------------------------
        // OPCION 1
        // MOSTRAR TABLERO
        // -------------------------------------

        if (opcion == 1)
        {
            cout << endl;
            cout << "========== TABLERO ==========" << endl;

            mostrarTablero(tablero,
                           ancho,
                           alto);
        }

        // -------------------------------------
        // OPCION 2
        // SELECCIONAR Y ELIMINAR FICHA
        // -------------------------------------

        else if (opcion == 2)
        {
            int fila;
            int columna;

            cout << endl;
            cout << "=== SELECCIONAR FICHA ===" << endl;

            cout << "Ingrese la fila (0 - "
                 << alto - 1
                 << "): ";
            cin >> fila;

            cout << "Ingrese la columna (0 - "
                 << ancho - 1
                 << "): ";
            cin >> columna;

            // Validar posicion
            if (fila < 0 || fila >= alto ||
                columna < 0 || columna >= ancho)
            {
                cout << endl;
                cout << "Posicion invalida." << endl;
            }
            else
            {
                int ficha = obtenerFicha(tablero,
                                         ancho,
                                         fila,
                                         columna);

                cout << endl;
                cout << "Ficha seleccionada: "
                     << ficha << endl;

                // Eliminar ficha
                modificarFicha(tablero,
                               ancho,
                               fila,
                               columna,
                               0);

                // Aplicar gravedad
                aplicarGravedad(tablero,
                                ancho,
                                alto);

                // Generar nuevas fichas
                rellenarTablero(tablero,
                                ancho,
                                alto);

                // Procesar combinaciones y cascadas
                int cantidadCascadas =
                    procesarCascadas(tablero,
                                     eliminadas,
                                     ancho,
                                     alto);

                cout << endl;
                cout << "Ficha eliminada correctamente."
                     << endl;

                cout << "Cascadas procesadas: "
                     << cantidadCascadas
                     << endl;

                cout << endl;
                cout << "Tablero despues del movimiento:"
                     << endl;

                mostrarTablero(tablero,
                               ancho,
                               alto);
            }
        }

        // -------------------------------------
        // OPCION 3
        // AGREGAR FILA
        // -------------------------------------

        else if (opcion == 3)
        {
            int posicion;

            cout << endl;
            cout << "=== AGREGAR FILA ===" << endl;

            cout << "Ingrese la posicion de la nueva fila (0 - "
                 << alto
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion > alto)
            {
                cout << "Posicion invalida." << endl;
            }
            else
            {
                tablero = agregarFila(tablero,
                                      ancho,
                                      alto,
                                      posicion);

                alto++;

                liberarMarcador(eliminadas);

                eliminadas = crearMarcador(ancho, alto);;

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

        // -------------------------------------
        // OPCION 4
        // ELIMINAR FILA
        // -------------------------------------

        else if (opcion == 4)
        {
            int posicion;

            cout << endl;
            cout << "=== ELIMINAR FILA ===" << endl;

            cout << "Ingrese la posicion de la fila (0 - "
                 << alto - 1
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion >= alto)
            {
                cout << "Posicion invalida." << endl;
            }
            else if (alto <= 1)
            {
                cout << "No se puede eliminar la ultima fila."
                     << endl;
            }
            else
            {
                tablero = eliminarFila(tablero,
                                       ancho,
                                       alto,
                                       posicion);

                alto--;

                liberarMarcador(eliminadas);

                eliminadas = crearMarcador(ancho, alto);

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

        // -------------------------------------
        // OPCION 5
        // AGREGAR COLUMNA
        // -------------------------------------

        else if (opcion == 5)
        {
            int posicion;

            cout << endl;
            cout << "=== AGREGAR COLUMNA ===" << endl;

            cout << "Ingrese la posicion de la nueva columna (0 - "
                 << ancho
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion > ancho)
            {
                cout << "Posicion invalida." << endl;
            }
            else
            {
                tablero = agregarColumna(tablero,
                                         ancho,
                                         alto,
                                         posicion);

                ancho++;

                liberarMarcador(eliminadas);

                eliminadas = crearMarcador(ancho, alto);

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

        // -------------------------------------
        // OPCION 6
        // ELIMINAR COLUMNA
        // -------------------------------------

        else if (opcion == 6)
        {
            int posicion;

            cout << endl;
            cout << "=== ELIMINAR COLUMNA ===" << endl;

            cout << "Ingrese la posicion de la columna (0 - "
                 << ancho - 1
                 << "): ";

            cin >> posicion;

            if (posicion < 0 || posicion >= ancho)
            {
                cout << "Posicion invalida." << endl;
            }
            else if (ancho <= 1)
            {
                cout << "No se puede eliminar la ultima columna."
                     << endl;
            }
            else
            {
                tablero = eliminarColumna(tablero,
                                          ancho,
                                          alto,
                                          posicion);

                ancho--;

                liberarMarcador(eliminadas);

                eliminadas = crearMarcador(ancho, alto);

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

        // -------------------------------------
        // OPCION 7
        // ESTADISTICAS
        // -------------------------------------

        else if (opcion == 7)
        {
            cout << endl;
            cout << "Las estadisticas "
                    "aun no estan implementadas."
                 << endl;
        }

        // -------------------------------------
        // OPCION 8
        // SALIR
        // -------------------------------------

        else if (opcion == 8)
        {
            cout << endl;
            cout << "Saliendo del juego..." << endl;
        }

        // -------------------------------------
        // OPCION INVALIDA
        // -------------------------------------

        else
        {
            cout << endl;
            cout << "Opcion invalida." << endl;
        }

    } while (opcion != 8);

    // -----------------------------------------
    // LIBERAR MEMORIA
    // -----------------------------------------

    liberarMarcador(eliminadas);

    liberarTablero(tablero);

    return 0;
}
