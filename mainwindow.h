#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QPixmap>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QImage>
#include <QDebug>
#include <QString>
#include <QFont>
#include <QList>
#include <QEventLoop>
#include <QMessageBox>
#include <QThread>
#include <QMutex>
#include "gameover.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); 
    QGraphicsScene *scene;
    int result = 0;
    QGraphicsPixmapItem *mons = nullptr, *blkhole = nullptr;
    QGraphicsPixmapItem *b = nullptr;
    bool m_pause = false;


public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    void moveright();
    void moveleft();
    void Jump();
    void check_collide();
    void rolling();
    void showscore();
    void plat_moving();
    void monster_moving();
    void protection_producing();
    void rocket_producing();
    void monster_producing();
    void blackhole_producing();
    void end_of_protection();
    void end_of_rocket();
    void game_over();
    void bulletfly();

private:
    Ui::MainWindow *ui;
    QGraphicsPixmapItem *P, *plat, *protect = nullptr, *roc = nullptr;
    QTimer *timer;
    QTimer *bullet_timer;
    QTimer *doodlejump;
    QTimer *roll;
    QString filepath;
    QGraphicsTextItem *score, *mention;
    QList <QGraphicsPixmapItem*> plats;
    QList <QGraphicsPixmapItem*> bullets;
    QList <int> platsType;
    int flag_status = 0;
    float move_start = 4.0;
    bool move_flag = 0;
    bool falling;
    bool rolling_flag = false;
    bool protection_flag = false, rocket_flag = false;
    bool monster_flag = false, blackhole_flag = false;
    bool end_flag = false;
    int falling_value = 14;
    int rolling_dist = 0, rolling_temp = 0;
    int platnum = 7;
    int temp_dist = 0;
    int temp_protection_order = 1, temp_rocket_order = 1;
    int temp_monster_order = 1, temp_blackhole_order = 1;
};

#endif // MAINWINDOW_H
