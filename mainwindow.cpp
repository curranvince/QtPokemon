#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow)
    , paused_(false), onMainMenu_(true)
{
    ui_->setupUi(this);

    pauseMenu_ = ui_->pauseMenuWid;
    pauseMenu_->hide();

    partyMenu_ = ui_->partyMenu;
    partyMenu_->hide();

    // the QGraphicsView is the UI element that contains the
    // scene that we will actually get to draw on
    QGraphicsView *view = ui_->graphicsView;
    scene_ = new QGraphicsScene;
    view->setScene(scene_);
    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    ShowScreen(0); // show main menu

    /* add map & player to game view */
    gameManager_ = new GameManager();
    for (Tile* t : gameManager_->GetMapTiles()) { scene_->addItem(t); }
    scene_->addItem(gameManager_->GetPlayer());
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::Unpause() {
    pauseMenu_->hide();
    paused_ = false;
}

void MainWindow::ShowScreen(int index) { ui_->stackedWidget->setCurrentIndex(index); }

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!onMainMenu_) {
        Direction dir = Direction::NONE;
        switch (event->key()) {
            case Qt::Key_Tab:
                if (ui_->stackedWidget->currentIndex() == 1) {
                    if (!paused_) pauseMenu_->show();
                    else pauseMenu_->hide();
                    paused_ = !paused_;
                }
                break;
            case Qt::Key_W:
                dir = Direction::kNorth;
                break;
            case Qt::Key_A:
                dir = Direction::kWest;
                break;
            case Qt::Key_S:
                dir = Direction::kSouth;
                break;
            case Qt::Key_D:
                dir = Direction::kEast;
                break;
        }

        if (!paused_ && dir != Direction::NONE)
            gameManager_->MovePlayer(dir);
    }
}

void MainWindow::on_newGameButton_clicked() {
    ShowScreen(1);
    onMainMenu_ = false;
}

void MainWindow::on_mainMenuButton_clicked() {
    Unpause();
    ShowScreen(0);
    onMainMenu_ = true;
}

void MainWindow::on_resumeButton_clicked() { Unpause(); }

void MainWindow::on_quitButton_clicked() { exit(0); }

void MainWindow::on_quitButton2_clicked() { exit(0); }

void MainWindow::on_partyBackButton_clicked() {
    partyMenu_->hide();
    pauseMenu_->show();
}

void MainWindow::on_partyButton_clicked() {
    UpdatePartyMenu();
    pauseMenu_->hide();
    partyMenu_->show();
}

/* please refactor me */
void MainWindow::UpdatePartyMenu() {
    std::vector<Pokemon*> party = gameManager_->GetPlayer()->GetParty();

    ui_->name1->setText(QString::fromStdString(party.at(0)->GetName()));
    std::string hpStr = "HP: " + std::to_string(party.at(0)->GetHP()) + " / " + std::to_string(party.at(0)->GetMaxHP());
    ui_->hp1->setText(QString::fromStdString(hpStr));
    ui_->lvl1->setText(QString::fromStdString("Lvl: " + std::to_string(party.at(0)->GetLevel())));

    if (party.size() > 1) {
        ui_->name2->setText(QString::fromStdString(party.at(1)->GetName()));
        hpStr = "HP: " + std::to_string(party.at(1)->GetHP()) + " / " + std::to_string(party.at(1)->GetMaxHP());
        ui_->hp2->setText(QString::fromStdString(hpStr));
        ui_->lvl2->setText(QString::fromStdString("Lvl: " + std::to_string(party.at(0)->GetLevel())));
        ui_->active2->setVisible(true);
    } else {
        ui_->name2->setText("");
        ui_->hp2->setText("");
        ui_->lvl2->setText("");
        ui_->active2->setVisible(false);
    }

    if (party.size() > 2) {
        ui_->name3->setText(QString::fromStdString(party.at(2)->GetName()));
        hpStr = "HP: " + std::to_string(party.at(2)->GetHP()) + " / " + std::to_string(party.at(2)->GetMaxHP());
        ui_->hp3->setText(QString::fromStdString(hpStr));
        ui_->lvl3->setText(QString::fromStdString("Lvl: " + std::to_string(party.at(2)->GetLevel())));
        ui_->active3->setVisible(true);
    } else {
        ui_->name3->setText("");
        ui_->hp3->setText("");
        ui_->lvl3->setText("");
        ui_->active3->setVisible(false);
    }

    if (party.size() > 3) {
        ui_->name4->setText(QString::fromStdString(party.at(3)->GetName()));
        hpStr = "HP: " + std::to_string(party.at(3)->GetHP()) + " / " + std::to_string(party.at(3)->GetMaxHP());
        ui_->hp4->setText(QString::fromStdString(hpStr));
        ui_->lvl4->setText(QString::fromStdString("Lvl: " + std::to_string(party.at(3)->GetLevel())));
        ui_->active4->setVisible(true);
    } else {
        ui_->name4->setText("");
        ui_->hp4->setText("");
        ui_->lvl4->setText("");
        ui_->active4->setVisible(false);
    }

    if (party.size() > 4) {
        ui_->name5->setText(QString::fromStdString(party.at(4)->GetName()));
        hpStr = "HP: " + std::to_string(party.at(4)->GetHP()) + " / " + std::to_string(party.at(4)->GetMaxHP());
        ui_->hp5->setText(QString::fromStdString(hpStr));
        ui_->lvl5->setText(QString::fromStdString("Lvl: " + std::to_string(party.at(4)->GetLevel())));
        ui_->active5->setVisible(true);
    } else {
        ui_->name5->setText("");
        ui_->hp5->setText("");
        ui_->lvl5->setText("");
        ui_->active5->setVisible(false);
    }

    if (party.size() > 5) {
        ui_->name6->setText(QString::fromStdString(party.at(5)->GetName()));
        hpStr = "HP: " + std::to_string(party.at(5)->GetHP()) + " / " + std::to_string(party.at(5)->GetMaxHP());
        ui_->hp6->setText(QString::fromStdString(hpStr));
        ui_->lvl6->setText(QString::fromStdString("Lvl: " + std::to_string(party.at(5)->GetLevel())));
        ui_->active6->setVisible(true);
    } else {
        ui_->name6->setText("");
        ui_->hp6->setText("");
        ui_->lvl6->setText("");
        ui_->active6->setVisible(false);
    }
}

void MainWindow::on_active2_clicked() {
    gameManager_->GetPlayer()->SetActive(1);
    UpdatePartyMenu();
}

void MainWindow::on_active3_clicked() {
    gameManager_->GetPlayer()->SetActive(2);
    UpdatePartyMenu();
}

void MainWindow::on_active4_clicked() {
    gameManager_->GetPlayer()->SetActive(3);
    UpdatePartyMenu();
}

void MainWindow::on_active5_clicked() {
    gameManager_->GetPlayer()->SetActive(4);
    UpdatePartyMenu();
}

void MainWindow::on_active6_clicked() {
    gameManager_->GetPlayer()->SetActive(5);
    UpdatePartyMenu();
}
