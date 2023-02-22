#ifndef MYSTICSQUARE_GAMEWIDGET_HH
#define MYSTICSQUARE_GAMEWIDGET_HH

#include <QWidget>
#include <QGridLayout>
#include <QPixmap>

#include "BackgroundEnum.hh"

/**
 * The widget displaying the current state of the game.
 */
class GameWidget: public QWidget {
    Q_OBJECT

private:
    /**
     * The current background.
     */
    Background _bg;

    /**
     * The current picture.
     */
     QPixmap _pixmap;

    /**
     * The current size.
     */
    int _size;

    /**
     * The layout of this widget.
     */
    QGridLayout *_layout;

public:
    /**
     * Create a new GameWidget.
     * @param parent The parent of the newly created GameWidget.
     */
    explicit GameWidget(QWidget* parent = nullptr);

public slots:
    /**
     * Change the current background.
     * @param bg The background to change to.
     */
    void changeBackground(Background bg);

    /**
     * Change the current size.
     * @param size The new size.
     */
    void changeSize(int size);

private:
    /**
     * Redraw every tile.
     */
    void redrawTiles();
};


#endif //MYSTICSQUARE_GAMEWIDGET_HH
