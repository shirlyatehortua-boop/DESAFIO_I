#ifndef TABLERO_H
#define TABLERO_H

#endif // TABLERO_H
//ESTE HEADER LO UTILIZARE PARA EL TABLERO PARA TENER MAYOR ORGANIZACION

#include <iostream>
#include <vector>
using namespace std;

// mi tablero pedirá filas y columnas
int main() {

    int filas, columnas;

    cout << "Ingrese el numero de filas: ";
    cin >> filas;

    cout << "Ingrese el numero de columnas: ";
    cin >> columnas;

//CREAR EL TABLERITO
    vector<vector<int>> tablero(filas, vector<int>(columnas, 0));

    // Mostrar el tablero
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << tablero[i][j];
        }
        cout << endl;
    }

    return 0;
}
