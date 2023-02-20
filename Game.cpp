#include "Game.hh"

Game::Game(const int &size, QObject* parent): QObject(parent), _size(size), _numberOfMoves(0) {}
