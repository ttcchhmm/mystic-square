#include "Game.hh"

#include <QRandomGenerator>
#include <QDebug>

bool Game::_riggedMode(false);

Game::Game(const int &size, QObject* parent): QObject(parent), _size(size), _numberOfMoves(0), _playField(0) {
    newGame(_size);
}

void Game::newGame(const int &size) {
    _size = size;
    _numberOfMoves = 0;
    _playField = PlayField(_size);

    // Contain the tiles ID to place. Will be used as a queue.
    QVector<int> toPlace;
    toPlace.reserve(_size * _size);

    for(int i(0); i < _size * _size; i++) {
        toPlace.append(i);
    }

    // Initialize the play field with empty tiles.
    for(int x(0); x < _size; x++) {
        _playField[x] = QVector<int>(_size);

        for(int y(0); y < _size; y++) {
            _playField[x][y] = EMPTY_TILE;
        }
    }

    if(_riggedMode) { // In rigged mode, don't use a random order.
        for(int x(0); x < _size; x++) {
            for(int y(0); y < _size; y++) {
                _playField[x][y] = toPlace.takeFirst();
            }
        }
    } else { // Normal mode.
        // While there is IDs to place.
        while(!toPlace.empty()) {
            // Generate a random X/Y pair to find a free spot.
            int x, y;
            do {
                x = QRandomGenerator::global()->bounded(_size);
                y = QRandomGenerator::global()->bounded(_size);
            } while(_playField[x][y] != EMPTY_TILE);

            _playField[x][y] = toPlace.takeFirst(); // Dequeue the first element.
        }
    }

    // Place a random empty tile.
    auto voidX(QRandomGenerator::global()->bounded(_size));
    auto voidY(QRandomGenerator::global()->bounded(_size));
    _playField[voidX][voidY] = EMPTY_TILE;

    // Print the play field to the console.
    for(auto const & x : _playField) {
        QString line;
        for(auto const & y : x) {
            line += QString::number(y) + " / ";
        }

        qDebug() << line;
    }

    emit gameCreated(_playField);
}

void Game::move(int tile) {
    // Search for the coordinates of the tile.
    int x(-1), y(-1);

    for(int lx(0); lx < _size; lx++) {
        for(int ly(0); ly < _size; ly++) {
            if(_playField[lx][ly] == tile) {
                x = lx;
                y = ly;

                break;
            }
        }
    }

    // If the tile is invalid.
    if(x == -1 || y == -1) {
        throw std::logic_error("Invalid tile value; coordinates not found.");
    }

    // Swap with the empty tile, if possible.
    for(auto delta : { Delta(-1, 0), Delta(1, 0), Delta(0, -1), Delta(0, 1) }) {
        auto emptyX(x + delta.first);
        auto emptyY(y + delta.second);

        // Out-of-bound check + empty tile found.
        if(emptyX >= 0 &&
           emptyY >= 0 &&
           emptyX < _size &&
           emptyY < _size &&
           _playField[emptyX][emptyY] == EMPTY_TILE) {

            // Swap with the empty tile.
            _playField[emptyX][emptyY] = _playField[x][y];
            _playField[x][y] = EMPTY_TILE;
            _numberOfMoves++;

            emit played(_numberOfMoves);
        }
    }
}

const Game::PlayField &Game::getPlayField() const {
    return _playField;
}

void Game::enableRiggedMode() {
    _riggedMode = true;
    qDebug() << "Rigged mode enabled.";
}
