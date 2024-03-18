#include <iostream>
#include <unordered_map>
#include <map>

typedef pair<int, int> Coordinate;
typedef map<Coordinate, bool> CoordinateMap;

struct Cell {
    int x;
    int y;
    bool occ;
    bool isWH; // true if the cell is a wormhole
};
typedef Cell* CellPtr;
// Definizione del tipo per la matrice
typedef vector<vector<Cell>> Matrix;

string ricorsivo(CellPtr* tmp, int snakeLenghts, int lung_temporanea, CoordinateMap* coordinateMap, string percorso, Matrix *mat ){
    Coordinate x_y_max;
    if(lung_temporanea = snakeLenghts-1){return percorso;}
    else{
        int int_max,x,y;
        int_max = 0;
        string direzione;
        if(mat[tmp->x - 1][tmp->y] > int_max ){
            int_max = mat[tmp->x - 1][tmp->y];
            x_y_max = make_pair(tmp->x - 1,tmp->y);
            direzione = "L";

        }else 
        if(mat[tmp->x + 1][tmp->y] > int_max ){
            int_max = mat[tmp->x + 1][tmp->y];
            x_y_max = make_pair(tmp->x + 1,tmp->y);
            direzione = "R";      
        } else
        if(mat[tmp->x ][tmp->y-1] > int_max ){
            int_max = mat[tmp->x][tmp->y - 1];
            x_y_max = make_pair(tmp->x,tmp->y-1);
            direzione = "D";      
        } else
        if(mat[tmp->x ][tmp->y + 1] > int_max ){
            int_max = mat[tmp->x][tmp->y+1];
            x_y_max = make_pair(tmp->x,tmp->y + 1);
            direzione = "U";      
        }

        (*coordinateMap)[x_y_max] = false;
        snakeLenghts--;
        CellaPtr new_start;
         
        return percorso += direzione += ricorsivo() 
        
    }

}

void ricerca(CellPtr start, int snakeLengths, ){
    
     string percorso = "";
    // Definizione della mappa 
    //  se la maps dà true => posso andare in quella direzione 
    CoordinateMap = coordinateMap;
    Coordinate start = make_pair(start->x, start->y);
    coordinateMap[start] = false;

    
}