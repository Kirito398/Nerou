#include "views/mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator qtLanguageTranslator;
    qtLanguageTranslator.load(QString("NerouLanguage_") + QString("ru_RU"));
    qApp->installTranslator(&qtLanguageTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
