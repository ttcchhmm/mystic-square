#ifndef MYSTICSQUARE_GAME_HH
#define MYSTICSQUARE_GAME_HH

#include <QObject>
#include <QFile>

#include "Stub.hh"

/**
 * Contains the state of a game.
 */
class Game: public QObject {
    Q_OBJECT

private:
    /**
     * The size of the game area.
     */
    int _size;

    /**
     * The number of moves played.
     */
    unsigned int _numberOfMoves;

public:
    /**
     * Create a new game object.
     * @param size The size of the game.
     * @param parent The parent of this object.
     */
    explicit Game(const int & size = 3, QObject* parent = nullptr);

public slots:
    /**
     * Create a new game.
     * @param size The size of the new game.
     */
    void newGame(const int & size);

    /**
     * Load a saved game from a file.
     * @param file The file to load.
     */
    void loadGame(QFile & file) STUB;

    /**
     * Save a game to a file.
     * @param file The file to save to.
     */
    void saveGame(QFile & file) STUB;

signals:
    /**
     * Emitted after the played made a move.
     * @param numberOfMoves The new number of moves played.
     */
    void played(unsigned int numberOfMoves);

    /**
     * Emitted after a new game is created.
     * @param size The size of the new game.
     */
    void gameCreated(int size);
};


#endif //MYSTICSQUARE_GAME_HH