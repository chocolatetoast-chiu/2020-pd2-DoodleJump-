#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>

namespace Ui {
class gameover;
}

class gameover : public QDialog
{
    Q_OBJECT

public:
    explicit gameover(int result = 0, QWidget *parent = nullptr);
    ~gameover();

private slots:
    void restartbtnclicked();

private:
    Ui::gameover *ui;

};

#endif // GAMEOVER_H
