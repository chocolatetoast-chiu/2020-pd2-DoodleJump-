#ifndef PLATFORM_H
#define PLATFORM_H
#include "mainwindow.h"

class platform
{
public:
    platform();
    virtual ~platform();
    virtual QGraphicsPixmapItem* place() = 0;
    virtual int getType() = 0;
};

#endif // PLATFORM_H
