#include "gamemanager.h"

#include <cmath>

#include "pokemondatabase.h"

GameManager::GameManager() : currentBattlePos_(Position(-1, -1))
{
    map_ = new Map();
    player_ = new Player(PokemonDatabase::Instance().CreatePokemon(1));

    combatWindow_ = new CombatWindow(player_);
    connect(combatWindow_, SIGNAL(CombatOver(bool)), this, SLOT(CombatOver_slot(bool)));
    combatWindow_->hide();

    /* create trainers */
    for (auto tile : GetMapTiles()) {
        if (tile->GetType() == Type::kPokeGym) {
            trainers_.emplace(tile->GetPosition(), new Trainer());
        }
    }

    /* scatter wild pokemon */
    std::vector<Position> usedPos;
    for (int i = 0; i < kNumWildPokemon; i++) {
        /* only place wild pokemon on grass tiles which do not already have a wild pokemon */
        Position pos = {-1,-1};
        do {
            pos = Position(Utility::Instance().GetRandom(0, 15), Utility::Instance().GetRandom(0, 24));
        } while (pos.x_ != -1 && !std::count(usedPos.begin(), usedPos.end(), pos) && pos != player_->GetPosition() && map_->CheckTileType(pos) != Type::kLand);
        usedPos.push_back(pos);
        wildPokemon_.emplace(pos, PokemonDatabase::Instance().CreateRandomPokemon());
    }
}

GameManager::~GameManager() {}

void GameManager::MovePlayer(Direction &dir) {
    /* move the player */
    if  (CheckTileValidity(player_->GetPosition(), dir)) {
        player_->Move(dir);
        /* handle landing on different tile types */
        switch (map_->CheckTileType(player_->GetPosition())) {
            case Type::kLand: {
                /* check if landed near a wild pokemon */
                std::pair<Position, Pokemon*>* pair = CheckForWild(player_->GetPosition());
                if (pair != nullptr) {
                    StartBattle(pair);
                 }
                delete pair;
                break;
            }
            case Type::kPokeGym: {
                /* fight a trainer if we havent beat the gym at this tile yet */
                if (!trainers_.at(player_->GetPosition())->defeated_) {
                    StartBattle(trainers_.at(player_->GetPosition()));
                }
                break;
            }
            case Type::kPokeCenter: {
                RunPokeCenter();
                break;
            }
            case Type::kWater: {
                break; // handle this case to remove warning
            }
        }
    }
}

/* see if a wild pokemon is in range of the given position */
/* return pokemon & its position, or nullptr if nothing found */
std::pair<Position, Pokemon*>* GameManager::CheckForWild(Position pos) {
    for (const auto &wild : wildPokemon_) {
        if (std::abs(pos.x_ - wild.first.x_) <= 2 && std::abs(pos.y_ - wild.first.y_) <= 2) {
            return new std::pair<Position, Pokemon*>(wild.first, wild.second);
        }
    }
    return nullptr;
}

void GameManager::StartBattle(std::pair<Position, Pokemon*>* pair) {
    currentBattlePos_ = pair->first;
    combatWindow_->SetOpponent(pair->second);
    combatWindow_->show();
}

void GameManager::StartBattle(Trainer* trainer) {
    combatWindow_->SetOpponent(trainer);
    combatWindow_->show();
}

void GameManager::RunPokeCenter() {
    player_->HealAll();
    // TO DO show pokedex & allow player to swap out party
}

/* based off combat outcome: capture pokemon, get a badge, or teleport to nearest PokeCenter */
void GameManager::CombatOver_slot(bool won) {
    if (won) {
        if (combatWindow_->battleType_ == BattleType::kWild) {
            player_->AddPokemon(new Pokemon(combatWindow_->GetOpponent()));
            wildPokemon_.erase(currentBattlePos_);
        } else if (combatWindow_->battleType_ == BattleType::kTrainer) {
            player_->BeatGym();
            trainers_.erase(player_->GetPosition());
        }
    } else {
        /* teleport to nearest poke center */
        qDebug() << "going to poke center";
        player_->Move(map_->FindNearest(player_->GetPosition(), Type::kPokeCenter));
        RunPokeCenter();
    }

    combatWindow_->battleType_ = BattleType::NONE;
    combatWindow_->hide();
}
