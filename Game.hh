#ifndef MYSTICSQUARE_GAME_HH
#define MYSTICSQUARE_GAME_HH

#include <QObject>
#include <QVector>
#include <QFile>
#include <QPair>

#include "Stub.hh"

/**
 * Contains the state of a game.
 */
class Game: public QObject {
    Q_OBJECT

public:
    /**
     * Defines a 2D array containing the play area.
     */
    using PlayField = QVector<QVector<int>>;

    /**
     * The value of the empty tile.
     */
    static const int EMPTY_TILE = -1;

private:
    /**
     * Defines a delta on two axis.
     */
    using Delta = QPair<int, int>;

    /**
     * True when rigged mode is enabled, false in normal mode.
     */
    static bool _riggedMode;

    /**
     * The size of the game area.
     */
    int _size;

    /**
     * The number of moves played.
     */
    unsigned int _numberOfMoves;

    /**
     * The current state of the play field.
     */
     PlayField _playField;

public:
    /**
     * Create a new game object.
     * @param size The size of the game.
     * @param parent The parent of this object.
     */
    explicit Game(const int & size = 3, QObject* parent = nullptr);

    /**
     * Get the current play field.
     * @return The current play field.
     */
    [[nodiscard]] const PlayField &getPlayField() const;

    /**
     * Enable the rigged mode.
     *
     * In this mode, a simple puzzle will always be generated. Used for testing.
     */
    static void enableRiggedMode();

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
    void loadGame(QFile & file);

    /**
     * Save a game to a file.
     * @param file The file to save to.
     */
    void saveGame(QFile & file);

    /**
     * Move the specified tile to the empty space next to it if possible.
     * @param tile The tile's ID.
     */
    void move(int tile);

signals:
    /**
     * Emitted after the player made a move.
     * @param numberOfMoves The new number of moves played.
     */
    void played(unsigned int numberOfMoves);

    /**
     * Emitted after a new game is created.
     * @param playField The new play area.
     * @param numberOfMoves The current number of moves (in case of a loaded game).
     */
    void gameCreated(PlayField & playField, unsigned int numberOfMoves);

    /**
     * Emitted when a saved game couldn't be loaded.
     * @param file The file concerned by this failure.
     */
    void loadFailure(QFile & file);

    /**
     * Emitted when an error occurred while saving a game.
     * @param file The file concerned by this failure.
     */
    void saveFailure(QFile & file);

    /**
     * Emitted when the player won the game.
     */
    void gameWon();

private:
    /**
     * Initialize an empty play field.
     * @param size The size of the new field.
     * @returns A new play field.
     */
    [[nodiscard]] PlayField initEmptyPlayField(int size) const;

    /**
     * Check if the user has finished the game.
     * @return True if the player won, false otherwise.
     */
    [[nodiscard]] bool hasWon() const;
};


#endif //MYSTICSQUARE_GAME_HH
