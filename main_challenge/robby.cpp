#include <iostream>
#include <optional>
#include <vector>

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

Direction giveDirection(int x1, int y1, int x2, int y2)
{
    if (x1 > x2)
    {
        if (y1 > y2)
        {
            return RIGHT_TO_DOWN;
        }
        else if (y1 == y2)
        {
            return RIGHT_TO_LEFT;
        }
        else
        {
            return RIGHT_TO_UP;
        }
    }
    else if (x1 == x2)
    {
        if (y1 > y2)
        {
            return UP_TO_DOWN;
        }
        else if (y1 == y2)
        {
            return NO_ACTION;
        }
        else
        {
            return DOWN_TO_UP;
        }
    }
    else
    {
        if (y1 > y2)
        {
            return LEFT_TO_DOWN;
        }
        else if (y1 == y2)
        {
            return LEFT_TO_RIGHT;
        }
        else
        {
            return LEFT_TO_UP;
        }
    }
}

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
                matrix[i][j].goldPoint.reset();
                pos[0] = i;
                pos[1] = j;
                return;
            }
        }
    }
}
