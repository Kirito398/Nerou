#include "views/mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtLanguageTranslator;
    qtLanguageTranslator.load(":/language/NerouLanguage_ru_RU.qm");
    qApp->installTranslator(&qtLanguageTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
