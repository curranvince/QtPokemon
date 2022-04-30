#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gamemanager.h"

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
}

MainWindow::~MainWindow()
{
    delete ui_;
}

