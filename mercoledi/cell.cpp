#include <iostream>
#include <cmath>
#include <utility> // per std::pair
#include <string> 

struct Cell {
    int x;
    int y;
    int relevance;  // Valore di rilevanza della cella
    bool occ;
    bool occ_tmp;
    bool isWH; // true if the cell is a wormhole

    //puntatori
    Cell *up;
    Cell *down;
    Cell *left;
    Cell *right;
};

typedef Cell *cell_ptr;

class CellClass {
    cell_ptr actual_cell;
public:
    CellClass(cell_ptr c_cell) { this->actual_cell = c_cell; }
    
    int distance(cell_ptr cell) {
        return (1 + std::abs(actual_cell->x - cell->x) + std::abs(actual_cell->y - cell->y));
    }

    
private:

};