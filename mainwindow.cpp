#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "newgamedialog.hh"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow), _game(QSharedPointer<Game>::create(3, this)) {
    ui->setupUi(this);

    // -- Connects --
    connect(ui->actionOriginalBackground, &QAction::triggered, this, [this]() {
        emit backgroundUpdated(Background::NUMBERED);
    });

    connect(ui->actionForestBackground, &QAction::triggered, this, [this]() {
        emit backgroundUpdated(Background::FOREST);
    });

    connect(ui->actionNetworkBackground, &QAction::triggered, this, [this]() {
        emit backgroundUpdated(Background::NETWORK);
    });

    connect(ui->actionTreeBackground, &QAction::triggered, this, [this]() {
        emit backgroundUpdated(Background::TREE);
    });

    connect(ui->actionAboutApp, &QAction::triggered, this, &MainWindow::aboutApp);
    connect(ui->actionAboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
    connect(ui->actionQuit, &QAction::triggered, this, &QApplication::quit);
    connect(ui->actionNewGame, &QAction::triggered, this, &MainWindow::newGame);
    connect(ui->actionLoadGame, &QAction::triggered, this, &MainWindow::loadGame);
    connect(ui->actionSaveGame, &QAction::triggered, this, &MainWindow::saveGame);
    connect(this, &MainWindow::backgroundUpdated, ui->playArea, &GameWidget::changeBackground);
    connect(_game.data(), &Game::played, this, &MainWindow::handlePlay);
    connect(_game.data(), &Game::gameCreated, this, &MainWindow::handleNewGame);
    connect(_game.data(), &Game::gameCreated, ui->playArea, &GameWidget::handleNewGame);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::aboutApp() {
    QMessageBox::about(this, tr("About Mystic Square", "Window title"), tr("Mystic Square, by Tom Chedmail. Made as an assignment for the Qt course."));
}

void MainWindow::aboutQt() {
    QMessageBox::aboutQt(this);
}

void MainWindow::newGame() {
    NewGameDialog d;
    d.exec();

    if(d.result() == QDialog::Accepted) {
        qDebug() << "Starting a game with size:" << d.getValue();
        _game->newGame(d.getValue());
    }
}

void MainWindow::loadGame() {
    auto result(QMessageBox::question(this, tr("Overwrite the current game ?", "Window title"), tr("Do you want to overwrite the current game and load a new one ?")));

    if(result == QMessageBox::Yes) {
        auto filename(QFileDialog::getOpenFileName(this, tr("Open game", "Window title"), QDir::homePath(), tr("Saved games (*.save)", "Saved games file type")));

        if(!filename.isEmpty()) {
            qDebug() << "Loading a game from:" << filename;
            QFile f(filename);
            _game->loadGame(f);
        }
    }
}

void MainWindow::saveGame() {
    auto filename(QFileDialog::getSaveFileName(this, tr("Save game", "Window title"), QDir::homePath(), tr("Saved games (*.save)", "Saved games file type")));

    if(!filename.isEmpty()) {
        qDebug() << "Saving a game to:" << filename;
        QFile f(filename);
        _game->saveGame(f);
    }
}

void MainWindow::handlePlay(unsigned int numberOfMoves) {
    this->ui->moveCountLabel->setText(tr("Moves: %1", "Number of moves display").arg(numberOfMoves));
}

void MainWindow::handleNewGame(Game::PlayField & playField) {
    this->ui->moveCountLabel->setText(tr("Moves: %1", "Number of moves display").arg(0));
}
