#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include <vector>
#include <models/modelitem.h>
#include <interfaces/moveiteminterface.h>

using namespace std;

class MainInteractor
{
public:
    static MainInteractor* getInstance();
    ModelItem* addNewItem(MoveItemInterface * listener);

private:
    MainInteractor();
    static MainInteractor *instance;
    vector<ModelItem> itemsList;
};

#endif // MAININTERACTOR_H
