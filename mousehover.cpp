#include "mousehover.h"
#include <QEvent>
#include <QDebug>
mouseHover::mouseHover()
{

}

bool mouseHover::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter){//鼠标进入控件
        emit signal_sendBtnObj(obj, obj->objectName());
        return true;
    }else if (event->type() == QEvent::Leave){//鼠标离开控件
        emit signal_sendBtnObj(obj, "mouse out");
        return true;
    }else{
        return  QObject::eventFilter(obj, event);
    }
}
