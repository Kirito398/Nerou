#include "mainrepository.h"

#include <QImage>
#include <QColor>
#include <QDir>

MainRepository::MainRepository()
{

}

double *MainRepository::loadValue(std::string path) {
    QImage img(QString::fromStdString(path));

    unsigned int width = img.width();
    unsigned int height = img.height();

    double *value = new double[width * height];

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            QColor pixel(img.pixel(i, j));
            value[i * height + j] = (pixel.red() + pixel.green() + pixel.blue()) / 3.0;
        }
    }

    return value;
}

double **MainRepository::loadColorValue(std::string path) {
    QImage img(QString::fromStdString(path));

    unsigned int width = img.width();
    unsigned int height = img.height();

    double **colorValue = new double*[3];
    for (unsigned int i = 0; i < 3; i++)
        colorValue[i] = new double[width * height];

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            QColor pixel(img.pixel(i, j));
            colorValue[0][i * height + j] = pixel.red();
            colorValue[1][i * height + j] = pixel.green();
            colorValue[2][i * height + j] = pixel.blue();
        }
    }

    return colorValue;
}

std::vector<std::string> MainRepository::getPaths(std::string mainPath) {
    std::vector<std::string> list;
    QString mPath = QString::fromStdString(mainPath);

    if (mPath.isEmpty())
        return list;

    QDir dir(mPath);
    QStringList entryList;
    entryList << "*.jpg" << "*.png";

    QStringList listPaths = dir.entryList(entryList);

    for (auto path : listPaths)
        list.push_back((mPath + path).toStdString());

    return list;
}
