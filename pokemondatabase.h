#ifndef POKEMONDATABASE_H
#define POKEMONDATABASE_H

#include "pokemon.h"

#define NUM_POKEMON 151

struct PokemonData {
    int id_;
    std::string name_;
    float hp_;
    int attack_;
    int defense_;
    int speed_;
    int maxAD_;
    std::string type1_;
    std::string type2_;
};

class PokemonDatabase
{

private:
    PokemonDatabase();

    PokemonData* pokemon[NUM_POKEMON];

public:
    static PokemonDatabase& Instance() {
        static PokemonDatabase instance;
        return instance;
    }

    PokemonDatabase(PokemonDatabase const&) = delete;
    void operator=(PokemonDatabase const&)  = delete;

    Pokemon* CreatePokemon(int id) { return new Pokemon(id, pokemon[id-1]->name_, pokemon[id-1]->hp_, pokemon[id-1]->attack_, pokemon[id-1]->defense_, pokemon[id-1]->speed_, pokemon[id-1]->maxAD_, pokemon[id-1]->type1_, pokemon[id-1]->type2_); }
    Pokemon* CreateRandomPokemon() { return CreatePokemon(Utility::Instance().GetRandom(1, NUM_POKEMON)); }
};

#endif // POKEMONDATABASE_H
