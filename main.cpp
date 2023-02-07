#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    if(translator.load(QLocale(), "MysticSquare", "-")) {
        qDebug() << "Loading translation from" << translator.filePath();
        QCoreApplication::installTranslator(&translator);
    }

    return QApplication::exec();
}
