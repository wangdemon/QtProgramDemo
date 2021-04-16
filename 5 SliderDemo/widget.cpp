#include "widget.h"

#include <QVBoxLayout>
#include "customslider.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    CustomSlider* slider = new CustomSlider;
    slider->setFixedHeight(60);
    layout->addWidget(slider);
    this->setLayout(layout);
    this->resize(700, 300);
}

Widget::~Widget()
{
}

