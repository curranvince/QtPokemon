#ifndef COMBATWINDOW_H
#define COMBATWINDOW_H

#include <QFrame>
#include <QTimer>

#include "battlesprite.h"
#include "player.h"
#include "trainer.h"

enum class BattleType {
    NONE,
    kWild,
    kTrainer
};

namespace Ui {
class CombatWindow;
}

class CombatWindow : public QFrame
{
    Q_OBJECT

private:
    Ui::CombatWindow *ui_;
    QGraphicsScene *scene_;

    QTimer *writeTimer_;

    BattleSprite* battleSprites[2];

    Player *player_;
    Trainer *opponent_;
    Pokemon *activeOpponent_;

    std::string currentDialogue_;
    std::string dialogue_;

    void Setup();
    void ShowScreen(int index);
    void UpdateDialogue();
    void ClearDialogue();
    void UpdateHealthBars();

    bool TryToCatch();
    bool DoAttack(Pokemon* attacker, Pokemon* defender); // returns true if the defender dies

    void HandlePlayerFaint();
    void HandleOpponentFaint();
    void AttemptTrainerSwitch();

public:
    BattleType battleType_;

    CombatWindow(Player *player);
    ~CombatWindow();

    void SetOpponent(Pokemon* pokemon);
    void SetOpponent(Trainer* trainer);

    Pokemon* GetOpponent() { return activeOpponent_; }
    Trainer* GetTrainer() { return opponent_; }

signals:
    void CombatOver(bool won);
    void ShowPartyMenu();

private slots:
    /* main combat menu button clicks */
    void on_fightButton_clicked();
    void on_inventoryButton_clicked();
    void on_switchButton_clicked();
    void on_runButton_clicked();
    /* attack menu button clicks */
    void on_attack1Button_clicked();
    void on_backButton_clicked();
    /* inventory menu button clicks */
    void on_pokeballButton_clicked();

public slots:
    void EnableButtons_slot();

};

#endif // COMBATWINDOW_H
