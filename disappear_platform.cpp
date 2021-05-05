#include "disappear_platform.h"

disappear_platform::disappear_platform()
{

}

disappear_platform::~disappear_platform()
{

}

QGraphicsPixmapItem* disappear_platform::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/disappear_platform.png"));
    return plat;
}

int disappear_platform::getType()
{
    int i = 1;
    return i;
}
