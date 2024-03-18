#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Cell {
    int x;
    int y;
    bool occ;
    bool isWH; // true if the cell is a wormhole
};

typedef Cell* CellPtr;

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

    vector<vector<Cell>> grid(R, vector<Cell>(C));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            char cell;
            input >> cell;
            if (cell == '*') {
                grid[i][j].isWH = true; // Segna la presenza di un wormhole
            } else {
                grid[i][j].x = i; // Coordinata x della cella
                grid[i][j].y = j; // Coordinata y della cella
                grid[i][j].occ = false; // Inizialmente la cella non è occupata
                grid[i][j].isWH = false; // Inizialmente la cella non è un wormhole
            }
        }
    }

    // Stampa della matrice inizializzata
    cout << "Matrice inizializzata:" << endl;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << "(" << grid[i][j].x << "," << grid[i][j].y << "," << grid[i][j].occ << "," << grid[i][j].isWH << ") ";
        }
        cout << endl;
    }

    input.close();

    return 0;
}
