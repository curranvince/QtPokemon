#ifndef MAP_H
#define MAP_H

#include <unordered_map>

#include "tile.h"

class Map
{

private:
    std::unordered_map<Position, Tile*, PositionHash> tiles_;

public:
    Map();

    std::vector<Tile*> GetAllTiles();

    bool CheckAdjTileValid(Position pos, Direction direction);
};

#endif // MAP_H
