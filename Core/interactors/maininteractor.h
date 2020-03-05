#ifndef MAININTERACTOR_H
#define MAININTERACTOR_H

#include <vector>

class NeuronInteractor;
class SinapsInteractor;

class MainInteractor
{
public:
    static MainInteractor* getInstance();
    void run();

private:
    MainInteractor();
    static MainInteractor *instance;
    std::vector<NeuronInteractor *> neuronsList;
    std::vector<SinapsInteractor *> sinapsList;
};

#endif // MAININTERACTOR_H
