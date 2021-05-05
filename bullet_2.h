#ifndef BULLET_2_H
#define BULLET_2_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"

class bullet_2:public platform
{
public:
    bullet_2();
    ~bullet_2();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;
};

#endif // BULLET_2_H
