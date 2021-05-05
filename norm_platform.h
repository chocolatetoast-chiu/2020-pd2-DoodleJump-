#ifndef NORM_PLATFORM_H
#define NORM_PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"


class norm_platform: public platform
{
public:
    norm_platform();
    ~norm_platform();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;

};

#endif // NORM_PLATFORM_H
