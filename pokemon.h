#ifndef POKEMON_H
#define POKEMON_H

#include <string>

#include "utility.h"

class Pokemon
{

private:
    static const int kMaxLevel = 100;

    const float kMaxHP;
    const int kMaxAD;

    const int kBaseHP;
    const int kBaseAttack;
    const int kBaseDefense;
    const int kBaseSpeed;

    const int id_;
    const std::string name_;
    const std::string type1_;
    const std::string type2_;

    float hp_;
    int level_, attack_, defense_, speed_;

public:
    Pokemon(int nID, std::string nName, float nMaxHP, int nAttack, int nDefense, int nSpeed, int nMaxAD, std::string nType1, std::string nType2)
        : kMaxHP(nMaxHP), kMaxAD(nMaxAD), kBaseHP(nMaxHP), kBaseAttack(nAttack), kBaseDefense(nDefense), kBaseSpeed(nSpeed)
        , id_(nID), name_(nName), type1_(nType1), type2_(nType2), hp_(nMaxHP), attack_(nAttack), defense_(nDefense), speed_(nSpeed) {}

    int GetID() const { return id_; }
    int GetAttackValue() const { return Utility::Instance().GetRandom(0, attack_); }
    int GetDefenseValue() const { return Utility::Instance().GetRandom(0, defense_); }

    void Damage(int dmg) { hp_ -= dmg; }
    void Heal() { hp_ = kMaxHP; }
    void LevelUp();

};

#endif // POKEMON_H
