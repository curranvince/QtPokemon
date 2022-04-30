#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // mainwindow must have the ui and scene so we can access buttons and draw the game
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;

    Map *map_;

};

#endif // MAINWINDOW_H
