#include <QApplication>
#include <QTranslator>
#include <QCommandLineParser>

#include "Game.hh"
#include "mainwindow.hh"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    qSetMessagePattern(QStringLiteral("[%{type} / %{file}:%{line} / %{function} / %{time yyyy-MM-dd h:mm:ss}]: %{message}"));

    QTranslator translator;
    if(translator.load(QLocale(), "MysticSquare", "-")) {
        qDebug() << "Loading translation from" << translator.filePath();
        QCoreApplication::installTranslator(&translator);
    }

    QApplication::setApplicationName("MysticSquare");
    QApplication::setApplicationDisplayName(QApplication::tr("Mystic Square", "Application display name"));
    QApplication::setWindowIcon(QIcon(":/assets/icon.png"));

    QCommandLineParser parser;
    parser.setApplicationDescription(QApplication::tr("An implementation of the \"Mystic Square\" game."));
    parser.addVersionOption();
    parser.addHelpOption();

    QCommandLineOption riggedMode(QStringList() << "r" << "rigged",
                                  QApplication::tr("Enable rigged mode. This makes all generated games to not be random.", "Help option"));
    parser.addOption(riggedMode);
    parser.process(a);

    if(parser.isSet(riggedMode)) {
        Game::enableRiggedMode();
    }

    MainWindow m;
    m.show();

    return QApplication::exec();
}
