#include "map.h"

#include <iostream>

#include <QFile>

Map::Map()
{
    // read in the map file
    // at each character, create a new tile and add it to the map
    QFile file(":/data/pokemap2.csv");

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Unable to open map file, exiting\n";
        exit(-1);
    }

    Tile::InitializePixmap();

    Type type = Type::kLand;
    int row, col;
    row = col = 0;

    std::string line;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        for (unsigned int i = 0; i < line.length(); i++) {
            switch (line[i].toLatin1()) {
                case '0':
                    type = Type::kLand;
                    break;
                case '1':
                    type = Type::kWater;
                    break;
                case '2':
                    type = Type::kPokeCenter;
                    break;
                case '3':
                    type = Type::kPokeGym;
                    break;
            }

            if (line[i] != ',') {
                tiles_.emplace(Position(row, col), new Tile(type, Position(row , col)));
                row++;
            }
        }
        col++;
        row = 0;
    }

    file.close();
}

/* Adapted from: https://stackoverflow.com/questions/8483985/obtaining-list-of-keys-and-values-from-unordered-map */
std::vector<Tile*> Map::GetAllTiles() const {
    std::vector<Tile*> tiles;
    tiles.reserve(tiles_.size());

    for (auto& t : tiles_) {
        tiles.push_back((t.second));
    }

    return tiles;
}

bool Map::CheckAdjTileValid(Position pos, Direction dir) const {
    Position adjPos = pos;
    switch (dir) {
        case Direction::NONE:
            break;
        case Direction::kSouth:
            adjPos.y_ += 1;
            break;
        case Direction::kNorth:
            adjPos.y_ -= 1;
            break;
        case Direction::kEast:
            adjPos.x_ += 1;
            break;
        case Direction::kWest:
            adjPos.x_ -= 1;
            break;
    }

    if (adjPos.x_ < 0 || adjPos.y_ < 0 || adjPos.x_ > 15 || adjPos.y_ > 24)
        return false;

    return tiles_.at(adjPos)->GetType() != Type::kWater;
}

/* using distance formula to find the nearest tile of a certain type */
Position Map::FindNearest(Position pos, Type type) const {
    int min_dist = INT_MAX;
    Position closest_pos(-1,-1);
    for (auto& t : tiles_) {
        if (t.second->GetType() == type) {
            float dist = std::sqrt(std::pow((t.first.x_-pos.x_), 2) + std::pow((t.first.y_-pos.y_), 2));
            if (dist < min_dist) {
                min_dist = dist;
                closest_pos = t.first;
            }
        }
    }
    return closest_pos;
}
