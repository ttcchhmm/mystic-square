#ifndef MYSTICSQUARE_GAMEWIDGET_HH
#define MYSTICSQUARE_GAMEWIDGET_HH

#include <QWidget>
#include <QGridLayout>
#include <QPixmap>
#include <QSharedPointer>
#include <QPushButton>

#include "BackgroundEnum.hh"
#include "Game.hh"

/**
 * The widget displaying the current state of the game.
 */
class GameWidget: public QWidget {
    Q_OBJECT

private:
    /**
     * The size of a single tile.
     */
    const int TILE_SIZE = 100;

    /**
     * The spacing between tiles.
     */
    const int SPACING = 5;

    /**
     * The current background.
     */
    Background _bg;

    /**
     * The current tiles.
     */
    QVector<QPixmap> _tiles;

    /**
     * The current size.
     */
    int _size;

    /**
     * A shared pointer to a Game instance, which handle game logic.
     */
    QSharedPointer<Game> _game;

    /**
     * The layout of this widget.
     */
    QGridLayout *_layout;

public:
    /**
     * Create a new GameWidget.
     * @param parent The parent of the newly created GameWidget. Its parent should be an instance of MainWindow.
     */
    explicit GameWidget(QWidget* parent);

public slots:
    /**
     * Change the current background and redraw tiles.
     * @param bg The background to change to.
     */
    void changeBackground(Background bg);

    /**
     * Change the current size.
     * @param size The new size.
     */
    void changeSize(int size);

    /**
     * Handle a new game.
     * @param playField The new play field.
     */
    void handleNewGame(Game::PlayField & playField);

    /**
     * Redraw every tile.
     */
    void redrawTiles();

private:
    /**
     * Get a new QPushButton created to be used as a tile.
     * @param val The value of the tile.
     * @return A new QPushButton created to be used as a tile.
     */
    QPushButton* getTileLabel(int val);
};


#endif //MYSTICSQUARE_GAMEWIDGET_HH
