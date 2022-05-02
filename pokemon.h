#ifndef POKEMON_H
#define POKEMON_H

#include <string>

#include "utility.h"

class Pokemon
{

private:
    static const int kMaxLevel = 100;

    const int kMaxAD;

    const int kBaseHP;
    const int kBaseAttack;
    const int kBaseDefense;
    const int kBaseSpeed;

    const int id_;
    const std::string name_;
    const std::string type1_;
    const std::string type2_;

    float hp_, maxHP_;
    int level_, attack_, defense_, speed_;

public:
    Pokemon(int nID, std::string nName, float nMaxHP, int nAttack, int nDefense, int nSpeed, int nMaxAD, std::string nType1, std::string nType2)
        : kMaxAD(nMaxAD), kBaseHP(nMaxHP), kBaseAttack(nAttack), kBaseDefense(nDefense), kBaseSpeed(nSpeed), id_(nID)
        , name_(nName), type1_(nType1), type2_(nType2), hp_(nMaxHP), maxHP_(nMaxHP), level_(1), attack_(nAttack), defense_(nDefense), speed_(nSpeed) {}

    Pokemon(Pokemon* other)
      : kMaxAD(other->kMaxAD), kBaseHP(other->kMaxAD), kBaseAttack(other->attack_), kBaseDefense(other->defense_), kBaseSpeed(other->speed_), id_(other->id_)
      , name_(other->name_), type1_(other->type1_), type2_(other->type2_), hp_(other->maxHP_), maxHP_(other->maxHP_), level_(other->level_), attack_(other->attack_), defense_(other->defense_), speed_(other->speed_) {}

    int GetID() const { return id_; }
    std::string GetName() const { return name_; }
    int GetHP() const { return std::ceil(hp_); }
    int GetMaxHP() const { return (int)maxHP_; }
    int GetLevel() const { return level_; }
    int GetSpeed() const { return speed_; }

    int GetAttackValue() const { return Utility::Instance().GetRandom(0, attack_); }
    int GetDefenseValue() const { return Utility::Instance().GetRandom(0, defense_); }

    void Damage(float dmg) { hp_ -= dmg; }
    void Heal(int amt) { hp_ = ((hp_ + amt) > maxHP_) ? maxHP_ : (hp_ + amt); } // clamp healing to max health amount
    void Heal() { hp_ = maxHP_; }
    void LevelUp();

};

#endif // POKEMON_H
