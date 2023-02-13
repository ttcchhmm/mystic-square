#ifndef MYSTICSQUARE_NEWGAMEDIALOG_HH
#define MYSTICSQUARE_NEWGAMEDIALOG_HH

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class NewGameDialog; }
QT_END_NAMESPACE

class NewGameDialog : public QDialog {
Q_OBJECT

public:
    explicit NewGameDialog(QWidget *parent = nullptr);

    [[nodiscard]] int getValue() const;

    ~NewGameDialog() override;

private:
    Ui::NewGameDialog *ui;
};


#endif //MYSTICSQUARE_NEWGAMEDIALOG_HH
