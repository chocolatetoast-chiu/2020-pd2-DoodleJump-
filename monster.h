#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"

class monster:public platform
{
public:
    monster();
    ~monster();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;
};

#endif // MONSTER_H
