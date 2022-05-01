#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QDockWidget>

namespace Ui {
class PauseMenu;
}

class PauseMenu : public QDockWidget
{
    Q_OBJECT

public:
    explicit PauseMenu(QWidget *parent = nullptr);
    ~PauseMenu();

private:
    Ui::PauseMenu *ui;
};

#endif // PAUSEMENU_H
