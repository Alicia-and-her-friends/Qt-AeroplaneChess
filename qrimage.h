#ifndef QRIMAGE_H
#define QRIMAGE_H

#include <QWidget>

namespace Ui {
class QRImage;
}

class QRImage : public QWidget
{
    Q_OBJECT

public:
    explicit QRImage(QWidget *parent = nullptr);
    ~QRImage();
public slots:
    void slots_showQR(QString);

private:
    Ui::QRImage *ui;
};

#endif // QRIMAGE_H

