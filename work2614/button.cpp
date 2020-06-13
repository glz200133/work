#include "button.h"

button::button(QString pix):QPushButton(0)
{
     QPixmap pixmap(pix);
     this->setFixedSize(pixmap.width(),pixmap.height());
     //根据图片外观调整自己外观
     this->setStyleSheet("QPushButton{border:Opx}");
     this->setIcon(pixmap);


     this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}
