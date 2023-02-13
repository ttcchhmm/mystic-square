#include "newgamedialog.hh"
#include "ui_newgamedialog.h"


NewGameDialog::NewGameDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::NewGameDialog) {
    ui->setupUi(this);
}

NewGameDialog::~NewGameDialog() {
    delete ui;
}

int NewGameDialog::getValue() const {
    return ui->squareSizeSpin->value();
}
