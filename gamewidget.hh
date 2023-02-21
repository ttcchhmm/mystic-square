#ifndef MYSTICSQUARE_GAMEWIDGET_HH
#define MYSTICSQUARE_GAMEWIDGET_HH

#include <QWidget>

#include "BackgroundEnum.hh"

/**
 * The widget displaying the current state of the game.
 */
class GameWidget: public QWidget {
    Q_OBJECT

private:
    Background _bg;
    int _size;

public:
    /**
     * Create a new GameWidget.
     * @param parent The parent of the newly created GameWidget.
     */
    explicit GameWidget(QWidget* parent = nullptr);

public slots:
    void changeBackground(Background bg);
    void changeSize(int size);
};


#endif //MYSTICSQUARE_GAMEWIDGET_HH
