#include "gamewidget.hh"

#include <QLabel>

GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    _bg(Background::NUMBERED),
    _pixmap(0, 0),
    _size(3),
    _layout(new QGridLayout(this)){

    this->setLayout(_layout);
    redrawTiles();
}

void GameWidget::changeBackground(Background bg) {
    _bg = bg;

    switch (_bg) {
        case Background::NUMBERED:
            _pixmap = QPixmap(0, 0);
            break;
        case Background::FOREST:
            _pixmap.load(":/assets/forest.jpg");
            break;
        case Background::TREE:
            _pixmap.load(":/assets/tree.jpg");
            break;
        case Background::NETWORK:
            _pixmap.load(":/assets/network.jpeg");
            break;
    }

    redrawTiles();
}

void GameWidget::changeSize(int size) {
    _size = size;
    redrawTiles();
}

void GameWidget::redrawTiles() {
    for(auto w : this->findChildren<QWidget*>()) {
        w->deleteLater();
    }

    unsigned int count(1);
    for(int x(0); x < _size; x++) {
        for(int y(0); y < _size; y++) {
            QLabel *label(nullptr);

            if(_bg == Background::NUMBERED) {
                label = new QLabel(QString::number(count), this);
                count++;
            } else {
                label = new QLabel(this);

                int height(_pixmap.width() / _size);
                int pixX(height * x);
                int pixY(height * y);

                label->setPixmap(_pixmap.copy(pixY, pixX, height, height));
            }

            _layout->addWidget(label, x, y);
        }
    }
}
