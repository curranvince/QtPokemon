#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "utility.h"
#include "tile.h"

// custom simple hash table to hold tiles

struct Hnode
{
    // nodes hold a Tile
    Tile* tile_;
    // pointer to next node for chaining collision resolution
    struct Hnode* next_;

    Hnode() : tile_(0), next_(0) {};
    Hnode(Tile* tile) : tile_(tile), next_(0) {};

};

class HashTable
{
    Hnode** table_;

public:
    HashTable();

    void insertTile(Tile* tile);
    int hashFunction(Position pos) const { return (((pos.x*9)+pos.y)%131); };
    Tile* getTile(Position pos) const;

};

#endif // HASHTABLE_H
