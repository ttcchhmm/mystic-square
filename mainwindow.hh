#ifndef MYSTICSQUARE_MAINWINDOW_HH
#define MYSTICSQUARE_MAINWINDOW_HH

#include <QMainWindow>
#include <QSharedPointer>

#include "Game.hh"
#include "BackgroundEnum.hh"
#include "Stub.hh"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * The main window for Mystic Square.
 *
 * Contains the game area and the main controls.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

private:
    /**
     * A shared pointer to a Game instance, which handle game logic.
     */
    QSharedPointer<Game> _game;

public:
    /**
     * Create a new MainWindow.
     * @param parent The parent of the newly created window.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * Get the current Game instance.
     * @return A shared pointer to the Game instance.
     */
    [[nodiscard]] const QSharedPointer<Game> &getGame() const;

    ~MainWindow() override;

public slots:
    /**
     * Show the "About Mystic Square" dialog.
     */
    void aboutApp();

    /**
     * Show the "About Qt" dialog.
     */
    void aboutQt();

    /**
     * Show the "New Game" dialog.
     */
    void newGame();

    /**
     * Show the "Load Game" dialog.
     */
    void loadGame();

    /**
     * Show the "Save Game" dialog.
     */
    void saveGame();

    /**
     * Executed when the player makes a move.
     * @param numberOfMoves The number of moves played.
     */
    void handlePlay(unsigned int numberOfMoves);

    /**
     * Executed when a new game is started.
     * @param playField The new play field.
     */
    void handleNewGame(Game::PlayField & playField);

signals:
    void backgroundUpdated(Background newBackground);

private:
    /**
     * The UI code generated by Qt Designer.
     */
    Ui::MainWindow *ui;
};


#endif //MYSTICSQUARE_MAINWINDOW_HH
