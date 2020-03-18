#ifndef MAINREPOSITORY_H
#define MAINREPOSITORY_H

#include "interfaces/repositoryinterface.h"

class MainRepository : public RepositoryInterface
{
public:
    MainRepository();

private:
    double *loadValue(std::string path) override;
    double **loadColorValue(std::string path) override;
    std::vector<std::string> getPaths(std::string mainPath) override;
};

#endif // MAINREPOSITORY_H
