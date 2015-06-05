#include "gameboard.h"
#include "mainwindow.h"
#include "ui_gameboard.h"
#include <QPushButton>
//#include <QMediaPlayer>

//Sets up the seed and creates the random number generator
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);

//CONSTRUCTOR
/**
 * @brief GameBoard constructor
 * @details This constructs the board for the game.
 * @param parent is the widget on which the board will be created.
 * @param board_sz is the size of the board.
 * @param f_spd is the speed at which the grade letter F will be moving accross the board.
 */
GameBoard::GameBoard(QWidget *parent, size_t board_sz, size_t f_spd, size_t num_of_f) :
    QWidget(parent),
    ui(new Ui::GameBoard), board_size(board_sz), f_speed(f_spd), number_of_fs(num_of_f)
{
    //ui->setupUi(this);

    //CREATES THE IMAGE FILES
    QString studentFileName(":/Images/student.jpg");
    student_image = new QPixmap(studentFileName);

    QString a_filename(":/Images/A_grade.jpg");
    a_image = new QPixmap(a_filename);

    QString b_filename(":/Images/B_grade.jpg");
    b_image = new QPixmap(b_filename);

    QString c_filename(":/Images/c_grade.jpg");
    c_image = new QPixmap(c_filename);

    QString d_filename(":/Images/D_grade.jpg");
    d_image = new QPixmap(d_filename);

    QString f_filename(":/Images/F_grade.jpg");
    f_image = new QPixmap(f_filename);

 /*  Adds sound to game
    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Images/Gorillaz Dare.mp3"));
    music->play();
*/
    Top = new QWidget;
    Top->setStyleSheet("QLabel { background-color : black; color : white; }");

    // This layout will space out the elements above
    QHBoxLayout *top_bar = new QHBoxLayout(Top);

    lives_remaining = 4;
    lives = new QLabel*[lives_remaining-1];

    //Puts the student image at the top of the bar
    for(size_t i=0;i<lives_remaining-1;i++) {
        lives[i] = new QLabel;
        lives[i]->setPixmap(*student_image);
        lives[i]->setMinimumSize(40,40);
        lives[i]->setMaximumSize(40,40);
        lives[i]->setScaledContents(true);
        top_bar->addWidget(lives[i]);
    }


    // Add in some horizontal space before next labels
    QSpacerItem* horizontal_space = new QSpacerItem(10,10);

    top_bar->addSpacerItem(horizontal_space);


//    QSpacerItem* horizontal_space_2 = new QSpacerItem(*horizontal_space);
  //  top_bar->addSpacerItem(horizontal_space_2);

    // This code Creates the Board
    Board = new QWidget;
    labels = new QLabel*[board_size*board_size];
    values = new int[board_size*board_size];
    QGridLayout *SquareGrid = new QGridLayout(Board);

    SquareGrid->setGeometry(QRect());
    SquareGrid->setSpacing(0);

    //Random Number Generator- it generates random numbers from 1-4.
    std::uniform_int_distribution<int> distribution(1,4);


    // Create each label for the board, initialize with random value which is assigned to a letter grade.
    for(size_t i=0;i<board_size;i++) {
        for(size_t j=0;j<board_size;j++) {

            // Random values between [1,4]
            values[i*board_size+j] = distribution(generator);

            // Create grid labels and puts letter grade image correspondingly
            labels[i*board_size+j] = new QLabel;
            if(values[i*board_size+j]==4){
                labels[i*board_size+j]->setPixmap(*a_image);
                labels[i*board_size+j]->setMinimumSize(40,40);
                labels[i*board_size+j]->setMaximumSize(40,40);
                labels[i*board_size+j]->setScaledContents(true);
            }
            else if(values[i*board_size+j]==3){
                labels[i*board_size+j]->setPixmap(*b_image);
                labels[i*board_size+j]->setMinimumSize(40,40);
                labels[i*board_size+j]->setMaximumSize(40,40);
                labels[i*board_size+j]->setScaledContents(true);
            }
            else if(values[i*board_size+j]==2){
                labels[i*board_size+j]->setPixmap(*c_image);
                labels[i*board_size+j]->setMinimumSize(40,40);
                labels[i*board_size+j]->setMaximumSize(40,40);
                labels[i*board_size+j]->setScaledContents(true);
            }
            else if(values[i*board_size+j]==1){
                labels[i*board_size+j]->setPixmap(*d_image);
                labels[i*board_size+j]->setMinimumSize(40,40);
                labels[i*board_size+j]->setMaximumSize(40,40);
                labels[i*board_size+j]->setScaledContents(true);
            }

            labels[i*board_size+j]->setFrameStyle(15);
            labels[i*board_size+j]->setAlignment(Qt::AlignCenter);

            // Add label to the layout
            SquareGrid -> addWidget(labels[i*board_size+j] ,i,j);

        }
    }

    // Initialize the student at the top left corner, coordinate (0,0).
    student_position = new QPoint(0,0);
    labels[0]->setPixmap(*student_image);
    labels[0]->setScaledContents(true);

    Board->setFixedSize(400,400);


    //Fixes the size of the widget
    setFixedSize(500,550);

    //Pieces the top bar and the board together

      // Create a vertical box layout for the two pieces
      QVBoxLayout *piece_together = new QVBoxLayout;

      piece_together->addWidget(Top,0,Qt::AlignCenter);
      piece_together->addWidget(Board,0,Qt::AlignCenter);

      QPushButton* quit = new QPushButton("Quit");
      quit->setStyleSheet("QPushButton {color: white}");
      QObject::connect(quit, SIGNAL(clicked()), parent, SLOT(game_over()));

      piece_together->addWidget(quit);

      this->setLayout(piece_together);
      this->setStyleSheet("QLabel { background-color : yellow; color : white; }");

      //Creates the roaming F's
      //number_of_fs = 4;
      f_positions = new QPoint[number_of_fs];

      for(size_t i=0; i< number_of_fs; ++i){
          if(i%2==0){
              f_positions[i].setX(-1);
          }
          else{
              f_positions[i].setX(board_size);
          }
          f_positions[i].setY(distribution(generator)%board_size);

      }

      QTimer *timer = new QTimer(this);
      connect(timer, SIGNAL(timeout()), this, SLOT(updateFs()));
      timer->start(f_speed);

      connect(this, SIGNAL(game_over()), parent, SLOT(game_over()));

}


