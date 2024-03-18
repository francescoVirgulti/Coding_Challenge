#include <iostream>
#include <fstream>
#include <vector>

//prova commento
using namespace std;
struct{
    int x,
    int y, 
    bool occ,
}cella_T;


int main() {
    int C, R, S;
    vector<int> snakeLengths;

    // Lettura dell'input
    ifstream input("input.txt");
    if (!input.is_open()) {
        cout << "Impossibile aprire il file di input." << endl;
        return 1;
    }

    input >> C >> R >> S;

    snakeLengths.resize(S);
    for (int i = 0; i < S; ++i) {
        input >> snakeLengths[i];
    }

    vector<vector<int>> grid(R, vector<int>(C));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            char cell;
            input >> cell;
            if (cell == '*') {
                grid[i][j] = -1; // Segna la presenza di un wormhole con -1
            } else {
                grid[i][j] = cell - '0'; // Converte il carattere in intero
            }
        }
    }

    // Stampa della matrice inizializzata
    cout << "Matrice inizializzata:" << endl;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    input.close();

    return 0;
}
