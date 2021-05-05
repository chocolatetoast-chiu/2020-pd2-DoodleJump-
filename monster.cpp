#include "monster.h"

monster::monster()
{

}

monster::~monster()
{

}

QGraphicsPixmapItem* monster::place()
{
    plat = new QGraphicsPixmapItem(QPixmap(":/images/monster.png"));
    return plat;
}

int monster::getType()
{
    int i = 5;
    return i;
}
