#ifndef REPOSITORYINTERFACE_H
#define REPOSITORYINTERFACE_H

#include <string>
#include <vector>

class DataModel;
class PerceptronModel;
class MainInteractorInterface;
class WeightModel;
class ConvolutionModel;
class CoreModel;

class RepositoryInterface
{
public:
    virtual std::vector<std::vector<std::vector<double>>> loadColorValue(std::string path) = 0;
    virtual std::vector<std::vector<double>> loadValue(std::string path) = 0;
    virtual std::vector<std::string> getPaths(std::string mainPath) = 0;
    virtual void save(std::string path, std::vector<DataModel> dataModelList, std::vector<PerceptronModel> perceptronModelList, std::vector<ConvolutionModel> convolutionModelList, std::vector<WeightModel> weightModelList, std::vector<CoreModel> coreModelList) = 0;
    virtual void load(std::string path) = 0;
    virtual void setInteractor(MainInteractorInterface* interactor) = 0;
    virtual std::vector<std::vector<std::string>> loadTableValue(std::string path) = 0;
};

#endif // REPOSITORYINTERFACE_H
