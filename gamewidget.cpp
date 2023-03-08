#include "gamewidget.hh"

#include <QPainter>

#include "mainwindow.hh"

GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    _bg(Background::NUMBERED),
    _size(3),
    /* The parent is the central widget of the main window, but we want the main window instance.
       Ugly, but we can't add more parameters to a constructor used as a promoted widget in Designer. */
    _game(dynamic_cast<MainWindow*>(parent->parentWidget())->getGame()),
    _layout(new QGridLayout(this)){

    _layout->setSpacing(SPACING);
    this->setLayout(_layout);

    connect(_game.data(), &Game::gameCreated, this, &GameWidget::handleNewGame);
    connect(_game.data(), &Game::played, this, &GameWidget::redrawTiles);

    changeBackground(_bg);
}

void GameWidget::changeBackground(Background bg) {
    _bg = bg;
    _tiles = QVector<QPixmap>(_size * _size);

    if(_bg == Background::NUMBERED) { // Without a picture
        for(int x(0); x < _size; x++) {
            for(int y(0); y < _size; y++) {
                QPixmap content(TILE_SIZE, TILE_SIZE);
                content.fill(palette().color(QPalette::Highlight)); // System highlight color

                QPainter painter(&content);
                painter.setPen(palette().color(QPalette::Text)); // System text color. Used to avoid black text in dark mode.
                painter.drawText(QRectF(0, 0, TILE_SIZE, TILE_SIZE), Qt::AlignHCenter | Qt::AlignVCenter,QString::number(x + _size * y + 1));

                _tiles[x + _size * y] = content;
            }
        }
    } else { // With a picture
        // Load the pixmap.
        QPixmap pixmap;
        switch (_bg) {
            case Background::FOREST:
                pixmap.load(":/assets/forest.jpg");
                break;
            case Background::TREE:
                pixmap.load(":/assets/tree.jpg");
                break;
            case Background::NETWORK:
                pixmap.load(":/assets/network.jpeg");
                break;
            default:
                throw std::logic_error("Invalid background type.");
        }

        // The height of a tile.
        int height(pixmap.height() / _size);

        // Generate tiles from loaded picture.
        for(int x(0); x < _size; x++) {
            for(int y(0); y < _size; y++) {
                _tiles[x + _size * y] = pixmap.copy( // Extract from the current picture.
                        height * x,
                        height * y,
                        height,
                        height)
                .scaled( // Scale it to an acceptable size.
                        TILE_SIZE,
                        TILE_SIZE,
                        Qt::AspectRatioMode::IgnoreAspectRatio, // We don't care about this, we're resizing a square to a square.
                        Qt::TransformationMode::SmoothTransformation); // Better picture quality.
            }
        }
    }

    redrawTiles();
}

void GameWidget::changeSize(int size) {
    _size = size;
    changeBackground(_bg);
}

void GameWidget::handleNewGame(Game::PlayField &playField) {
    setEnabled(true);
    changeSize(playField.size());
}

void GameWidget::redrawTiles() {
    // Clear the grid.
    for(auto w : this->findChildren<QWidget*>()) {
        w->deleteLater();
    }

    auto widgetSize((TILE_SIZE + SPACING) * _size);
    setFixedSize(widgetSize, widgetSize);

    // Set tiles
    for(int x(0); x < _size; x++) {
        for(int y(0); y < _size; y++) {
            auto val(_game->getPlayField()[x][y]);
            auto btn(getTileLabel(val));

            if(val != Game::EMPTY_TILE) {
                btn->setIcon(_tiles[val]);
            } else {
                btn->setEnabled(false);
            }

            _layout->addWidget(btn, x, y);
        }
    }
}

QPushButton *GameWidget::getTileLabel(int val) {
    auto btn(new QPushButton(this));
    btn->setFixedSize(TILE_SIZE, TILE_SIZE);
    btn->setIconSize(QSize(TILE_SIZE, TILE_SIZE));
    btn->setFlat(true);

    // Trigger a change only on a non-empty space.
    if(val != Game::EMPTY_TILE) {
        connect(btn, &QPushButton::clicked, this, [this, val]() {
           _game->move(val);
        });
    }

    return btn;
}
