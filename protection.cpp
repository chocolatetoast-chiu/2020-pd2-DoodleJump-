#include "protection.h"

protection::protection()
{

}

protection::~protection()
{

}

QGraphicsPixmapItem* protection::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/protect.png"));
    return plat;
}

int protection::getType()
{
    int i = 3;
    return i;
}
