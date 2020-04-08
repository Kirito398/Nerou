#ifndef CONVOLUTIONMODEL_H
#define CONVOLUTIONMODEL_H


class ConvolutionModel
{
public:
    ConvolutionModel(unsigned long id);
    unsigned long getID();
    void setID(unsigned long id);
    double getX();
    void setX(double value);
    double getY();
    void setY(double value);
    bool getIsActivateFunctionEnabled();
    void setIsActivateFunctionEnabled(bool enable);
    int getType();
    void setType(int type);

private:
    unsigned long id;
    double posX, posY;
    bool isActivateFunctionEnabled;
    int type;
};

#endif // CONVOLUTIONMODEL_H
