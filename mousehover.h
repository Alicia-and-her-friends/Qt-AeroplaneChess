#ifndef MOUSEHOVER_H
#define MOUSEHOVER_H

#include <QObject>

class mouseHover : public QObject
{
    Q_OBJECT
public:
    mouseHover();
signals:
    void signal_sendBtnObj(QObject*, QString);
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MOUSEHOVER_H

