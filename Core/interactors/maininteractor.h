#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include <vector>
#include <models/perceptronmodel.h>
#include <models/sinapsmodel.h>
#include <interfaces/moveiteminterface.h>

using namespace std;

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
};

#endif // MAININTERACTOR_H
