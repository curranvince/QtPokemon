#ifndef TRAINER_H
#define TRAINER_H

#include "pokemondatabase.h"

#include <string>

class Trainer
{

private:
    const std::string kName;

    Pokemon* activePokemon_;
    std::vector<Pokemon*> party_;

public:
    bool defeated_;

    Trainer();

    Pokemon* GetActive() const { return activePokemon_; }

    bool NextPokemon();
};

#endif // TRAINER_H
