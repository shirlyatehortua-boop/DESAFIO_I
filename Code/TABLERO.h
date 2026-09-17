#ifndef TABLERO_H
#define TABLERO_H

//ESTE HEADER LO UTILIZARE PARA EL TABLERO PARA TENER MAYOR ORGANIZACION

// mi tablero pedirá filas y columnas, se representa el tablero de juego usando 1 bit por celda
//empacado en bytes, por el ancho debe ser multiplo de 8, cada fila ocupa (ancho / 8) bytes.

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
