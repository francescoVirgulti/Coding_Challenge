#ifndef CELLCLASS_H
#define CELLCLASS_H

#include <string>

struct Cell {
    int x;
    int y;
    int relevance;  // Valore di rilevanza della cella
    bool occ;
    bool occ_tmp;
    bool isWH; // true if the cell is a wormhole

    // Puntatori alle celle adiacenti
    Cell *up;
    Cell *down;
    Cell *left;
    Cell *right;
};

typedef Cell *cell_ptr;

class CellClass {
private:
    cell_ptr actual_cell;
public:
    CellClass(cell_ptr c_cell);

    int distance(cell_ptr cell);


private:
};

#endif // CELLCLASS_H
