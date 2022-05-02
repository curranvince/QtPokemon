#include "combatwindow.h"
#include "ui_combatwindow.h"

#include <chrono>
#include <thread>

#include <qtconcurrentrun.h>

#include "utility.h"

CombatWindow::CombatWindow(Player *player) :
    QFrame(nullptr),
    ui_(new Ui::CombatWindow),
    player_(player), currentDialogue_(""), dialogue_(""), battleType_(BattleType::NONE)
{
    ui_->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    // the QGraphicsView is the UI element that contains the
    // scene that we will actually get to draw on
    QGraphicsView *view = ui_->combatView;
    scene_ = new QGraphicsScene;
    view->setScene(scene_);
    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());
    scene_->addItem(new QGraphicsPixmapItem(QPixmap(":/img/combat_background.png")));

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff );

    BattleSprite::InitializePixmap();
    battleSprites[0] = new BattleSprite(player->GetActive()->GetID(), true);
    battleSprites[1] = new BattleSprite(player->GetActive()->GetID(), false);
    scene_->addItem(battleSprites[0]);
    scene_->addItem(battleSprites[1]);
    ShowScreen(0);

    writeTimer_ = new QTimer();
}

CombatWindow::~CombatWindow() { delete ui_; }

void CombatWindow::Setup() {
    ShowScreen(0);
    battleSprites[1]->ChangeImage(activeOpponent_->GetID());
    UpdateHealthBars();
    if (player_->pokeballs_ == 0) {
        ui_->pokeballButton->setEnabled(false);
    }
}

void CombatWindow::ShowScreen(int index) { ui_->stackedWidget->setCurrentIndex(index); }

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
                    + "    HP: " + std::to_string((int)std::ceil(player_->GetActive()->GetHP())) + " / " +  std::to_string(player_->GetActive()->GetMaxHP())));
    ui_->opponentActiveLabel->setText(
                QString::fromStdString(
                    activeOpponent_->GetName()
                    + ":\nLvl: " + std::to_string(activeOpponent_->GetLevel())
                    + "    HP: " + std::to_string((int)std::ceil(activeOpponent_->GetHP())) + " / " +  std::to_string(activeOpponent_->GetMaxHP())));
}

bool CombatWindow::DoAttack(Pokemon* attacker, Pokemon* defender) {
    ShowScreen(4);
    float dmg = attacker->GetAttackValue();
    dialogue_ = attacker->GetName() + " deals " + std::to_string((int)std::ceil(dmg)) + " damage " + " to " + defender->GetName() + "\n";
    defender->Damage(dmg);
    bool death = defender->GetHP() <= 0;
    if (death) {
        dialogue_ += defender->GetName() + " has fainted!\n";
        if (defender != player_->GetActive() && battleType_ == BattleType::kWild) {
            dialogue_ += defender->GetName() + " health will be restored, and they will be added to your party or pokedex";
        }
    }

    UpdateDialogue();
    UpdateHealthBars();

    return death;
}

void CombatWindow::ClearDialogue() {
    dialogue_ = "";
    currentDialogue_ = "";
    ui_->dialogueLabel->setText(nullptr);
}

void CombatWindow::HandlePlayerFaint() {
    if (!player_->NextPokemon()) {
        emit CombatOver(false); // player active pokemon death
    } else {
        battleSprites[0]->ChangeImage(player_->GetActive()->GetID());
        UpdateHealthBars();
    }
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
        battleSprites[1]->ChangeImage(activeOpponent_->GetID());
        UpdateHealthBars();
    } else {
        dialogue_ = "Congratulations! You have beat the trainer and earned a badge!";
        UpdateDialogue();
        emit CombatOver(true);
    }
}

void CombatWindow::on_fightButton_clicked() { ShowScreen(1); }

void CombatWindow::on_inventoryButton_clicked() { ShowScreen(3); }

void CombatWindow::on_switchButton_clicked() {
    ui_->switchButton->setEnabled(false);
    ui_->fightButton->setEnabled(false);
    ui_->runButton->setEnabled(false);
    ui_->inventoryButton->setEnabled(false);
    emit ShowPartyMenu();
}

void CombatWindow::on_runButton_clicked() {
    /* TO DO : see what enemy wants to do, then calculate chances of escape */
    emit CombatOver(false);
}

void CombatWindow::on_attack1Button_clicked() {
    ClearDialogue();
    /* TO DO : need to determine if enemy wants to fight or flee */
    bool dies;
    if (player_->GetActive()->GetSpeed() > activeOpponent_->GetSpeed()) {
        /* player attacks first */
        battleSprites[0]->DoAttackAnimation();
        dies = DoAttack(player_->GetActive(), activeOpponent_);
        if (dies) {
            HandleOpponentFaint(); // opponent death
        }
        if (!dies) battleSprites[1]->DoAttackAnimation();
        if (!dies && DoAttack(activeOpponent_, player_->GetActive())) {
            HandlePlayerFaint();
        }
    } else {
        /* opponent attacks first */
        battleSprites[1]->DoAttackAnimation();
        dies = DoAttack(activeOpponent_, player_->GetActive());
        if (dies) {
            HandlePlayerFaint();
        }
        if (!dies) battleSprites[0]->DoAttackAnimation();
        if (!dies && DoAttack(player_->GetActive(), activeOpponent_)) {
            HandleOpponentFaint();
        }
    }
    ShowScreen(0);
}

void CombatWindow::on_backButton_clicked() { ShowScreen(0); }

void CombatWindow::on_pokeballButton_clicked() {
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

void CombatWindow::EnableButtons_slot() {
    ui_->switchButton->setEnabled(true);
    ui_->fightButton->setEnabled(true);
    ui_->runButton->setEnabled(true);
    ui_->inventoryButton->setEnabled(true);
}
