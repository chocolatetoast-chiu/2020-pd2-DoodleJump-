#ifndef PROTECTION_H
#define PROTECTION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "platform.h"
#include "mainwindow.h"

class protection: public platform
{
public:
    protection();
    ~protection();
    virtual QGraphicsPixmapItem* place();
    virtual int getType();

private:
    QGraphicsPixmapItem *plat;
};

#endif // PROTECTION_H
