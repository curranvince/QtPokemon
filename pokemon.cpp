#include "pokemon.h"

void Pokemon::LevelUp() {
    if (level_ < kMaxLevel) {
        level_++;
        hp_ += std::ceil(0.2 * kBaseHP);
        maxHP_ += std::ceil(0.2 * kBaseHP);
        speed_ += std::ceil(0.2 * kBaseSpeed);
        attack_ = (attack_ + std::ceil(0.2 * kBaseAttack)) > kMaxAD ? kMaxAD : (attack_ + std::ceil(0.2 * kBaseAttack));
        defense_ = (defense_ + std::ceil(0.2 * kBaseDefense)) > kMaxAD ? kMaxAD : (defense_ + std::ceil(0.2 * kBaseDefense));
    }
}
