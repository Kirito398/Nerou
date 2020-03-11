#ifndef REPOSITORYINTERFACE_H
#define REPOSITORYINTERFACE_H

#include "string"

class RepositoryInterface
{
public:
    virtual void loadValue(std::string path, double** colorValue) = 0;
    virtual void loadValue(std::string path, double* value);
};

#endif // REPOSITORYINTERFACE_H
