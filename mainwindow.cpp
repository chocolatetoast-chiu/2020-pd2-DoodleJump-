#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bullet_2.h"
#include "genmonster.h"
#include "genplatform.h"
#include "protection.h"
#include "rocket.h"
#include "monster.h"
#include "blackhole.h"
#include <ctime>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(static_cast<unsigned int>(time(0)));
    scene = new QGraphicsScene;
    scene->setSceneRect(0, 0, 300, 400);
    ui->graphicsView->setScene(scene);
    // create doodle...
    P = new QGraphicsPixmapItem(QPixmap(":/images/doodle_1.png"));
    P->setZValue(1);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(P));
    P->setPos(125, 350);
    timer = new QTimer();
    roll = new QTimer();
    bullet_timer = new QTimer();
    roll->start(50);
    bullet_timer->start(10);
    // set jumping status...
    doodlejump = new QTimer();
    doodlejump->start(50);
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(Jump()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(check_collide()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(showscore()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(plat_moving()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(monster_moving()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(protection_producing()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(rocket_producing()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(monster_producing()));
    connect(doodlejump, SIGNAL(timeout()), this, SLOT(blackhole_producing()));
    connect(bullet_timer, SIGNAL(timeout()), this, SLOT(bulletfly()));
    // create platform...
    platform* platptr;
    plats.clear();
    platsType.clear();
    bullets.clear();
    platptr = genplatform(result);
    plat = platptr->place();
    platsType.append((platptr->getType()));
    plats.append(plat);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(plats.at(0)));
    plat->setPos(125, 350);
    delete platptr;
    for(int i = 1;i < platnum;i++){
        platptr = genplatform(result);
        plat = platptr->place();
        platsType.append((platptr->getType()));
        plats.append(plat);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(plats.at(i)));
        plat->setPos(30 * (rand()%8 + 1), 50 * (i-1));
        delete platptr;
    }
    // show score...
    score = new QGraphicsTextItem;
    score->setPlainText(QString::number(result));
    score->setFont(QFont("", 18));
    score->setPos(0, 0);
    score->setZValue(1);
    score->setDefaultTextColor(Qt::black);
    scene->addItem(static_cast<QGraphicsTextItem*>(score));
    // doodle falling out...
    if(P->y()>400)
        QTimer::singleShot(0, this, SLOT(game_over()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_A:
        if(P->x()<=-25)
            P->setPos(275, P->y());
        else {
            timer->start(10);
            QTimer::singleShot(5, this, SLOT(moveleft()));
        }
        break;
    case Qt::Key_D:
        if(P->x()>=275)
            P->setPos(-25, P->y());
        else {
            timer->start(10);
            QTimer::singleShot(5, this, SLOT(moveright()));
        }
        break;
    case Qt::Key_Space:
        if(!m_pause){
            doodlejump->stop();
            timer->stop();
            roll->stop();
            bullet_timer->stop();
            m_pause = true;
        }
        else {
            doodlejump->start();
            timer->start();
            roll->start();
            bullet_timer->start();
            m_pause = false;
        }
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(!m_pause){
        platform* bullptr;
        bullptr = new bullet_2;
        QImage image(":/images/doodle_2.png");
        P->setPixmap(QPixmap::fromImage(image));
        b = bullptr->place();
        bullets.append(b);
        b->setZValue(1);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        b->setPos(P->x() + P->pixmap().width() / 2 - b->pixmap().width() / 2, P->y() - b->pixmap().height());
    }
}

void MainWindow::moveright()
{
    if(!m_pause){
        move_flag = true;
        if(static_cast<int>(move_start) == 1){
            move_start = 4;
            move_flag = false;
            timer->stop();
        }
        switch (flag_status) {
        case 0:
            filepath = ":/images/doodle_1.png";
            break;
        case 1:
            filepath = ":/images/doodle_rocket.png";
            break;
        case 2:
            filepath = ":/images/doodle_protected.png";
        }
        QImage image(filepath);
        QImage Mirror_Image = image.mirrored(true, false);
        P->setPixmap(QPixmap::fromImage(Mirror_Image));
        if(move_flag){
            P->setPos(P->x() + static_cast<int>(move_start), P->y());
            //qDebug() << move_start << endl;
            move_start -= 0.3;
            QTimer::singleShot(5, this, SLOT(moveright()));
        }
    }
}

void MainWindow::moveleft()
{
    if(!m_pause){
        move_flag = true;
        if(static_cast<int>(move_start) == 1){
            move_start = 4;
            move_flag = false;
            timer->stop();
        }
        switch (flag_status) {
        case 0:
            filepath = ":/images/doodle_1.png";
            break;
        case 1:
            filepath = ":/images/doodle_rocket.png";
            break;
        case 2:
            filepath = ":/images/doodle_protected.png";
        }
        QImage image(filepath);
        P->setPixmap(QPixmap::fromImage(image));
        if(move_flag){
            P->setPos(P->x() - static_cast<int>(move_start), P->y());
            //qDebug() << move_start << endl;
            move_start -= 0.3;
            QTimer::singleShot(3, this, SLOT(moveleft()));
        }
    }

}

void MainWindow::Jump()
{
    if(!rolling_flag && P->y() >= 245){
        if(falling_value >=0)
            falling = false;
        else
            falling = true;
        P->setPos(P->x(), P->y()-falling_value);
        falling_value -= 1;
    }
    else {
        rolling_flag = true;
        rolling_dist = 105 - (rolling_temp - 245);
        QTimer::singleShot(1, this, SLOT(rolling()));
    }
    // doodle falling out...
    if(P->y()>400 && !end_flag){
        QTimer::singleShot(0, this, SLOT(game_over()));
        end_flag = true;
    }
}

void MainWindow::check_collide()
{
    // check platform collide...
    if(falling){
        for(int i = 0;i < platnum;i++){
            if(P->collidesWithItem(plats.at(i)) && P->y() <= plats.at(i)->y() - 25){
                if(plats.at(i)->isEnabled() == true){
                    falling_value = 14;
                    if(rolling_temp != static_cast<int>(P->y())){
                        rolling_temp = static_cast<int>(P->y());
                        result = result + 400 - rolling_temp;
                    }
                    if(platsType.at(i) == 1){
                        plats.at(i)->setEnabled(false);
                        plats.at(i)->hide();
                    }
                }
            }
        }
    }
    // check protection collide...
    if(protect != nullptr){
        if(P->collidesWithItem(protect) && !protection_flag && !rocket_flag){
            flag_status = 2;
            QImage image(":/images/doodle_protected.png");
            P->setPixmap(QPixmap::fromImage(image));
            protection_flag = true;
            protect->hide();
            QTimer::singleShot(8000, this, SLOT(end_of_protection()));
        }
    }
    // check rocket collide...
    if(roc != nullptr){
        if(P->collidesWithItem(roc) && !rocket_flag && !protection_flag){
            flag_status = 1;
            rolling_flag = true;
            QImage image(":/images/doodle_rocket.png");
            P->setPixmap(QPixmap::fromImage(image));
            rocket_flag = true;
            roc->hide();
            QTimer::singleShot(5000, this, SLOT(end_of_rocket()));
        }
    }
    // check monster collide...
    if(mons != nullptr){
        if(P->collidesWithItem(mons) && !rocket_flag && !protection_flag && !end_flag){
            QTimer::singleShot(0, this, SLOT(game_over()));
            end_flag = true;
        }
    }
    // check blackhole collide...
    if(blkhole != nullptr){
        if(P->collidesWithItem(blkhole) && !rocket_flag && !protection_flag && !end_flag){
            QTimer::singleShot(0, this, SLOT(game_over()));
            end_flag = true;
        }
    }
    // check monster collide bullet...
    if(mons != nullptr){
    }

}

void MainWindow::rolling()
{
    if(rolling_flag){
        // platform rolling...
        for(int i = 0; i < plats.size(); i++){
            if(plats.at(i)->y() <= 400){
                plats.at(i)->setPos(plats.at(i)->x(), plats.at(i)->y() + falling_value);
                if(falling_value == 0){
                    temp_dist = 0;
                    rolling_flag = false;
                    P->setPos(P->x(), 245);
                    disconnect(roll, SIGNAL(timeout()), this, SLOT(rolling()));
                }
            }
            // if there is a platform disappear,
            // replace invisible platform with new created one...
            else {
                platform* platptr;
                platptr = genplatform(result);
                plat = platptr->place();
                plats.replace(i, plat);
                platsType.replace(i, platptr->getType());
                scene->addItem(static_cast<QGraphicsPixmapItem*>(plats.at(i)));
                plat->setPos(30 * (rand()%8 + 1), 0);
                delete platptr;
            }
        }
        // prop rolling...
        if(protect == nullptr) {}
        else {
            if(protect->y() <= 400)
                protect->setPos(protect->x(), protect->y() + falling_value);
            else
                protect = nullptr;
        }
        // rocket rolling...
        if(roc == nullptr){}
        else {
            if(roc->y() <= 400)
                roc->setPos(roc->x(), roc->y() + falling_value);
            else
                roc = nullptr;
        }
        // monster rolling...
        if(mons == nullptr){}
        else {
            if(mons->y() <= 400)
                mons->setPos(mons->x(), mons->y() + falling_value);
            else
                mons = nullptr;
        }
        // blackhole rolling...
        if(blkhole == nullptr){}
        else {
            if(blkhole->y() <= 400)
                blkhole->setPos(blkhole->x(), blkhole->y() + falling_value);
            else
                blkhole = nullptr;
        }
        // falling_value renewed...
        falling_value = falling_value - 1;
        // having rocket...
        if(rocket_flag) {
            falling_value = 20;
            result = result + 20;
        }

    }
}

void MainWindow::showscore()
{
    score->setPlainText(QString::number(result));
}

void MainWindow::plat_moving()
{
    for(int i = 0; i < plats.size(); i++){
        if(platsType.at(i) == 2){
            if(plats.at(i)->x() >= 270)
                plats.at(i)->setPos(-30, plats.at(i)->y());
            plats.at(i)->setPos(plats.at(i)->x() + 5, plats.at(i)->y());
        }
    }
}

void MainWindow::monster_moving()
{
    if(mons != nullptr){
        if(mons->x() >= 270)
            mons->setPos(-30, mons->y());
        mons->setPos(mons->x() + 5, mons->y());  
    }
}

void MainWindow::protection_producing()
{
    // add protect item...
    if(result / 1800 == temp_protection_order){
        platform* propptr;
        propptr = new protection;
        protect = propptr->place();
        protect->setZValue(1);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(protect));
        protect->setPos(30 * (rand()%8 + 1), 0);
        delete propptr;
        temp_protection_order++;
    }
}

void MainWindow::rocket_producing()
{
    // add rocket item...
    if(result / 3000 == temp_rocket_order){
        platform* rockptr;
        rockptr = new rocket;
        roc = rockptr->place();
        roc->setZValue(1);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(roc));
        roc->setPos(30 * (rand()%8 + 1), 0);
        delete rockptr;
        temp_rocket_order++;
    }
}

void MainWindow::monster_producing()
{
    // add monster item...
    if(result / 2420 == temp_monster_order){
        platform* monptr;
        monptr = new monster;
        mons = monptr->place();
        mons->setZValue(1);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(mons));
        mons->setPos(30 * (rand()%8 + 1), 0);
        delete monptr;
        temp_monster_order++;
    }
}

void MainWindow::blackhole_producing()
{
    // add blkhole item...
    if(result / 3500 == temp_blackhole_order){
        platform* blkptr;
        blkptr = new blackhole;
        blkhole = blkptr->place();
        blkhole->setZValue(1);
        scene->addItem(static_cast<QGraphicsPixmapItem*>(blkhole));
        blkhole->setPos(30 * (rand()%8 + 1), 0);
        delete blkptr;
        temp_blackhole_order++;
    }
}

void MainWindow::end_of_protection()
{
    mention = new QGraphicsTextItem;
    mention->setPlainText("About to deactivate...");
    mention->setFont(QFont("", 12));
    mention->setPos(0, 90);
    mention->setZValue(1);
    mention->setDefaultTextColor(Qt::red);
    scene->addItem(static_cast<QGraphicsTextItem*>(mention));
    QEventLoop eventloop;
    QTimer::singleShot(2000, &eventloop, SLOT(quit()));
    eventloop.exec();
    flag_status = 0;
    protection_flag = false;
    scene->removeItem(static_cast<QGraphicsTextItem*>(mention));
}

void MainWindow::end_of_rocket()
{
    flag_status = 0;
    rocket_flag = false;
}

void MainWindow::game_over()
{
    close();
    gameover *go = new gameover(result);
    go->setModal(true);
    go->exec();
}

void MainWindow::bulletfly()
{
    for(int i = 0; i < bullets.size(); i++){
        bullets.at(i)->setPos(bullets.at(i)->x(), bullets.at(i)->y() - 3);
        if(bullets.at(i)->y()<0){
            scene->removeItem(bullets.at(i));
            bullets.removeAt(i);
        }
        if(mons != nullptr){
            if(bullets.at(i)->collidesWithItem(mons)){
                mons->hide();
                mons = nullptr;
            }
        }
    }
}

