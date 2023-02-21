#include "Game.hh"

Game::Game(const int &size, QObject* parent): QObject(parent), _size(size), _numberOfMoves(0) {}

void Game::newGame(const int &size) {
    _size = size;
    _numberOfMoves = 0;
    emit gameCreated(size);
}
