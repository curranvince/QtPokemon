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
    Type CheckTileType(Position pos) { return tiles_.at(pos)->GetType(); }

    Position FindNearest(Position pos, Type type);
};

#endif // MAP_H
