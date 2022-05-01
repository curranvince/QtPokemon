#ifndef COMBATWINDOW_H
#define COMBATWINDOW_H

#include <QFrame>
#include <QTimer>

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
    QTimer *writeTimer_;

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

private slots:
    void on_backButton_clicked();
    void on_fightButton_clicked();
    void on_runButton_clicked();
    void on_pokeballButton_clicked();
    void on_fightBuinventoryButtontton_clicked();

    void on_attack1Button_clicked();
};

#endif // COMBATWINDOW_H
