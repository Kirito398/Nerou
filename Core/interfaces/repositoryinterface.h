#ifndef REPOSITORYINTERFACE_H
#define REPOSITORYINTERFACE_H

#include <string>
#include <vector>

class DataModel;
class PerceptronModel;
class MainInteractorInterface;

class RepositoryInterface
{
public:
    virtual double** loadColorValue(std::string path) = 0;
    virtual double* loadValue(std::string path) = 0;
    virtual std::vector<std::string> getPaths(std::string mainPath) = 0;
    virtual void save(std::string path, std::vector<DataModel> dataModelList, std::vector<PerceptronModel> perceptronModelList) = 0;
    virtual void load(std::string path) = 0;
    virtual void setInteractor(MainInteractorInterface* interactor) = 0;
};

#endif // REPOSITORYINTERFACE_H
