#ifndef BUTTON_H
#define BUTTON_H
#include<QWidget>
#include<QPushButton>

class button: public QPushButton
{
    Q_OBJECT
public:
    button(QString pix);//切换界面的button
};

#endif // BUTTON_H
