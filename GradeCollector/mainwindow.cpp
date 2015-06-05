#include "mainwindow.h"
#include "gameboard.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow constructor
 * @details It creates the main window and displays it.
 * @param parent is the widget that will be passed to the main window to be displayed.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/**
 * @brief It starts the game on easy mode
 */
void MainWindow::easy_game_begin() {
    board = new GameBoard(this,5,100,3);
    this->setCentralWidget(board);
}

/**
 * * @brief It starts the game on medium mode
 */
void MainWindow::medium_game_begin() {
    board = new GameBoard(this,7,50,5);
    this->setCentralWidget(board);
}

/**
 * @brief It starts the game on hard mode
 */
void MainWindow::hard_game_begin() {
    board = new GameBoard(this,10,10,7);
    this->setCentralWidget(board);
}

/**
 * @brief It ends and exits the game.
 */
void MainWindow::game_over() {

    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    // Line above will delete the widget gracefully (no memory errors)

    // Display something which says that you lost, maybe display high score.
    QLabel* label = new QLabel("High score!");
    // labels[py*board_size+px]->setText(QString::number( values[py*board_size+px]));
    //label->setText(QString::number(board->getNumberofF()));
    label->setText(QString::number(board->getStudentScore()));
    label->show();
    // Reset the MainWindow with the initial startup screen
    ui->setupUi(this);


}

/**
 * @brief It provides the user with instructions.
 * @details It creates a new window with the game instructions.
 */
void MainWindow::game_play(){

    QLabel* title = new QLabel("Gameplay");
    title->setStyleSheet("QLabel {background color: black ;color:yellow}");
    //top_title->addWidget(title, 0, Qt::AlignCenter);

    //QVBoxLayout* gameplay = new QVBoxLayout;

    QLabel* inst1 = new QLabel("Use the arrow keys to control the student and move around the board.");
    QLabel* inst2 = new QLabel("Use the space bar to munch the grades.");
    QLabel* inst3 = new QLabel("Try to avoid the roaming F's.");
    QLabel* inst4 = new QLabel("Good luck!");

    //gameplay->addWidget(inst1, 0, Qt::AlignCenter);
    //gameplay->addWidget(inst2, 0, Qt::AlignCenter);
    //gameplay->addWidget(inst3, 0, Qt::AlignCenter);
    //gameplay->addWidget(inst4, 0, Qt::AlignCenter);

    //QWidget* top = new QWidget;
    //QWidget* bottom = new QWidget;

    //top_title->addWidget(top);
    //gameplay->addWidget(bottom);

    QWidget* w = new QWidget;

    QVBoxLayout* together = new QVBoxLayout;
    together->addWidget(title, 0, Qt::AlignCenter);
    together->addWidget(inst1, 0, Qt::AlignCenter);
    together->addWidget(inst2, 0, Qt::AlignCenter);
    together->addWidget(inst3, 0, Qt::AlignCenter);
    together->addWidget(inst4, 0, Qt::AlignCenter);


    w->setLayout(together);
    w->show();
    //label1->show();
    ui->setupUi(this);
}

/**
 * @brief deconstructor of the MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}
