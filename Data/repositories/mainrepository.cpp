#include "mainrepository.h"

#include <QImage>
#include <QColor>
#include <QDir>

#include "models/datamodel.h"
#include "models/classmodel.h"
#include "models/perceptronmodel.h"
#include "interfaces/maininteractorinterface.h"

MainRepository::MainRepository()
{

}

void MainRepository::save(std::string path, std::vector<DataModel> dataModelList, std::vector<PerceptronModel> perceptronModelList) {
    QFile *file = new QFile(QString::fromStdString(path));
    file->open(QIODevice::WriteOnly);
    QDataStream out(file);

    size_t dataSize = dataModelList.size();
    size_t perceptronSize = perceptronModelList.size();

    out << QString::number(dataSize) << QString::number(perceptronSize);

    for (size_t i = 0; i < perceptronSize; i++) {
        PerceptronModel model = perceptronModelList.at(i);
        out << model.getX()
            << model.getY()
            << QString::number(model.getID())
            << model.getType()
            << model.getIsOutput();
    }

    for (size_t i = 0; i < dataSize; i++) {
        DataModel model = dataModelList.at(i);
        out << model.getX()
            << model.getY()
            << QString::number(model.getID())
            << model.getType()
            << model.getIsOutput()
            << model.getIsColorMode();

        std::vector<ClassModel> classList = model.getClassList();
        size_t classSize = classList.size();
        out << QString::number(classSize);

        for (size_t j = 0; j < classSize; j++) {
            ClassModel classModel = classList.at(j);
            out << QString::number(classModel.getNeuronID())
                << QString::fromStdString(classModel.getTestingMainPath())
                << QString::fromStdString(classModel.getTrainingMainPath());
        }
    }

    file->close();
    delete file;
}

void MainRepository::load(std::string path) {
    QFile *file = new QFile(QString::fromStdString(path));
    file->open(QIODevice::ReadOnly);
    QDataStream in(file);

    QString data, perceptron;
    in >> data >> perceptron;

    size_t dataSize = data.toULong();
    size_t perceptronSize = perceptron.toULong();

    for (size_t i = 0; i < perceptronSize; i++) {
        double posX, posY;
        QString neuronID;
        int type;
        bool isOutput;

        in >> posX
                >> posY
                >> neuronID
                >> type
                >> isOutput;

        PerceptronModel model;
        model.setX(posX);
        model.setY(posY);
        model.setID(neuronID.toULong());
        model.setType(type);
        model.setIsOutput(isOutput);

        interactor->onPerceptronModelLoaded(model);
    }

    for (size_t i = 0; i < dataSize; i++) {
        double posX, posY;
        QString neuronID;
        int type;
        bool isOutput, isColorMode;

        in >> posX >> posY
                >> neuronID
                >> type
                >> isOutput
                >> isColorMode;

        std::vector<ClassModel> classList;
        QString size;

        in >> size;

        size_t classSize = size.toULong();

        for (size_t j = 0; j < classSize; j++) {
            QString neuronID, testingMainPath, trainingMainPath;

            in >> neuronID >> testingMainPath >> trainingMainPath;

            ClassModel newClass(neuronID.toULong());
            newClass.setTestingMainPath(testingMainPath.toStdString());
            newClass.setTestingPathslist(getPaths(testingMainPath.toStdString()));
            newClass.setTrainingMainPath(trainingMainPath.toStdString());
            newClass.setTrainingPathsList(getPaths(trainingMainPath.toStdString()));

            classList.push_back(newClass);
        }

        DataModel model;
        model.setX(posX);
        model.setY(posY);
        model.setID(neuronID.toULong());
        model.setType(type);
        model.setIsOutput(isOutput);
        model.setClassList(classList);
        model.setIsColorMode(isColorMode);

        interactor->onDataModelLoaded(model);
    }

    file->close();
    delete file;
}

void MainRepository::setInteractor(MainInteractorInterface *interactor) {
    this->interactor = interactor;
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
    entryList << "*.jpg" << "*.png" << "*.bmp";

    QStringList listPaths = dir.entryList(entryList);

    for (auto path : listPaths)
        list.push_back((mPath + path).toStdString());

    return list;
}
