#include "convolutionpresentor.h"

#include <QImage>
#include <QColor>

#include "listeners/convolutioninteractorlistener.h"
#include "listeners/convolutionviewlistener.h"

ConvolutionPresentor::ConvolutionPresentor()
{
    interactor = nullptr;
    view = nullptr;
}

void ConvolutionPresentor::setView(ConvolutionViewListener *listener) {
    view = listener;
}

void ConvolutionPresentor::setInteractor(ConvolutionInteractorListener *listener) {
    interactor = listener;
    interactor->setView(this);
}

void ConvolutionPresentor::setPosition(double x, double y) {
    interactor->setPosition(x, y);
}

void ConvolutionPresentor::setOutValue(std::vector<std::vector<double> > value) {
    if (value.empty()) {
        view->setOutValue(QImage());
        return;
    }

    unsigned int row = value.size();
    unsigned int column = value[0].size();

    QImage img(QSize(column, row), QImage::Format_RGB32);

    for (unsigned int i = 0; i < row; i++)
        for (unsigned int j = 0; j < column; j++) {
            int pixel = value[i][j] * 255;
            img.setPixel(i, j, QColor(pixel ,pixel, pixel).rgb());
        }

    view->setOutValue(img);
}

unsigned long ConvolutionPresentor::getID() {
    return interactor->getID();
}

void ConvolutionPresentor::updatePosition(double x, double y) {
    view->updatePosition(x, y);
}

void ConvolutionPresentor::setActive(bool enable) {
    view->setActive(enable);
}

int ConvolutionPresentor::getActivateFunctionType() {
    return  interactor->getActivateFunctionType();
}

void ConvolutionPresentor::setActivateFunctionType(int type) {
    interactor->setActivateFunctionType(type);
}

void ConvolutionPresentor::setCoreSize(int size) {
    interactor->setCoreSize(size);
}

int ConvolutionPresentor::getCoreSize() {
    return interactor->getCoreSize();
}

void ConvolutionPresentor::setPoolCoreSize(int size) {
    interactor->setPoolCoreSize(size);
}

int ConvolutionPresentor::getPoolCoreSize() {
    return interactor->getPoolCoreSize();
}

ConvolutionPresentor::~ConvolutionPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();
}
