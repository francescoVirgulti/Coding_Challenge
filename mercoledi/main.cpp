#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include "RedBlackTree.h"
#include "Cell.h"
#include "SerpenteRedBlackTree.h"
using namespace std;
int N = 5;


int main() {
    RedBlackTree albero;
    SerpenteRedBlackTree serpente_albero;
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
        int key;
        input >> key; 
        serpente_albero.insert(key, i);
    }

   std::vector<std::vector<Cell*>> matrix(R, std::vector<Cell*>(C));

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            int cell;
            input >> cell;
            albero.insert(cell,i,j);
            if (cell == '*') {
                matrix[i][j]->relevance = 0;
                matrix[i][j]->isWH = true;
                
            } else {
                matrix[i][j]->relevance = cell - '0'; // Converte il carattere in intero
                matrix[i][j]->isWH = false;
            }
            if(i==0 && j==0){
                    matrix[i][j]->right= matrix[0][j+1];
                    matrix[i][j]->left= matrix[0][C-1];
                    matrix[i][j]->up= matrix[R-1][0];
                    matrix[i][j]->down= matrix[i+1][0];
                }
                else if(i == 0 && j == C - 1){
                    matrix[i][j]->right= matrix[0][0];
                    matrix[i][j]->left= matrix[0][j-1];
                    matrix[i][j]->up= matrix[R-1][j];
                    matrix[i][j]->down= matrix[i+1][j];
                }
                else if(i == R-1 && j == C - 1){
                    matrix[i][j]->right= matrix[i][0];
                    matrix[i][j]->left= matrix[i][j-1];
                    matrix[i][j]->up= matrix[i-1][j];
                    matrix[i][j]->down= matrix[0][j];
                }
                else if(i == R-1 && j == 0){
                    matrix[i][j]->right= matrix[i][j+1];
                    matrix[i][j]->left= matrix[i][C-1];
                    matrix[i][j]->up= matrix[i-1][j];
                    matrix[i][j]->down= matrix[0][j];
                }
                else if(i == 0 ){
                    matrix[i][j]->right= matrix[i][j+1];
                    matrix[i][j]->left= matrix[i][j-1];
                    matrix[i][j]->up= matrix[R-1][j];
                    matrix[i][j]->down= matrix[i+1][j];
                }else if(i == R-1){
                    matrix[i][j]->right= matrix[i][j+1];
                    matrix[i][j]->left= matrix[i][j-1];
                    matrix[i][j]->up= matrix[i-1][j];
                    matrix[i][j]->down= matrix[0][j];
                }else if(j = 0){
                    matrix[i][j]->right= matrix[i][j+1];
                    matrix[i][j]->left= matrix[i][C-1];
                    matrix[i][j]->up= matrix[i-1][j];
                    matrix[i][j]->down= matrix[i+1][j];
                }else if(j==C-1){
                    matrix[i][j]->right= matrix[i][0];
                    matrix[i][j]->left= matrix[i][j-1];
                    matrix[i][j]->up= matrix[i-1][j];
                    matrix[i][j]->down= matrix[i+1][j];
                }else{
                    matrix[i][j]->right= matrix[i][j+1];
                    matrix[i][j]->left= matrix[i][j-1];
                    matrix[i][j]->up= matrix[i-1][j];
                    matrix[i][j]->down= matrix[i+1][j];
                }
            matrix[i][j]->x = i;
            matrix[i][j]->y = j; 
            matrix[i][j]->occ = false;
            matrix[i][j]->occ_tmp = false;
        
        }
    }

    std::queue<int> massimi;

    for(int i=0; i<S; i++){
        int snakeLenght  = serpente_albero.maximum(serpente_albero.getRoot())->data;
        int nSerpente =serpente_albero.maximum(serpente_albero.getRoot())->nSerpente;
        serpente_albero.deleteNode_S(snakeLenght);

        std::vector<NodePtr> n_massimi;

        NodePtr  max = albero.maximum(albero.getRoot()) ;
        albero.deleteNode(max->data);

        n_massimi.push_back(albero.maximum(albero.getRoot()));

        for (int j = 0; j < N; j++)
        {
            bool flag=false;
            for(int k=0; k< n_massimi.size()&&flag==false; k++){
                if(abs(n_massimi.at(k)->x - albero.successor(max)->x) + abs(n_massimi.at(k)->y - albero.successor(max)->y) + 1
                    <snakeLenght)
                    flag=true;
            }
            if(flag==false)
                n_massimi.push_back(albero.successor(max));
        }
        
        CellClass c(matrix[n_massimi.front() -> x][(n_massimi.front()) -> y]);

        for (int j = 0; j < N; j++)
        {
            n_massimi.push(albero.successor(max));
        }

    }

    

    
    input.close();

    return 0;
}
