#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include "newgamedialog.hh"

#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // -- Connects --
    connect(ui->actionAboutApp, &QAction::triggered, this, &MainWindow::aboutApp);
    connect(ui->actionAboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
    connect(ui->actionQuit, &QAction::triggered, this, &QApplication::quit);
    connect(ui->actionNewGame, &QAction::triggered, this, &MainWindow::newGame);
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
        // TODO : Start game
    }
}
