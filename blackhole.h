#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"

class blackhole: public platform
{
public:
    blackhole();
    ~blackhole();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;

};

#endif // BLACKHOLE_H
