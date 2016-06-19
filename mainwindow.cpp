#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/music/Angry Birds Space Theme Song (FULL).mp3"));
    player->play();
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    world->SetContactListener(new life());
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    itemList.push_back(new Land(16,1.5,32,3,QPixmap(":/image/down.png").scaled(960,90),world,scene));
    itemList.push_back(new background(16,10.5,32,15,QPixmap(":/image/up.png").scaled(960,450),world,scene));
    // Create 彈弓
    QGraphicsPixmapItem *shot = new QGraphicsPixmapItem(QPixmap(":/image/shot.png"));
    shot->setPos(150,360);
    shot->setScale(b2_pi/17);
    scene->addItem(shot);

    setGame();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(deleteitem()));
    timer.start(100/6);
}

void MainWindow::setGame()
{
    // Create bird (You can edit here)
    birdie=new Bird(5.0f,6.0f,0.9f,&timer,QPixmap(":/image/Normal_Bird_1.png").scaled(48,48),world,scene);
    birdie->getBody()->SetActive(0);

    birdYellow=new bird_yellow(4.0f,4.0f,0.9f,&timer,QPixmap(":/image/bird_yellow.png").scaled(48,48),world,scene);
    birdYellow->getBody()->SetActive(0);

    birdBlack=new bird_black(2.5f,4.0f,0.9f,&timer,QPixmap(":/image/bird_black.png").scaled(48,48),world,scene);
    birdBlack->getBody()->SetActive(0);

    birdBig=new bird_big(0.5f,4.5f,1.6f,&timer,QPixmap(":/image/bird_big.png").scaled(96,96),world,scene);
    birdBig->getBody()->SetActive(0);

    itemList.push_back(birdie);
    itemList.push_back(birdBig);
    itemList.push_back(birdBlack);
    itemList.push_back(birdYellow);


    //障礙物
    Barrier *barrier1 =new Barrier(21,4,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,60),world,scene);
    BarrierList.push_back(barrier1);

    Barrier *barrier2 =new Barrier(21,6,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier2);

    Barrier *barrier3 =new Barrier(28,4,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier3);

    Barrier *barrier4 =new Barrier(28,6,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier4);

    Barrier *barrier5 =new Barrier(25.5,7,10,0.7,&timer,QPixmap(":/image/bar1.png").scaled(5*50,0.35*50),world,scene);
    BarrierList.push_back(barrier5);

    Barrier *barrier6 =new Barrier(22,8,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier6);

    Barrier *barrier7 =new Barrier(27,8,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier7);

    Barrier *barrier8 =new Barrier(22,10,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier8);

    Barrier *barrier9 =new Barrier(27,10,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier9);

    Barrier *barrier10 =new Barrier(25.5,11,7,0.7,&timer,QPixmap(":/image/bar1.png").scaled(3.5*50,0.35*50),world,scene);
    BarrierList.push_back(barrier10);

    Barrier *barrier11 =new Barrier(18,4,1.2,1.2,&timer,QPixmap(":/image/block.png").scaled(50,50),world,scene);
    BarrierList.push_back(barrier11);

    //豬豬
    Pig *pig1 = new Pig(23.5,3.5,0.75,&timer,QPixmap(":/image/pig_1.png").scaled(50,50),world,scene);
    PigList.push_back(pig1);

    Pig *pig2 = new Pig(25.5,3.5,0.75,&timer,QPixmap(":/image/pig_1.png").scaled(50,50),world,scene);
    PigList.push_back(pig2);

    Pig *pig3 = new Pig(24.25,8.5,0.75,&timer,QPixmap(":/image/pig_1.png").scaled(50,50),world,scene);
    PigList.push_back(pig3);

    Pig *pig4 = new Pig(24.25,11.5,0.75,&timer,QPixmap(":/image/pig_1.png").scaled(50,50),world,scene);
    PigList.push_back(pig4);

    Pig *pig5 = new Pig(18,6,0.75,&timer,QPixmap(":/image/pig_1.png").scaled(50,50),world,scene);
    PigList.push_back(pig5);
}

