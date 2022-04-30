#include "pokemondatabase.h"

#include <iostream>

#include <QFile>
#include <QTextStream>

#include "pokemon.h"

PokemonDatabase::PokemonDatabase()
{
    QFile file(":/txt/pokemon.txt");

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Unable to open pokemon data file, exiting\n";
        exit(-1);
    }

    int pokemonNo = 0;

    std::string line;
    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList dataPieces = line.split(",");

        PokemonData *tempData = new PokemonData();
        tempData->id_ = dataPieces.value(0).toInt();
        tempData->name_ = dataPieces.value(1).toStdString();
        tempData->hp_ = dataPieces.value(2).toFloat();
        tempData->attack_ = dataPieces.value(3).toInt();
        tempData->defense_ = dataPieces.value(4).toInt();
        tempData->speed_ = dataPieces.value(5).toInt();
        tempData->maxAD_ = dataPieces.value(6).toInt();
        tempData->type1_ = dataPieces.value(7).toStdString();
        tempData->type2_ = dataPieces.length() > 8 ? dataPieces.value(8).toStdString() : "NONE";

        pokemon[pokemonNo] = tempData;
        pokemonNo++;
    }

    file.close();
}
