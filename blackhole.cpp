#include "blackhole.h"

blackhole::blackhole()
{

}

blackhole::~blackhole()
{

}

QGraphicsPixmapItem* blackhole::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/blackhole.png"));
    return plat;
}

int blackhole::getType()
{
    int i = 6;
    return i;
}
