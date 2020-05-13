#ifndef TABLEDATAMODEL_H
#define TABLEDATAMODEL_H

class TableDataSetModel;

class TableDataModel
{
public:
    TableDataModel();
    double getX();
    void setX(double value);
    double getY();
    void setY(double value);
    unsigned long getID();
    void setID(unsigned long id);
    bool getIsOutput();
    void setIsOutput(bool enable);
    int getType();
    void setType(int type);
    TableDataSetModel *getDataSet();
    void setDataSet(TableDataSetModel *model);
    int getActivateFunctionType();
    void setActivateFunctionType(int type);
    int getLossFunctionType();
    void setLossFunctionType(int type);

private:
    double posX, posY;
    unsigned long id;
    bool isOutput;
    int type;
    TableDataSetModel *dataSet;
    int activateFunctionType;
    int lossFunctionType;
};

#endif // TABLEDATAMODEL_H
