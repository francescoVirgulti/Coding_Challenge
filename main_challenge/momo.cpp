#include <iostream>
#include <vector>
#include <string>

struct GoldenPoint {
    int x, y;
};

struct SilverPoint {
    int x, y, score;
};

struct Tile {
    std::string id;
    int cost, numAvailable;
};

int main() {
    int W, H, GN, SM, TL;
    std::cin >> W >> H >> GN >> SM >> TL;

    std::vector<GoldenPoint> goldenPoints(GN);
    for (int i = 0; i < GN; ++i) {
        std::cin >> goldenPoints[i].x >> goldenPoints[i].y;
    }

    std::vector<SilverPoint> silverPoints(SM);
    for (int i = 0; i < SM; ++i) {
        std::cin >> silverPoints[i].x >> silverPoints[i].y >> silverPoints[i].score;
    }

    std::vector<Tile> tiles(TL);
    for (int i = 0; i < TL; ++i) {
        std::cin >> tiles[i].id >> tiles[i].cost >> tiles[i].numAvailable;
    }


    return 0;
}
