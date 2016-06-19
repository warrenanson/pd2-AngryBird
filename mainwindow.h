#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <QString>
#include <QMediaPlayer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>

#include <gameitem.h>
#include <land.h>
#include <background.h>
#include <bird.h>
#include <bird_big.h>
#include <bird_black.h>
#include <bird_yellow.h>
#include <barrier.h>
#include <pig.h>
#include <life.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void setGame();
signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void deleteitem();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QMediaPlayer *player;

    Bird *birdie;
    Bird *birdBig;
    Bird *birdBlack;
    Bird *birdYellow;

    QList<Barrier *> BarrierList;
    QList<Pig *> PigList;

    float32 x_final,y_final;
    float32 x_move,y_move;
    float32 x_end,y_end;

    bool shoot = false;
    bool fire = false;

    int count = 1;
    int pignum = 5;
    int score = 0;
};

#endif // MAINWINDOW_H
