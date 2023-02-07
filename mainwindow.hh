#ifndef MYSTICSQUARE_MAINWINDOW_HH
#define MYSTICSQUARE_MAINWINDOW_HH

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:
    void aboutApp();
    void aboutQt();

private:
    Ui::MainWindow *ui;
};


#endif //MYSTICSQUARE_MAINWINDOW_HH
