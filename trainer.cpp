#include "trainer.h"

#include "utility.h"

Trainer::Trainer() : kName("Trainer"), defeated_(false)
{
    int numPokemon = Utility::Instance().GetRandom(1, 6);
    for (int i = 0; i < numPokemon; i++) {
        party_.push_back(PokemonDatabase::Instance().CreatePokemon(Utility::Instance().GetRandom(1, 151)));
    }

    activePokemon_ = party_.at(0);
}

bool Trainer::NextPokemon() {
    for (unsigned int i = 0; i < party_.size(); i++) {
        if (party_.at(i)->GetHP() > 0) {
            activePokemon_ = party_.at(i);
            return true;
        }
    }
    return false;
}
