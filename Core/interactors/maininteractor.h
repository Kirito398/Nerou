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
    int addNewItem(MoveItemInterface * listener);
    void setItemPosition(float posX, float posY);
    void setCurrentItem(string objectName);

private:
    MainInteractor();
    static MainInteractor *instance;
    vector<ModelItem> itemsList;
    ModelItem *currentItem = nullptr;
    void setCurrentItem(ModelItem *item);
};

#endif // MAININTERACTOR_H
