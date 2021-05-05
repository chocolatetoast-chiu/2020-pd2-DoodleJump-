#include "rocket.h"

rocket::rocket()
{

}

rocket::~rocket()
{

}

QGraphicsPixmapItem* rocket::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/rocket.png"));
    return plat;
}

int rocket::getType()
{
    int i = 4;
    return i;
}
