#include "pokemon.h"

void Pokemon::LevelUp() {
    if (level_ < kMaxLevel) {
        level_++;
        hp_ += std::ceil(0.2 * kBaseHP);
        speed_ += std::ceil(0.2 * kBaseSpeed);
        if (attack_ < kMaxAD) attack_ += std::ceil(0.2 * kBaseAttack);
        if (defense_ < kMaxAD) defense_ += std::ceil(0.2 * kBaseDefense);
    }
}
