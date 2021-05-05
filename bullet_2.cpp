#include "bullet_2.h"

bullet_2::bullet_2()
{

}

bullet_2::~bullet_2()
{

}

QGraphicsPixmapItem* bullet_2::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/bullet.png"));
    return plat;
}

int bullet_2::getType()
{
    int i = 7;
    return i;
}
