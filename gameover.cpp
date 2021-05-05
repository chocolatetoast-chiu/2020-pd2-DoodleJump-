#include "gameover.h"
#include "mainwindow.h"
#include "ui_gameover.h"

gameover::gameover(int result, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QPixmap(":/images/BG.png").scaled(this->size(),
                     Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    this->setPalette(palette);
    ui->SCORE->setNum(result);
    connect(ui->restart, SIGNAL(clicked()), this, SLOT(restartbtnclicked()));
}

gameover::~gameover()
{
    delete ui;
}

void gameover::restartbtnclicked()
{
    close();
    MainWindow *m = new MainWindow();
    m->show();
}
