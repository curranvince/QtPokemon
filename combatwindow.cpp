#include "combatwindow.h"
#include "ui_combatwindow.h"

#include <chrono>
#include <thread>

#include "utility.h"

CombatWindow::CombatWindow(Player *player) :
    QFrame(nullptr),
    ui_(new Ui::CombatWindow),
    player_(player), currentDialogue_(""), dialogue_("")
{
    ui_->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ShowScreen(0);

    writeTimer_ = new QTimer();
}

CombatWindow::~CombatWindow()
{
    delete ui_;
}

void CombatWindow::ShowScreen(int index) { ui_->stackedWidget->setCurrentIndex(index); }

void CombatWindow::on_fightButton_clicked() {
    ShowScreen(1);
}

void CombatWindow::on_backButton_clicked() {
    ShowScreen(0);
}

void CombatWindow::on_runButton_clicked() {
    emit CombatOver(false);
}

void CombatWindow::on_pokeballButton_clicked()
{
    ShowScreen(4);
    ClearDialogue();
    if (player_->pokeballs_ > 0) {
        player_->pokeballs_--;
        ui_->pokeballLabel->setText(QString::fromStdString("Pokeball(s): " + std::to_string(player_->pokeballs_)));
        if (TryToCatch()) {
            emit CombatOver(true);
        } else {
            DoAttack(activeOpponent_, player_->GetActive());
            ShowScreen(0);
        }
    }
}

bool CombatWindow::TryToCatch() {
    dialogue_ = "You throw a pokeball!\n";
    for (int i = 0; i < Utility::Instance().GetRandom(2,4); i++) {
        dialogue_ += "Tick ";
    }
    dialogue_ += "\n";
    bool caught = Utility::Instance().GetRandom(0,99) < 60;
    dialogue_ += caught ? ("The capture is successful!\n" +  activeOpponent_->GetName() + " will be healed and added to your party or PC")
                        : "The capture is unsuccessful!\n";
    UpdateDialogue();
    return caught;
}

void CombatWindow::SetOpponent(Pokemon* pokemon) {
    activeOpponent_ = pokemon;
    battleType_ = BattleType::kWild;
    Setup();
}

void CombatWindow::SetOpponent(Trainer *trainer) {
    opponent_ = trainer;
    activeOpponent_ = opponent_->GetActive();
    battleType_ = BattleType::kTrainer;
    Setup();
}

void CombatWindow::Setup() {
    ShowScreen(0);
    UpdateHealthBars();
    if (player_->pokeballs_ == 0) {
        ui_->pokeballButton->setEnabled(false);
    }
}

void CombatWindow::on_fightBuinventoryButtontton_clicked() { ShowScreen(3); }

void CombatWindow::UpdateDialogue() {
    QEventLoop loop;
    connect(writeTimer_, SIGNAL(timeout()), &loop, SLOT(quit()));
    writeTimer_->start(55);
    for (unsigned int i = 0; i < dialogue_.size(); i++) {
        loop.exec();
        currentDialogue_.push_back(dialogue_.at(i));
        ui_->dialogueLabel->setText(QString::fromStdString(currentDialogue_));
    }

    for (unsigned int i = 0; i < 8; i++) {
        loop.exec();
    }
}

void CombatWindow::UpdateHealthBars() {
    ui_->playerActiveLabel->setText(
                QString::fromStdString(
                    player_->GetActive()->GetName()
                    + ":\nLvl: " + std::to_string(player_->GetActive()->GetLevel())
                    + "    HP: " + std::to_string(player_->GetActive()->GetHP()) + " / " +  std::to_string(player_->GetActive()->GetMaxHP())));
    ui_->opponentActiveLabel->setText(
                QString::fromStdString(
                    activeOpponent_->GetName()
                    + ":\nLvl: " + std::to_string(activeOpponent_->GetLevel())
                    + "    HP: " + std::to_string(activeOpponent_->GetHP()) + " / " +  std::to_string(activeOpponent_->GetMaxHP())));
}

bool CombatWindow::DoAttack(Pokemon* attacker, Pokemon* defender) {
    ShowScreen(4);
    int dmg = attacker->GetAttackValue();
    dialogue_ = attacker->GetName() + " deals " + std::to_string(dmg) + " damage " + " to " + defender->GetName() + "\n";
    defender->Damage(dmg);

    if (defender->GetHP() <= 0) {
        dialogue_ += defender->GetName() + " has fainted!\n";
        if (defender != player_->GetActive() && battleType_ == BattleType::kWild) {
            dialogue_ += defender->GetName() + " health will be restored, and they will be added to your party or pokedex";
        }
    }

    UpdateDialogue();
    UpdateHealthBars();

    return defender->GetHP() <= 0;
}

void CombatWindow::ClearDialogue() {
    dialogue_ = "";
    currentDialogue_ = "";
    ui_->dialogueLabel->setText(nullptr);
}

void CombatWindow::on_attack1Button_clicked()
{
    ClearDialogue();
    bool dies;
    if (player_->GetActive()->GetSpeed() > activeOpponent_->GetSpeed()) {
        /* player attacks first */
        dies = DoAttack(player_->GetActive(), activeOpponent_);
        if (dies) {
            HandleOpponentFaint(); // opponent death
        }
        if (!dies && DoAttack(activeOpponent_, player_->GetActive())) {
            if (!player_->NextPokemon()) emit CombatOver(false); // player active pokemon death
            else UpdateHealthBars();
        }
    } else {
        /* opponent attacks first */
        dies = DoAttack(activeOpponent_, player_->GetActive());
        if (dies) {
            if (!player_->NextPokemon()) emit CombatOver(false);
            else UpdateHealthBars();
        }
        if (!dies && DoAttack(player_->GetActive(), activeOpponent_)) {
            HandleOpponentFaint();
        }
    }
    ShowScreen(0);
}

void CombatWindow::HandleOpponentFaint() {
    if (battleType_ == BattleType::kWild) {
        emit CombatOver(true);
    } else {
        AttemptTrainerSwitch();
    }
}

void CombatWindow::AttemptTrainerSwitch() {
    ClearDialogue();
    if (opponent_->NextPokemon()) {
        activeOpponent_ = opponent_->GetActive();
        dialogue_ = "The trainer has more Pokemon!\nThey now send out " + activeOpponent_->GetName() + "!";
        UpdateDialogue();
        UpdateHealthBars();
    } else {
        dialogue_ = "Congratulations! You have beat the trainer and earned a badge!";
        UpdateDialogue();
        emit CombatOver(true);
    }
}
