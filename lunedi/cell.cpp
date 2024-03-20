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

    std::string ricerca(int snakeLengths) {
        return ricorsivo(0, snakeLengths, actual_cell);
    }

    int ricercaPointMax(int snakeLengths) {
        return ricorsivo(0, snakeLengths, actual_cell);
    }
    
    int ricorsivoPointMax(int index, int snakeLengths, cell_ptr c) {
        if (index == snakeLengths) {
            return 0;
        } else {
            int punteggio;
            int int_max;
            cell_ptr temporaneo;
            int_max = 0;
            
            if (c->left->relevance > int_max && !c->left->occ_tmp) {
                int_max = c->left->relevance;
                punteggio = c->left->relevance;
                temporaneo = c->left;
            } else if (c->right->relevance > int_max && !c->right->occ_tmp) {
                int_max = c->right->relevance;
                temporaneo = c->right;
                direzione = "R";      
            } else if (c->down->relevance > int_max && !c->down->occ_tmp) {
                int_max = c->down->relevance;
                temporaneo = c->down;
                direzione = "D";      
            } else if (c->up->relevance > int_max &&  !c->up->occ_tmp) {
                int_max = c->up->relevance;
                temporaneo = c->up;
                direzione = "U";      
            }
            
            temporaneo->occ_tmp = true;
            return direzione + ricorsivo(index + 1, snakeLengths, temporaneo);
        }
    }


private:
    std::string ricorsivo(int index, int snakeLengths, cell_ptr c) {
        if (index == snakeLengths) {
            return "";
        } else {
            std::string direzione;
            int int_max;
            cell_ptr temporaneo;
            int_max = 0;
            
            if (c->left->relevance > int_max && !c->left->occ_tmp) {
                int_max = c->left->relevance;
                direzione = "L";
                temporaneo = c->left;
            } else if (c->right->relevance > int_max && !c->right->occ_tmp) {
                int_max = c->right->relevance;
                temporaneo = c->right;
                direzione = "R";      
            } else if (c->down->relevance > int_max && !c->down->occ_tmp) {
                int_max = c->down->relevance;
                temporaneo = c->down;
                direzione = "D";      
            } else if (c->up->relevance > int_max &&  !c->up->occ_tmp) {
                int_max = c->up->relevance;
                temporaneo = c->up;
                direzione = "U";      
            }
            
            temporaneo->occ_tmp = true;
            return direzione + ricorsivo(index + 1, snakeLengths, temporaneo);
        }
    }
};