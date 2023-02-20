#include <QApplication>
#include <QTranslator>
#include <QDebug>

#include "mainwindow.hh"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/assets/icon.png"));

    qSetMessagePattern(QStringLiteral("[%{type} / %{file}:%{line} / %{function} / %{time yyyy-MM-dd h:mm:ss}]: %{message}"));

    QTranslator translator;
    if(translator.load(QLocale(), "MysticSquare", "-")) {
        qDebug() << "Loading translation from" << translator.filePath();
        QCoreApplication::installTranslator(&translator);
    }

    MainWindow m;
    m.show();

    return QApplication::exec();
}
