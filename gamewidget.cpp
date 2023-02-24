#include "gamewidget.hh"

#include <QLabel>

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

    setFixedSize(WIDGET_SIZE, WIDGET_SIZE);

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
    for(auto w : this->findChildren<QWidget*>()) {
        w->deleteLater();
    }

    // The size of a single tile.
    const int tileSize(WIDGET_SIZE/_size);

    // The height of a subsection inside the pixmap
    int height(_pixmap.width() / _size);

    // The current number of tiles.
    unsigned int count(1);

    for(int x(0); x < _size; x++) {
        for(int y(0); y < _size; y++) {
            QLabel *label(nullptr);

            if(_bg == Background::NUMBERED) { // Without a picture
                label = new QLabel(QString::number(count), this);
                count++;
            } else { // Using a picture
                label = new QLabel(this);

                // Calculate the coordinates inside the pixmap
                int pixX(height * x);
                int pixY(height * y);

                // Set the tile's picture
                label->setPixmap(
                        _pixmap.copy(
                                pixY,
                                pixX,
                                height, height
                                )

                                // Scale it to an acceptable size
                                .scaled(
                                        tileSize,
                                        tileSize,
                                        Qt::AspectRatioMode::IgnoreAspectRatio,
                                        Qt::TransformationMode::SmoothTransformation
                                )
                        );
            }

            _layout->addWidget(label, x, y);
        }
    }
}
