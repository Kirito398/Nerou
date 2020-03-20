#ifndef PROGRESSTRAININGDIALOG_H
#define PROGRESSTRAININGDIALOG_H

#include <QDialog>

class QBoxLayout;
class QLabel;
class QProgressBar;

class ProgressTrainingDialog : public QDialog
{
    Q_OBJECT
public:
    ProgressTrainingDialog();
    ~ProgressTrainingDialog();
    void setMaxEpoh(unsigned int maxEpoh);
    void setMaxIteration(unsigned int maxIteration);
    void setTotalProcess(unsigned int total);
    void setCurrentEpoh(unsigned int currentEpoh);
    void setCurrentIteration(unsigned int currentIteration);
    void onTrainingFinished();

private:
    void initTimer();
    void initEpohLayer();
    void initIterationLayer();
    void updateTotalProgressBar();

private:
    QProgressBar *totalProgressBar;
    QTimer *timer;
    QBoxLayout *layout;
    QLabel *lTime, *lEpoh, *lIteration;
    unsigned long seconds;
    unsigned int maxEpoh, maxIteration, currentEpoh, currentIteration;

private slots:
    void onTimeout();
};

#endif // PROGRESSTRAININGDIALOG_H