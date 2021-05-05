#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"

class moving_platform: public platform
{
public:
    moving_platform();
    ~moving_platform();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;

};

#endif // MOVING_PLATFORM_H
