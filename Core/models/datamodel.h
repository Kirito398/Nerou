#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <vector>

class ClassModel;

class DataModel
{
public:
    DataModel();
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
    bool getIsColorMode();
    void setIsColorMode(bool enable);
    std::vector<ClassModel> getClassList();
    void setClassList(std::vector<ClassModel> list);
    int getActivateFunctionType();
    void setActivateFunctionType(int type);
    int getLossFunctionType();
    void setLossFunctionType(int type);

private:
    double posX, posY;
    unsigned long id;
    bool isOutput;
    int type;
    bool isColorMode;
    std::vector<ClassModel> classList;
    int activateFunctionType;
    int lossFunctionType;
};

#endif // DATAMODEL_H
