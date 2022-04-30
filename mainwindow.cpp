#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

#include "player.h"
#include "pokemondatabase.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // the QGraphicsView is the UI element that contains the
    // scene that we will actually get to draw on.
    QGraphicsView * view = ui_->graphicsView;
    scene_ = new QGraphicsScene;
    view->setScene(scene_);
    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    map_ = new Map();
    for (Tile* t : map_->GetAllTiles()) {
        scene_->addItem(t);
    }

    player_ = new Player(PokemonDatabase::Instance().CreatePokemon(1));
    scene_->addItem(player_);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    Direction dir;
    switch (event->key()) {
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

    if (map_->CheckAdjTileValid(player_->GetPosition(), dir))
        player_->Move(dir);
}
