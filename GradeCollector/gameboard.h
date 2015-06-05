#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <random>
#include <chrono>
#include <QTimer>
#include <iostream>


namespace Ui {
class GameBoard;
}
/** @class GameBoard
 * @brief class that creates a game board.
 * @details it creates a game board where the user could move around the board and munch letter grades..
 */
class GameBoard : public QWidget
{
    Q_OBJECT

public slots:
       void updateFs();

signals:
       void game_over();

public:
    explicit GameBoard(QWidget *parent = 0, size_t board_size = 10, size_t f_speed = 10, size_t number_of_fs= 1);
    ~GameBoard();

       void keyPressEvent(QKeyEvent *event);
       void paintEvent(QPaintEvent *e);
       void showEvent(QShowEvent *e);

       void munchGrade(int x, int y);
       void updateStudent(int px, int py, int nx, int ny);
       void updateAfterMunch(bool flag);
       bool isValidMunch(int x, int y);

       int getStudentScore(){return number_of_fs;}

private:
    Ui::GameBoard *ui;

    //STUDENT VARIABLE
    const QPixmap* student_image;
    QPoint *student_position;
    int student_score;

    //LETTER GRADES' IMAGES
    QPixmap* a_image;
    QPixmap* b_image;
    QPixmap* c_image;
    QPixmap* d_image;

    //F VARIABLE
    QPixmap* f_image;
    QPoint *f_positions;
    size_t number_of_fs;

    QWidget* Top;
    unsigned int lives_remaining;
    QLabel** lives;

    // Board Variables
    QWidget *Board;
    size_t board_size;
    size_t f_speed;
    QLabel** labels;
    int* values;
};


#endif // GAMEBOARD_H

