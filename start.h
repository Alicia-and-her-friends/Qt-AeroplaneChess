#ifndef START_H
#define START_H

#include <QMainWindow>
#include <QPushButton>
#include "Game.h"
#include "path.h"
#include <iostream>
#include <cstring>

namespace Ui {
class start;
}

class start : public QMainWindow
{
    Q_OBJECT

public:
    Game *game;
    explicit start(QWidget *parent = nullptr);
    ~start();
    start(QWidget *parent, Game* game_);

private:
    Ui::start *ui;
signals:
    void clk();//点击
public:
    void emit_clk();
private slots:
    void slotclk();
};


#endif // START_H
