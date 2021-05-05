#include "moving_platform.h"

moving_platform::moving_platform()
{

}

moving_platform::~moving_platform()
{

}

QGraphicsPixmapItem* moving_platform::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/moving_platform.png"));
    return plat;
}

int moving_platform::getType()
{
    int i = 2;
    return i;
}
