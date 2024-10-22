#ifndef MAINREPOSITORY_H
#define MAINREPOSITORY_H

#include "interfaces/repositoryinterface.h"

class MainInteractorInterface;

class MainRepository : public RepositoryInterface
{
public:
    MainRepository();

private:
    std::vector<std::vector<double>> loadValue(std::string path) override;
    std::vector<std::vector<std::vector<double>>> loadColorValue(std::string path) override;
    std::vector<std::string> getPaths(std::string mainPath) override;
    void save(std::string path, std::vector<DataModel> dataModelList, std::vector<PerceptronModel> perceptronModelList, std::vector<ConvolutionModel> convolutionModelList, std::vector<WeightModel> weightModelList, std::vector<CoreModel> coreModelList) override;
    void load(std::string path) override;
    void setInteractor(MainInteractorInterface *interactor) override;

private: MainInteractorInterface *interactor;
};

#endif // MAINREPOSITORY_H
