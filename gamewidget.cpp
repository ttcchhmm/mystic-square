#include "gamewidget.hh"

GameWidget::GameWidget(QWidget *parent): QWidget(parent), _bg(Background::NUMBERED), _size(3) {

}

void GameWidget::changeBackground(Background bg) {
    _bg = bg;
}

void GameWidget::changeSize(int size) {
    _size = size;
}
