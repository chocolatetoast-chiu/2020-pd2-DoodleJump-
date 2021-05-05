#include "norm_platform.h"

norm_platform::norm_platform()
{

}

norm_platform::~norm_platform()
{

}

QGraphicsPixmapItem* norm_platform::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/normal_platform.png"));
    return plat;
}

int norm_platform::getType()
{
    int i = 0;
    return i;
}
