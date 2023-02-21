#include "gamewidget.hh"

#include <QLabel>

GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    _bg(Background::NUMBERED),
    _size(3),
    _layout(new QGridLayout(this)){

    this->setLayout(_layout);
    redrawTiles();
}

void GameWidget::changeBackground(Background bg) {
    _bg = bg;
}

void GameWidget::changeSize(int size) {
    _size = size;
    redrawTiles();
}

void GameWidget::redrawTiles() {
    for(auto w : this->findChildren<QWidget*>()) {
        w->deleteLater();
    }

    for(int x(0); x < _size; x++) {
        for(int y(0); y < _size; y++) {
            _layout->addWidget(new QLabel(QString::number(x) + " / " + QString::number(y), this), x, y);
        }
    }
}
