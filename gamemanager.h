#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "map.h"
#include "player.h"
#include "trainer.h"
#include "combatwindow.h"

class GameManager : public QObject
{
    Q_OBJECT

private:
    const int kNumWildPokemon = 20;

    CombatWindow* combatWindow_;

    Map* map_;
    Player* player_;

    std::unordered_map<Position, Trainer*, PositionHash> trainers_;
    std::unordered_map<Position, Pokemon*, PositionHash> wildPokemon_;

    Position currentBattlePos_;

    std::pair<Position, Pokemon*>* CheckForWild(Position pos);

    void StartBattle(std::pair<Position, Pokemon*>* pair);
    void StartBattle(Trainer* trainer);

    void RunPokeCenter();

public:
    GameManager();
    ~GameManager();

    Player* GetPlayer() { return player_; }

    std::vector<Tile*> GetMapTiles() { return map_->GetAllTiles(); }
    bool CheckTileValidity(Position pos, Direction dir) { return map_->CheckAdjTileValid(pos, dir); }
    void MovePlayer(Direction dir);

public slots:
    void CombatOver_slot(bool won);

};

#endif // GAMEMANAGER_H
