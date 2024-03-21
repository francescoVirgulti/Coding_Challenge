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





enum Direction
{
    LEFT_TO_RIGHT,
    DOWN_TO_RIGHT,
    LEFT_TO_DOWN,
    UP_TO_RIGHT,
    LEFT_TO_UP,
    UP_TO_DOWN
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

    // Usa printf per stampare l'inventario dei tile
    for (const auto &tile : tileInventory)
    {
        printf("Tile ID: %s\n", tile.second.id.c_str());
        printf("Cost: %d\n", tile.second.cost);
        printf("Number Available: %d\n\n", tile.second.numAvailable);
    }
    return 0;
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
