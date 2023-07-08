#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QThread>
#include <QEventloop>
#include <ctime>
#include <QLabel>
#include "Game.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,Game* game_=nullptr);
    ~MainWindow();
    void m_sleep(int time);
    Game* game_now;
    QLabel* win_state;
    QLabel* color_now;

private slots:
    void slotDiceClicked(bool checked);//点击骰子
    void slotChangeWinState(int x);//是否分出胜负
    void slotChangeColorNow(int x);//更改当前颜色

private:
    QPushButton *dice;//骰子
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
