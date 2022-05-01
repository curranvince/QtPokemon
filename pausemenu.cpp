#include "pausemenu.h"
#include "ui_pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PauseMenu)
{
    ui->setupUi(this);
}

PauseMenu::~PauseMenu()
{
    delete ui;
}
