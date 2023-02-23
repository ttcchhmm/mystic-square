#include "Game.hh"

#include <QRandomGenerator>
#include <QDebug>

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

    // Initialize the play field with -1.
    for(int x(0); x < _size; x++) {
        _playField[x] = QVector<int>(_size);

        for(int y(0); y < _size; y++) {
            _playField[x][y] = -1;
        }
    }

    // While there is IDs to place.
    while(!toPlace.empty()) {
        // Generate a random X/Y pair to find a free spot.
        int x, y;
        do {
            x = QRandomGenerator::global()->bounded(_size);
            y = QRandomGenerator::global()->bounded(_size);
        } while(_playField[x][y] != -1);

        _playField[x][y] = toPlace.takeFirst(); // Dequeue the first element.
    }

    // Place a random free tile.
    auto voidX(QRandomGenerator::global()->bounded(_size));
    auto voidY(QRandomGenerator::global()->bounded(_size));
    _playField[voidX][voidY] = -1;

    // Print the play field to the console.
    for(auto const & x : _playField) {
        QString line(QLatin1String(""));
        for(auto const & y : x) {
            line += QString::number(y) + " / ";
        }

        qDebug() << line;
    }

    emit gameCreated(_playField);
}
