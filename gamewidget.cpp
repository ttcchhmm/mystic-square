#include "gamewidget.hh"

#include <QLabel>
#include <QPainter>

#include "mainwindow.hh"

GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    _bg(Background::NUMBERED),
    _pixmap(0, 0),
    _size(3),
    /* The parent is the central widget of the main window, but we want the main window instance.
       Ugly, but we can't add more parameters to a constructor used as a promoted widget in Designer. */
    _game(dynamic_cast<MainWindow*>(parent->parentWidget())->getGame()),
    _layout(new QGridLayout(this)){

    this->setLayout(_layout);

    connect(_game.data(), &Game::gameCreated, this, &GameWidget::handleNewGame);

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

void GameWidget::handleNewGame(Game::PlayField &playField) {
    changeSize(playField.size());
}

void GameWidget::redrawTiles() {
    // Clear the grid.
    for(auto w : this->findChildren<QWidget*>()) {
        w->deleteLater();
    }

    // The height of a subsection inside the pixmap
    int height(_pixmap.width() / _size);

    for(int x(0); x < _size; x++) {
        for(int y(0); y < _size; y++) {
            auto *label(new QLabel(this));
            auto val(_game->getPlayField()[x][y]);

            if(_game->getPlayField()[x][y] != -1) {
                if(_bg == Background::NUMBERED) { // Without a picture
                    QPixmap content(TILE_SIZE, TILE_SIZE);
                    content.fill(palette().color(QPalette::Highlight)); // System highlight color

                    QPainter painter(&content);
                    painter.setPen(palette().color(QPalette::Text)); // System text color. Used to avoid black text in dark mode.
                    painter.drawText(QRectF(0, 0, TILE_SIZE, TILE_SIZE), Qt::AlignHCenter | Qt::AlignVCenter, QString::number(val + 1));

                    label->setPixmap(content);
                } else { // Using a picture
                    // Calculate the coordinates inside the pixmap
                    int pixX(height * (val - val/_size));
                    int pixY(height * (val/_size));

                    // Set the tile's picture
                    label->setPixmap(
                            _pixmap.copy(
                                    pixY,
                                    pixX,
                                    height, height
                                    )

                                    // Scale it to an acceptable size
                                    .scaled(
                                            TILE_SIZE,
                                            TILE_SIZE,
                                            Qt::AspectRatioMode::IgnoreAspectRatio,
                                            Qt::TransformationMode::SmoothTransformation
                                    )
                            );
                }
            }

            _layout->addWidget(label, x, y);
        }
    }
}
