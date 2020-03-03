#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include "factories/itemfactory.h"

class MainInteractor
{
public:
    static MainInteractor* getInstance();
    ModelItem* addNewItem(MoveItemInterface *listener, ModelItem::ItemType type);
    void removeItem(MoveItemInterface *item);
    SinapsModel *makeSinaps(ModelItem *inputItem, ModelItem *outputItem);
    void removeSinaps(SinapsModel *item);
    void run();

private:
    MainInteractor();
    static MainInteractor *instance;
    vector<ModelItem *> itemsList;
    vector<SinapsModel *> sinapsModelsList;
    ItemFactory itemFactory;
};

#endif // MAININTERACTOR_H
