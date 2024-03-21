#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <optional>

struct GoldenPoint
{
    int x, y;
};

struct SilverPoint
{
    int x, y, score;
};

struct Tile
{
    std::string id;
    int cost, numAvailable;
};

struct Cell
{
    std::optional<GoldenPoint> goldPoint;
    std::optional<SilverPoint> silverPoint;
    std::optional<Tile> tile;
};

class RedBlackTree
{

private:
    NodePtr root;
    NodePtr TNULL;

    void initializeNULLNode(NodePtr node, NodePtr parent)
    {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    // Preorder
    void preOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            std::cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Inorder

    void inOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            inOrderHelper(node->left);
            std::cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(NodePtr node)
    {
        if (node != TNULL)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            std::cout << node->data << " ";
        }
    }

    NodePtr searchTreeHelper(NodePtr node, int key)
    {
        if (node == TNULL || key == node->data)
        {
            return node;
        }

        if (key < node->data)
        {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    // For balancing the tree after deletion
    void deleteFix(NodePtr x)
    {
        NodePtr s;
        while (x != root && x->color == 0)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == 0)
                    {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == 1)
                {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0)
                {
                    s->color = 1;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == 0)
                    {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    void rbTransplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key, std::string id)
    {
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL)
        {
            if (node->data == key && !node->id.compare(id))
            {
                z = node;
            }

            if (node->data <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == TNULL)
        {
            std::cout << "Key not found in the tree" << std::endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == TNULL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0)
        {
            deleteFix(x);
        }
    }

    // For balancing the tree after insertion
    void insertFix(NodePtr k)
    {
        NodePtr u;
        while (k->parent->color == 1)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == 1)
                {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = 0;
    }

    void printHelper(NodePtr root, std::string indent, bool last)
    {
        if (root != TNULL)
        {
            std::cout << indent;
            if (last)
            {
                std::cout << "R----";
                indent += "   ";
            }
            else
            {
                std::cout << "L----";
                indent += "|  ";
            }

            std::string sColor = root->color ? "RED" : "BLACK";
            std::cout << root->data << "(" << sColor << ")" << std::endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

public:
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    void preorder()
    {
        preOrderHelper(this->root);
    }

    void inorder()
    {
        inOrderHelper(this->root);
    }

    void postorder()
    {
        postOrderHelper(this->root);
    }

    NodePtr searchTree(int k)
    {
        return searchTreeHelper(this->root, k);
    }

    NodePtr minimum(NodePtr node)
    {
        while (node->left != TNULL)
        {
            node = node->left;
        }
        return node;
    }

    NodePtr maximum(NodePtr node)
    {
        while (node->right != TNULL)
        {
            node = node->right;
        }
        return node;
    }

    NodePtr successor(NodePtr x)
    {
        if (x->right != TNULL)
        {
            return minimum(x->right);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    NodePtr predecessor(NodePtr x)
    {
        if (x->left != TNULL)
        {
            return maximum(x->left);
        }

        NodePtr y = x->parent;
        while (y != TNULL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    void leftRotate(NodePtr x)
    {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(NodePtr x)
    {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(int key, std::string id)
    {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->id = id;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        while (x != TNULL)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        insertFix(node);
    }

    NodePtr getRoot()
    {
        return this->root;
    }

    void deleteNode(int data, std::string id)
    {
        deleteNodeHelper(this->root, data, id);
    }

    void printTree()
    {
        if (root)
        {
            printHelper(this->root, "", true);
        }
    }
};
RedBlackTree L_R, U_D, L_U, L_D, R_U, R_D;

enum Direction
{
    LEFT_TO_RIGHT,
    LEFT_TO_DOWN,
    LEFT_TO_UP,

    UP_TO_RIGHT,
    UP_TO_LEFT,
    UP_TO_DOWN,

    RIGHT_TO_UP,
    RIGHT_TO_LEFT,
    RIGHT_TO_DOWN,

    DOWN_TO_RIGHT,
    DOWN_TO_UP,
    DOWN_TO_LEFT,

    NO_ACTION
};
std::unordered_map<std::string, Tile> tileInventory;

// Completamento della mappa con i nuovi Tiles
const std::map<std::string, std::vector<Direction>> tileDirections = {
    {"3", {LEFT_TO_RIGHT}},
    {"5", {DOWN_TO_RIGHT}},
    {"6", {LEFT_TO_DOWN}},
    {"7", {LEFT_TO_RIGHT, LEFT_TO_DOWN, DOWN_TO_RIGHT}},
    {"9", {UP_TO_RIGHT}},
    {"96", {LEFT_TO_DOWN, UP_TO_RIGHT}},
    {"A", {LEFT_TO_UP}},
    {"A5", {LEFT_TO_UP, DOWN_TO_RIGHT}},
    {"B", {LEFT_TO_RIGHT, LEFT_TO_UP, UP_TO_RIGHT}},
    {"C", {UP_TO_DOWN}},
    {"C3", {LEFT_TO_RIGHT, UP_TO_DOWN}},
    {"D", {UP_TO_DOWN, UP_TO_RIGHT, DOWN_TO_RIGHT}},
    {"E", {LEFT_TO_UP, LEFT_TO_DOWN, UP_TO_DOWN}},
    {"F", {LEFT_TO_RIGHT, LEFT_TO_DOWN, LEFT_TO_UP, UP_TO_DOWN, DOWN_TO_RIGHT, UP_TO_RIGHT}},
};

// Dichiarazioni delle funzioni per la lettura
void readGoldenPoints(std::ifstream &file, std::vector<GoldenPoint> &goldenPoints);
void readSilverPoints(std::ifstream &file, std::vector<SilverPoint> &silverPoints);
void readTiles(std::ifstream &file, std::unordered_map<std::string, Tile> &tiles);

int *searchFirstPoint(std::vector<std::vector<Cell>> &matrix, int H, int W)
{
    int *pos = new int[2];

    int i, j;
    for (i = 0; i <= W; i++)
    {
        for (j = 0; j <= H; j++)
        {
            if (matrix[i][j].goldPoint.has_value())
            {
                pos[0] = i;
                pos[1] = j;
                return;
            }
        }
    }
}

// fra

struct Node
{
    int data;
    std::string id;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};

typedef Node *NodePtr;

//
int main()
{
    std::ifstream file("./input/trailer.txt");
    if (!file)
    {
        std::cerr << "Impossibile aprire il file di input!" << std::endl;
        return 1;
    }

    int W, H, GN, SM, TL;
    file >> W >> H >> GN >> SM >> TL;

    std::vector<std::vector<Cell>> matrix(H, std::vector<Cell>(W));
    std::vector<GoldenPoint> goldenPoints(GN);
    readGoldenPoints(file, goldenPoints, matrix);

    std::vector<SilverPoint> silverPoints(SM);
    readSilverPoints(file, silverPoints, matrix);

    readTiles(file, tileInventory);

    file.close(); // Chiudi il file dopo aver finito di leggere i dati

    // iniziamo a fare schifo
    searchFirstPoint(matrix, H, W);
    const std::string filename = "output.txt";

    writeRowToFile(filename, matrix, W, H);

    return 0;
}

void writeRowToFile(const std::string &filename, std::vector<std::vector<Cell>> &matrix, int W, int H)
{
    std::ofstream file(filename, std::ios::app);
    if (file.is_open())
    {
        for (int i = 0; i < W; i++)
        {
            for (int j = 0; j < H; j++)
            {
                if (matrix[i][j].tile.has_value())
                {
                    file << '\t' << matrix[i][j].tile.value().id << '\t' << i << '\t' << j << "\n";
                }
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file." << std::endl;
    }
}

void readGoldenPoints(std::ifstream &file, std::vector<GoldenPoint> &goldenPoints, std::vector<std::vector<Cell>> &matrix)
{
    for (auto &point : goldenPoints)
    {
        file >> point.x >> point.y;
        matrix[point.x][point.y].goldPoint = point;
    }
}

void readSilverPoints(std::ifstream &file, std::vector<SilverPoint> &silverPoints, std::vector<std::vector<Cell>> &matrix)
{
    for (auto &point : silverPoints)
    {
        file >> point.x >> point.y >> point.score;
        matrix[point.x][point.y].silverPoint = point;
    }
}

// Funzione per leggere i tiles e aggiornare l'inventario
void readTiles(std::ifstream &file, std::unordered_map<std::string, Tile> &tileInventory)
{

    int TL; // Numero di tipi di tiles
    file >> TL;
    std::string id;
    int cost, numAvailable;
    for (int i = 0; i < TL; ++i)
    {
        file >> id >> cost >> numAvailable;
        tileInventory[id] = {id, cost, numAvailable};
        if (!id.compare("3"))
        {
            L_R.insert(cost, id);
        }
        if (!id.compare("5"))
        {
            L_U.insert(cost, id);
            R_D.insert(cost, id);
        }
        if (!id.compare("6"))
        {
            L_D.insert(cost, id);
        }
        if (!id.compare("7"))
        {
            L_R.insert(cost, id);
            R_D.insert(cost, id);
        }
        if (!id.compare("9"))
        {
            R_U.insert(cost, id);
        }
        if (!id.compare("A"))
        {
            L_U.insert(cost, id);
        }
        if (!id.compare("B"))
        {
            L_R.insert(cost, id);
            L_U.insert(cost, id);
            R_U.insert(cost, id);
        }
        if (!id.compare("C"))
        {
            U_D.insert(cost, id);
        }
        if (!id.compare("D"))
        {
            U_D.insert(cost, id);
            R_U.insert(cost, id);
            R_D.insert(cost, id);
        }
        if (!id.compare("E"))
        {
            U_D.insert(cost, id);
            L_U.insert(cost, id);
            L_D.insert(cost, id);
        }
        if (!id.compare("F"))
        {
            L_R.insert(cost, id);
            L_U.insert(cost, id);
            L_D.insert(cost, id);
            R_U.insert(cost, id);
            R_D.insert(cost, id);
            R_D.insert(cost, id);
            U_D.insert(cost, id);
        }
    }
}

// Funzione per utilizzare un tile e aggiornare l'inventario
void useTile(const std::string &id)
{
    if (tileInventory[id].numAvailable > 0)
    {
        tileInventory[id].numAvailable--;
        // Qui puoi aggiungere altre logiche per l'uso del tile
    }
    else
    {
        std::cerr << "Non ci sono più tile disponibili per l'ID: " << id << std::endl;
    }
}

std::optional<SilverPoint> searchSilverPoint(std::vector<std::vector<Cell>> &matrix, int H, int W, GoldenPoint &G1, GoldenPoint &G2)
{
    int i, j;
    for (i = G1.x; i <= G2.x; i++)
    {
        for (j = G1.y; j <= G2.y; j++)
        {
            if (matrix[i][j].silverPoint.has_value())
            {
                return matrix[i][j].silverPoint;
            }
        }
    }
}
