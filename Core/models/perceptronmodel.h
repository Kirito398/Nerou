#ifndef PERCEPTRONMODEL_H
#define PERCEPTRONMODEL_H


class PerceptronModel
{
public:
    PerceptronModel();
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
    int getActivateFunctionType();
    void setActivateFunctionType(int type);

private:
    double posX, posY;
    unsigned long id;
    bool isOutput;
    int type;
    int activateFunctionType;
};

#endif // PERCEPTRONMODEL_H
