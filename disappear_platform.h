#ifndef DISAPPEAR_PLATFORM_H
#define DISAPPEAR_PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"

class disappear_platform: public platform
{
public:
    disappear_platform();
    ~disappear_platform();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;

};

#endif // DISAPPEAR_PLATFORM_H
