#include "maininteractor.h"

#include "interactors/neuroninteractor.h"
#include "interactors/sinapsinteractor.h"
#include "interactors/datainteractor.h"
#include "interactors/perceptroninteractor.h"
#include "interactors/weightinteractor.h"
#include "interactors/coreinteractor.h"
#include "listeners/mainpresentorlistener.h"

MainInteractor::MainInteractor()
{

}

MainInteractor* MainInteractor::getInstance() {
    if (instance == nullptr)
        instance = new MainInteractor();
    return instance;
}

void MainInteractor::setView(MainPresentorListener *listener) {
    view = listener;
}

void MainInteractor::run() {
    for (auto sinaps : sinapsList)
        sinaps->init();

//    ModelItem *data = itemFactory.create(nullptr, ModelItem::Data);
//    SinapsModel *sinaps = sinapsFactory.create(data, itemsList[0], SinapsModel::Weigth);
//    data->addOutputSinaps(sinaps);
//    itemsList[0]->addInputSinaps(sinaps);
//    sinaps->init();

//    dynamic_cast<DataModel *>(data)->sendData();
}

void MainInteractor::createNewPerceptron() {
    PerceptronInteractor *newPerceptron = new PerceptronInteractor();
    neuronsList.push_back(newPerceptron);
    view->onNewPerceptronCreated(newPerceptron);
}

//SinapsModel *MainInteractor::makeSinaps(ModelItem *inputItem, ModelItem *outputItem) {
//    SinapsModel::SinapsType type;

//    if (inputItem->getType() == ModelItem::Perceptron || inputItem->getType() == ModelItem::Data) {
//        type = SinapsModel::Weigth;
//    } else {
//        type = SinapsModel::Core;
//    }

//    SinapsModel *sinaps = sinapsFactory.create(inputItem, outputItem, type);

//    inputItem->addOutputSinaps(sinaps);
//    outputItem->addInputSinaps(sinaps);

//    sinapsModelsList.push_back(sinaps);

//    return sinaps;
//}

//void MainInteractor::removeItem(MoveItemInterface *item) {
//    for(unsigned long i = 0; i < itemsList.size(); i++) {
//        if (itemsList.at(i)->getListener() == item) {
//            itemsList.erase(itemsList.begin() + i);
//            vector<ModelItem *>(itemsList).swap(itemsList);
//            break;
//        }
//    }
//}

//void MainInteractor::removeSinaps(SinapsModel *item) {
//    for(unsigned long i = 0; i < sinapsModelsList.size(); i++) {
//        if (sinapsModelsList.at(i) == item) {
//            sinapsModelsList.erase(sinapsModelsList.begin() + i);
//            vector<SinapsModel *>(sinapsModelsList).swap(sinapsModelsList);
//            break;
//        }
//    }
//}

MainInteractor * MainInteractor::instance;
