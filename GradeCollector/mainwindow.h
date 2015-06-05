#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"


namespace Ui {
class MainWindow;
}

/** @class MainWindow
 * @brief class for the main window of game
 * @details it displays buttons to select the level of game play.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void easy_game_begin();
    void medium_game_begin();
    void hard_game_begin();
    void game_play();

    void game_over();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameBoard* board;
};

#endif // MAINWINDOW_H