/**
 * @brief GameBoard::~GameBoard
 * @details GameBoard deconstructor- it deallocates the memory that was used.
 */
GameBoard::~GameBoard()
{
    delete [] values;
    delete [] f_positions;
    delete [] student_position;

    delete ui;
}

/**
 * @brief GameBoard::keyPressEvent
 * @details It identifies if the left,right,up,down, or spacebar keys were pressed and calls the updateStudent
 * and munchGrade function.
 * @param event records the key from the keyboard that was pressed.
 */
void GameBoard::keyPressEvent(QKeyEvent *event){

    int x = student_position->rx();
    int y = student_position->ry();

    switch (event->key()) {
    case Qt::Key_Left:
        if(student_position->rx() != 0)
            updateStudent(x,y,x-1,y);

        break;
    case Qt::Key_Right:
        if(student_position->rx() != board_size-1)
            updateStudent(x,y,x+1,y);

        break;
    case Qt::Key_Up:
        if(student_position->ry() != 0)
            updateStudent(x,y,x,y-1);

        break;
    case Qt::Key_Down:
        if(student_position->ry() != board_size-1)
            updateStudent(x,y,x,y+1);

        break;

    case Qt::Key_Space:
        munchGrade(x,y);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
    return;
}

/**
 * @brief GameBoard::paintEvent
 * @details It sets the images(student and letter F) on their respective(current) location on the board.
 * @param e
 */
void GameBoard::paintEvent(QPaintEvent *e) {

    int x = student_position->rx();
    int y = student_position->ry();

    labels[y*board_size+x]->setPixmap(*student_image);
    labels[y*board_size+x]->setScaledContents(true);

    for(size_t i=0;i<number_of_fs;i++) {
        int px = f_positions[i].rx();
        int py = f_positions[i].ry();

        if(px >= 0 && py >= 0 && px < (int)board_size && py < (int)board_size) {
            labels[py*board_size+px]->setPixmap(*f_image);
            labels[py*board_size+px]->setScaledContents(true);
        }
    }


}

/**
 * @brief GameBoard::showEvent
 * @details Sets the board as the main/active window and displays it
 * @param e
 */
void GameBoard::showEvent(QShowEvent *e) {

    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}

/**
 * @brief GameBoard::updateStudent
 * @details It updates the position of the student on the board.
 * @param px is the previous x-coordinate of the student's location on the board.
 * @param py is the previous y-coordinate of the student's location on the board.
 * @param nx is the new x-coordinate of the student's location on the board.
 * @param ny is the new y-coordinate of the student's location on the board.
 */
void GameBoard::updateStudent
(int px, int py, int nx, int ny) {
    labels[py*board_size+px]->clear();
    if(values[py*board_size+px]==4){
        labels[py*board_size+px]->setPixmap(*a_image);
    }
    else if(values[py*board_size+px]==3){
        labels[py*board_size+px]->setPixmap(*b_image);
    }
    else if(values[py*board_size+px]==2){
        labels[py*board_size+px]->setPixmap(*c_image);
    }
    else if(values[py*board_size+px]==1){
        labels[py*board_size+px]->setPixmap(*d_image);
    }

    student_position->setX(nx);
    student_position->setY(ny);

}

bool GameBoard::isValidMunch(int x, int y) {

    if( values[y*board_size+x])
        return true;

    return false;
}

/**
 * @brief GameBoard::munchGrade
 * @details It allows the student to munch the letter grade on the board.
 * @param x is the x-coordinate
 * @param y is the y-coordinate
 */
void GameBoard::munchGrade(int x, int y){

    if(values[y*board_size+x]){
        //updateScore(true);
        student_score += values[y*board_size+x];
        values[y*board_size+x] = 0;
        //return true;
    }
    //else{
        //updatScore(false);
      //  return false;
    //}
}


/*
void GameBoard::updateScore(bool flag){
    int x = student_position->rx();
    int y = student_position->ry();
    if(flag){
        student_score += values[y*board_size+x];
        values[y*board_size+x] = 0;
    }
}*/


/**
 * @brief GameBoard::updateAfterMunch
 * @details It updates the
 * @param flag will determine
 */
void GameBoard::updateAfterMunch(bool flag) {
    int x = student_position->rx();
    int y = student_position->ry();

    if(flag){
        values[y*board_size+x] = 0;
        //labels[y*board_size+x]
    }
    else {
        values[y*board_size+x] = 0;
        if(lives_remaining > 1) {
            lives_remaining--;
            lives[lives_remaining-1]->clear();
        }
        else {
            this->game_over();
            // Game Over
        }
    }
}

/**
 * @brief It updates the location of the F's
 * @details It randomly updates the location of the F's around the game board.
 */
void GameBoard::updateFs() {

    std::uniform_real_distribution<double> p(0,1);
    std::uniform_int_distribution<int> x_or_y(0,1);
    std::uniform_int_distribution<int> increment(0,1);

    for(size_t i=0;i<number_of_fs;i++) {

        int px = f_positions[i].rx();
        int py = f_positions[i].ry();

        if(px>=0 && py >= 0 && px<(int)board_size && py<(int)board_size) {
            labels[py*board_size+px]->clear();

            if(values[py*board_size+px]==4){
                labels[py*board_size+px]->setPixmap(*a_image);
            }
            else if(values[py*board_size+px]==3){
                labels[py*board_size+px]->setPixmap(*b_image);
            }
            else if(values[py*board_size+px]==2){
                labels[py*board_size+px]->setPixmap(*c_image);
            }
            else if(values[py*board_size+px]==1){
                labels[py*board_size+px]->setPixmap(*d_image);
            }
        }

        int nx = px;
        int ny = py;

        // Moves the specific F around the board
        if(p(generator) < 0.1) {

            if(x_or_y(generator) == 0) {
                nx = px + 2*increment(generator)-1;
                if(nx >= -1 && nx <= (int)board_size)
                    f_positions[i].setX(nx);
            }
            else {
                ny = py + 2*increment(generator)-1;
                if(ny >= -1 && ny <= (int)board_size)
                    f_positions[i].setY(ny);

            }

        }

    }

    repaint();
    QCoreApplication::processEvents();

}
