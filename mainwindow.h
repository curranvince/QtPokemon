#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "map.h"
#include "gamemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    // mainwindow must have the ui and scene so we can access buttons and draw the game
    Ui::MainWindow *ui_;
    QGraphicsScene *scene_;

    QWidget *pauseMenu_;
    QWidget *partyMenu_;

    GameManager* gameManager_;

    bool paused_;
    bool onMainMenu_;

    void Unpause();
    void ShowScreen(int index);
    void UpdatePartyMenu();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newGameButton_clicked();
    void on_quitButton_clicked();
    void on_quitButton2_clicked();
    void on_mainMenuButton_clicked();
    void on_resumeButton_clicked();
    void on_partyButton_clicked();
    void on_partyBackButton_clicked();
    void on_active2_clicked();
    void on_active3_clicked();
    void on_active4_clicked();
    void on_active5_clicked();
    void on_active6_clicked();
};

#endif // MAINWINDOW_H
