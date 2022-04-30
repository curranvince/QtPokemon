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

    Type GetTileType(Position pos) { return tiles_.at(pos)->GetType(); }
    std::vector<Tile*> GetAllTiles();

};

#endif // MAP_H
