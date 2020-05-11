#include "mainrepository.h"

#include <QImage>
#include <QColor>
#include <QDir>
#include <QTextStream>

#include "models/datamodel.h"
#include "models/classmodel.h"
#include "models/perceptronmodel.h"
#include "models/convolutionmodel.h"
#include "models/weightmodel.h"
#include "models/coremodel.h"
#include "interfaces/maininteractorinterface.h"

MainRepository::MainRepository()
{

}

std::vector<std::vector<std::string>> MainRepository::loadTableValue(std::string path) {
    QFile *file = new QFile(QString::fromStdString(path));
    file->open(QIODevice::ReadOnly);
    QTextStream in(file);

    std::vector<std::vector<std::string>> vector;

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList list = line.split(";");

        std::vector<std::string> newSet;
        for (QString item : list) {
            item.replace(',', '.');
            newSet.push_back(item.toStdString());
        }

        vector.push_back(newSet);
    }

    file->close();

    return vector;
}

void MainRepository::save(std::string path, std::vector<DataModel> dataModelList, std::vector<PerceptronModel> perceptronModelList, std::vector<ConvolutionModel> convolutionModelList, std::vector<WeightModel> weightModelList, std::vector<CoreModel> coreModelList) {
    QFile *file = new QFile(QString::fromStdString(path));
    file->open(QIODevice::WriteOnly);
    QDataStream out(file);

    size_t dataSize = dataModelList.size();
    size_t perceptronSize = perceptronModelList.size();
    size_t convolutionSize = convolutionModelList.size();
    size_t weightSize = weightModelList.size();
    size_t coreSize = coreModelList.size();

    out << QString::number(dataSize) << QString::number(perceptronSize) << QString::number(convolutionSize) << QString::number(weightSize) << QString::number(coreSize);

    for (size_t i = 0; i < perceptronSize; i++) {
        PerceptronModel model = perceptronModelList.at(i);
        out << model.getX()
            << model.getY()
            << QString::number(model.getID())
            << model.getType()
            << model.getIsOutput()
            << model.getActivateFunctionType();
    }

    for (size_t i = 0; i < convolutionSize; i++) {
        ConvolutionModel model = convolutionModelList.at(i);
        out << model.getX()
            << model.getY()
            << QString::number(model.getID())
            << model.getType()
            << model.getIsActivateFunctionEnabled()
            << model.getActivateFunctionType();
    }

    for (size_t i = 0; i < dataSize; i++) {
        DataModel model = dataModelList.at(i);
        out << model.getX()
            << model.getY()
            << QString::number(model.getID())
            << model.getType()
            << model.getIsOutput()
            << model.getIsColorMode()
            << model.getActivateFunctionType()
            << model.getLossFunctionType();

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

    for (size_t i = 0; i < weightSize; i++) {
        WeightModel model = weightModelList.at(i);
        out << QString::number(model.getID())
            << model.getType()
            << model.getWeight()
            << QString::number(model.getInputNeuronID())
            << QString::number(model.getOutputNeuronID());
    }

    for (size_t i = 0; i < coreSize; i++) {
        CoreModel model = coreModelList.at(i);
        out << QString::number(model.getID())
            << model.getType()
            << QString::number(model.getCoreSize())
            << QString::number(model.getInputNeuronID())
            << QString::number(model.getOutputNeuronID())
            << model.getIsMaxPoolingEnable()
            << QString::number(model.getMaxPoolingCoreSize());

        std::vector<std::vector<double>> weight = model.getWeight();
        size_t row = weight.size();
        size_t column = weight[0].size();

        out << QString::number(row) << QString::number(column);

        for (size_t k = 0; k < row; k++)
            for (size_t j = 0; j < column; j++)
                out << weight[k][j];
    }

    file->close();
    delete file;
}

void MainRepository::load(std::string path) {
    QFile *file = new QFile(QString::fromStdString(path));
    file->open(QIODevice::ReadOnly);
    QDataStream in(file);

    QString data, perceptron, convolution, weight, core;
    in >> data >> perceptron >> convolution >> weight >> core;

    size_t dataSize = data.toULong();
    size_t perceptronSize = perceptron.toULong();
    size_t convolutionSize = convolution.toULong();
    size_t weightSize = weight.toULong();
    size_t coreSize = core.toULong();

    for (size_t i = 0; i < perceptronSize; i++) {
        double posX, posY;
        QString neuronID;
        int type, activateFunctionType;
        bool isOutput;

        in >> posX
                >> posY
                >> neuronID
                >> type
                >> isOutput
                >> activateFunctionType;

        PerceptronModel model;
        model.setX(posX);
        model.setY(posY);
        model.setID(neuronID.toULong());
        model.setType(type);
        model.setIsOutput(isOutput);
        model.setActivateFunctionType(activateFunctionType);

        interactor->onPerceptronModelLoaded(model);
    }

    for (size_t i = 0; i < convolutionSize; i++) {
        double posX, posY;
        QString neuronID;
        int type, activateFunctionType;
        bool isActivateFunctionEnabled;

        in >> posX
                >> posY
                >> neuronID
                >> type
                >> isActivateFunctionEnabled
                >> activateFunctionType;

        ConvolutionModel model(neuronID.toULong());
        model.setX(posX);
        model.setY(posY);
        model.setType(type);
        model.setIsActivateFunctionEnabled(isActivateFunctionEnabled);
        model.setActivateFunctionType(activateFunctionType);

        interactor->onConvolutionModelLoaded(model);
    }

    for (size_t i = 0; i < dataSize; i++) {
        double posX, posY;
        QString neuronID;
        int type, activateFunctionType, lossFunctionType;
        bool isOutput, isColorMode;

        in >> posX >> posY
                >> neuronID
                >> type
                >> isOutput
                >> isColorMode
                >> activateFunctionType
                >> lossFunctionType;

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
        model.setActivateFunctionType(activateFunctionType);
        model.setLossFunctionType(lossFunctionType);

        interactor->onDataModelLoaded(model);
    }

    for (size_t i = 0; i < weightSize; i++) {
        QString sinapsID, inputNeuronID, outputNeuronID;
        int type;
        double weight;

        in >> sinapsID
                >> type
                >> weight
                >> inputNeuronID
                >> outputNeuronID;

        WeightModel newSinaps(sinapsID.toULong());
        newSinaps.setType(type);
        newSinaps.setWeight(weight);
        newSinaps.setInputNeuronID(inputNeuronID.toULong());
        newSinaps.setOutputNeuronID(outputNeuronID.toULong());

        interactor->onWeightModelLoaded(newSinaps);
    }

    for (size_t i = 0; i < coreSize; i++) {
        QString sinapsID, cSize, inputNeuronID, outputNeuronID, maxPoolingCoreSize;
        int type;
        bool isMaxPoolingEnable;

        in >> sinapsID
                >> type
                >> cSize
                >> inputNeuronID
                >> outputNeuronID
                >> isMaxPoolingEnable
                >> maxPoolingCoreSize;

        QString rowS, columnS;

        in >> rowS >> columnS;

        size_t row = rowS.toULong();
        size_t column = columnS.toULong();
        std::vector<std::vector<double>> weight;

        for (size_t i = 0; i < row; i++)
            weight.push_back(std::vector<double>(column));

        for (size_t i = 0; i < row; i++)
            for (size_t j = 0; j < column; j++)
                in >> weight[i][j];

        CoreModel model(sinapsID.toULong());
        model.setType(type);
        model.setWeight(weight);
        model.setCoreSize(cSize.toULong());
        model.setInputNeuronID(inputNeuronID.toULong());
        model.setOutputNeuronID(outputNeuronID.toULong());
        model.setIsMaxPoolingEnable(isMaxPoolingEnable);
        model.setMaxPoolingCoreSize(maxPoolingCoreSize.toULong());

        interactor->onCoreModelLoaded(model);
    }

    file->close();
    delete file;
}

void MainRepository::setInteractor(MainInteractorInterface *interactor) {
    this->interactor = interactor;
}

std::vector<std::vector<double> > MainRepository::loadValue(std::string path) {
    QImage img(QString::fromStdString(path));

    unsigned int width = img.width();
    unsigned int height = img.height();

    std::vector<std::vector<double>> value;
    for (unsigned int i = 0; i < width; i++)
        value.push_back(std::vector<double>(height));

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            QColor pixel(img.pixel(i, j));
            value[i][j] = (pixel.red() + pixel.green() + pixel.blue()) / 3.0;
        }
    }

    return value;
}

std::vector<std::vector<std::vector<double> > > MainRepository::loadColorValue(std::string path) {
    QImage img(QString::fromStdString(path));

    unsigned int width = img.width();
    unsigned int height = img.height();

    std::vector<std::vector<std::vector<double>>> colorValue;
    for (unsigned int i = 0; i < 3; i++)
        colorValue.push_back(std::vector<std::vector<double>>());

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned j = 0; j < height; j++) {
            QColor pixel(img.pixel(i, j));
            colorValue[0][i][j] = pixel.red();
            colorValue[1][i][j] = pixel.green();
            colorValue[2][i][j] = pixel.blue();
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
