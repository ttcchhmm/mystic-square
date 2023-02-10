#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->actionAboutApp, &QAction::triggered, this, &MainWindow::aboutApp);
    connect(ui->actionAboutQt, &QAction::triggered, this, &MainWindow::aboutQt);

    connect(ui->actionQuit, &QAction::triggered, this, &QApplication::quit);
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