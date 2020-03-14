#ifndef REPOSITORYINTERFACE_H
#define REPOSITORYINTERFACE_H

#include "string"

class RepositoryInterface
{
public:
    virtual double** loadColorValue(std::string path) = 0;
    virtual double* loadValue(std::string path) = 0;
};

#endif // REPOSITORYINTERFACE_H
