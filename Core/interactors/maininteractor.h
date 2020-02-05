#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include <vector>
#include <models/modelitem.h>

using namespace std;

class MainInteractor
{
public:
    static MainInteractor* getInstance();
    int addNewItem();

private:
    MainInteractor();
    static MainInteractor *instance;
    vector<ModelItem> itemsList;
};

#endif // MAININTERACTOR_H
