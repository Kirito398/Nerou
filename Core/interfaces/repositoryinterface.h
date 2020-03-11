#ifndef REPOSITORYINTERFACE_H
#define REPOSITORYINTERFACE_H

#include "string"

class RepositoryInterface
{
public:
    virtual void loadValue(std::string path, double* red, double* green, double* blue, unsigned int* row, unsigned int* column) = 0;
    virtual void loadValue(std::string path, double* value, unsigned int* row, unsigned int* column);
};

#endif // REPOSITORYINTERFACE_H
