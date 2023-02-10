#ifndef MYSTICSQUARE_GAMEWIDGET_HH
#define MYSTICSQUARE_GAMEWIDGET_HH

#include <QWidget>

/**
 * The widget displaying the current state of the game.
 */
class GameWidget: public QWidget {
    Q_OBJECT

public:
    /**
     * Create a new GameWidget.
     * @param parent The parent of the newly created GameWidget.
     */
    explicit GameWidget(QWidget* parent = nullptr);
};


#endif //MYSTICSQUARE_GAMEWIDGET_HH
