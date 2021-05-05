#ifndef ROCKET_H
#define ROCKET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"

class rocket: public platform
{
public:
    rocket();
    ~rocket();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;
};

#endif // ROCKET_H
