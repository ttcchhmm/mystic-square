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
    _playField = initEmptyPlayField(size);

    // Contain the tiles ID to place. Will be used as a queue.
    QVector<int> toPlace;
    toPlace.reserve(_size * _size);

    for(int i(0); i < _size * _size; i++) {
        toPlace.append(i);
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

    emit gameCreated(_playField, 0);
}

Game::PlayField Game::initEmptyPlayField(int size) {
    PlayField field(size);

    for(int x(0); x < size; x++) {
        field[x] = QVector<int>(size);

        for(int y(0); y < size; y++) {
            field[x][y] = EMPTY_TILE;
        }
    }

    return field;
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

    if(hasWon()) {
        emit gameWon();
    }
}

void Game::loadGame(QFile &file) {
    // Try to open the file
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open:" << file.fileName();
        emit loadFailure(file);
        return;
    }

    // Read the file
    QTextStream in(&file);
    auto data(in.readAll().trimmed());
    file.close();

    // Process the file
    auto lines(data.split("\n"));

    // Check for a minimal amount of lines (at least a header and 3 lines).
    if(lines.length() < 4) {
        qWarning() << "Not enough lines:" << lines.length();
        emit loadFailure(file);
        return;
    }

    auto firstLine(lines[0].split(" "));

    // Check if the header is correctly formatted.
    if(firstLine.length() != 2) {
        qWarning() << "Invalid header:" << firstLine.length();
        emit loadFailure(file);
        return;
    }

    auto size(firstLine[0].toInt());

    // Check if all the lines are present (+ header).
    if(lines.length() != size + 1) {
        qWarning() << "Invalid number of lines:" << lines.length();
        emit loadFailure(file);
        return;
    }

    auto field(initEmptyPlayField(size));

    // Parse the file.
    for(int x(1); x < lines.length(); x++) {
        auto line(lines[x].trimmed().split(" "));

        if(line.length() != size) {
            qWarning() << "Invalid number of values within a line:" << line.length();
            emit loadFailure(file);
            return;
        }

        for(int y(0); y < line.length(); y++) {
            field[x - 1][y] = line[y].toInt();
        }
    }

    _numberOfMoves = firstLine[1].toUInt();
    _size = size;
    _playField = field;

    emit gameCreated(_playField, _numberOfMoves);
}

void Game::saveGame(QFile &file) {
    // Try to open the file for writing
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << "Failed to open for writing:" << file.fileName();
        emit saveFailure(file);
        return;
    }

    QTextStream out(&file);
    out << _size << ' ' << _numberOfMoves << '\n'; // Write the header

    // Write the content
    for(auto const & line : _playField) {
        for(auto const & val : line) {
            out << val << ' ';
        }

        out << '\n';
    }

    file.close();
}

const Game::PlayField &Game::getPlayField() const {
    return _playField;
}

const unsigned int &Game::getNumberOfMoves() const {
    return _numberOfMoves;
}

void Game::enableRiggedMode() {
    _riggedMode = true;
    qDebug() << "Rigged mode enabled.";
}

bool Game::hasWon() const {
    int expected(0);

    for(auto const & line : _playField) {
        for(auto const & val : line) {
            if(val == -1 || val == expected) {
                expected++;
            } else {
                return false;
            }
        }
    }

    return true;
}
