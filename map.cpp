#include "map.h"

#include <iostream>

#include <QFile>

Map::Map()
{
    // read in the map file
    // at each character, create a new tile and add it to the map
    QFile file(":/txt/map.txt");

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Unable to open map file, exiting\n";
        exit(-1);
    }

    Type type = Type::kLand;
    int row, col;
    row = col = 0;

    std::string line;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        for (unsigned int i = 0; i < line.length(); i++) {
            switch (line[i].toLatin1()) {
                case 'p':
                    type = Type::kLand;
                    break;
                case 'w':
                    type = Type::kWater;
                    break;
                case 'C':
                    type = Type::kPokeCenter;
                    break;
                case 'G':
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
std::vector<Tile*> Map::GetAllTiles() {
    std::vector<Tile*> tiles;
    tiles.reserve(tiles_.size());

    for (auto& t : tiles_) {
        tiles.push_back((t.second));
    }

    return tiles;
}

