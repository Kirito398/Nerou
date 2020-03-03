#ifndef DATAMODEL_H
#define DATAMODEL_H

#include "models/modelitem.h"

class DataModel : public ModelItem
{
public:
    DataModel(MoveItemInterface *listener);
    void onInputSignalChanged() override;
    void sendData();
};

#endif // DATAMODEL_H