void MainWindow::deleteitem()
{
    int i;
    for(i=0;i<BarrierList.size();i++)
    {
        if( BarrierList[i]!=NULL && BarrierList[i]->dead)
        {
            qDebug()<<"BarrierList"<<i<<"bye";
            delete BarrierList[i];
            BarrierList[i]=NULL;
            score+=1000;
            ui->scorenum->setText(QString::number(score));
        }
    }
    for(i=0;i<PigList.size();i++)
    {
        if(PigList[i]!=NULL && PigList[i]->dead)
        {
            qDebug()<<"bye";
            delete PigList[i];
            pignum -= 1;
            PigList[i]=NULL;
            score+=50000;
            ui->scorenum->setText(QString::number(score));
        }
    }
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);

    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(count == 1)
        {
            shoot = true;
            birdie->getBody()->SetTransform(b2Vec2(5.0f,6.0f),0);
            birdie->getBody()->SetActive(0);
            std::cout << "Press1 !" << std::endl ;
        }
        else if(count == 2)
        {
            shoot = true;
            birdYellow->getBody()->SetActive(0);
            std::cout << "Press2 !" << std::endl ;
        }
        else if(count == 3)
        {
            shoot = true;
            birdBlack->getBody()->SetActive(0);
            std::cout << "Press3 !" << std::endl ;
        }
        else if(count == 4)
        {
            shoot = true;

            birdBig->getBody()->SetActive(0);
            std::cout << "Press4 !" << std::endl ;
        }
    }
    if(event->type() == QEvent::MouseMove)
    {
        if(shoot == true && count == 1)
        {
            x_move = mouse_event->x()/32;
            y_move = 17-mouse_event->y()/32;
            birdie->getBody()->SetTransform(b2Vec2(x_move,y_move),0);
            std::cout << "Move1 !" << std::endl ;
        }
        else if(shoot == true && count == 2)
        {
            x_move = mouse_event->x()/32;
            y_move = 17-mouse_event->y()/32;
            birdYellow->getBody()->SetTransform(b2Vec2(x_move,y_move),0);
            std::cout << "Move2 !" << std::endl ;
        }
        else if(shoot == true && count == 3)
        {
            x_move = mouse_event->x()/32;
            y_move = 17-mouse_event->y()/32;
            birdBlack->getBody()->SetTransform(b2Vec2(x_move,y_move),0);
            std::cout << "Move3 !" << std::endl ;
        }
        else if(shoot == true && count == 4)
        {
            x_move = mouse_event->x()/32;
            y_move = 17-mouse_event->y()/32;
            birdBig->getBody()->SetTransform(b2Vec2(x_move,y_move),0);
            std::cout << "Move4 !" << std::endl ;
        }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(shoot == true && count == 1)
        {
            x_end = mouse_event->x()/32;
            y_end = 17 - mouse_event->y()/32;
            x_final = 5 - abs(x_end);
            y_final = 6 - abs(y_end);
            birdie->getBody()->SetActive(1);
            birdie->setLinearVelocity(b2Vec2(x_final*3,y_final*3.5));
            shoot = false;
            fire = true;
            count++;
            birdYellow->getBody()->SetTransform(b2Vec2(5.0f,6.0f),0);
            std::cout << "Release1 !" << std::endl ;
        }
        else if(shoot == true && count == 2)
        {
            x_end = mouse_event->x()/32;
            y_end = 17 - mouse_event->y()/32;
            x_final = 5 - abs(x_end);
            y_final = 6 - abs(y_end);
            birdYellow->getBody()->SetActive(1);
            birdYellow->setLinearVelocity(b2Vec2(x_final*3,y_final*4));
            shoot = false;
            fire = true;
            count++;
            birdBlack->getBody()->SetTransform(b2Vec2(5.0f,6.0f),0);
            std::cout << "Release2 !" << std::endl ;
        }
        else if(shoot == true && count == 3)
        {
            x_end = mouse_event->x()/32;
            y_end = 17 - mouse_event->y()/32;
            x_final = 5 - abs(x_end);
            y_final = 6 - abs(y_end);
            birdBlack->getBody()->SetActive(1);
            birdBlack->setLinearVelocity(b2Vec2(x_final*3,y_final*4));
            shoot = false;
            fire = true;
            count++;
            birdBig->getBody()->SetTransform(b2Vec2(5.0f,6.0f),0);
            std::cout << "Release3 !" << std::endl ;
        }
        else if(shoot == true && count == 4)
        {
            x_end = mouse_event->x()/32;
            y_end = 17 - mouse_event->y()/32;
            x_final = 5 - abs(x_end);
            y_final = 6 - abs(y_end);
            birdBig->getBody()->SetActive(1);
            birdBig->setLinearVelocity(b2Vec2(x_final*3,y_final*4));
            shoot = false;
            fire = true;
            count++;
            birdBig->getBody()->SetTransform(b2Vec2(5.0f,6.0f),0);
            std::cout << "Release4 !" << std::endl ;
        }

    }

    if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Space)
        {
            if(fire == true && count == 2){
                std::cout << "1" << std::endl;
                birdie->effect();
                fire = false;
            }
            if(fire == true && count == 3){
                std::cout << "2" << std::endl;
                birdYellow->effect();
                fire = false;
            }
            if(fire == true && count == 4){
                std::cout << "3" << std::endl;
                birdBlack->effect();
                fire = false;
            }
            if(fire == true && count == 5){
                std::cout << "4" << std::endl;
                birdBig->effect();
                fire = false;
            }
        }
    }

    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::on_pushButton_clicked()
{
    shoot = false;
    fire = false;

    count = 1;
    pignum = 5;
    score = 0;
    ui->scorenum->setText(QString::number(score));

    int i;
    for(i=0;i<BarrierList.size();i++)
    {
        if( BarrierList[i]!=NULL)
        {
            delete BarrierList[i];
            BarrierList[i]=NULL;
        }
    }
    for(i=0;i<PigList.size();i++)
    {
        if(PigList[i]!=NULL)
        {
            delete PigList[i];
            PigList[i]=NULL;
        }
    }
    delete birdie;
    delete birdYellow;
    delete birdBig;
    delete birdBlack;

    BarrierList.clear();
    PigList.clear();
    setGame();
    timer.start(100/6);
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}
