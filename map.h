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

    std::vector<Tile*> GetAllTiles() const;

    bool CheckAdjTileValid(Position pos, Direction direction) const;
    Type CheckTileType(Position pos) const { return tiles_.at(pos)->GetType(); }

    Position FindNearest(Position pos, Type type) const;
};

#endif // MAP_H
