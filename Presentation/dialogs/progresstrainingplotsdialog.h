#ifndef PROGRESSTRAININGPLOTSDIALOG_H
#define PROGRESSTRAININGPLOTSDIALOG_H

#include <QDialog>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE

class QBoxLayout;

class ProgressTrainingPlotsDialog : public QDialog
{
    Q_OBJECT
public:
    ProgressTrainingPlotsDialog();
    void addNewLoss(double value);
    void addNewAccuracy(double value);
    void addNewTotalLoss(double value);
    void resetData();

private:
    void initLossChart();
    void initAccuracyChart();
    void initTotalLossChart();

private:
    QBoxLayout *layout;

    QLineSeries *lossSeries;
    QLineSeries *accuracySeries;
    QLineSeries *totalLossSeries;

    QValueAxis *lossAxisX;
    QValueAxis *lossAxisY;

    QValueAxis *accuracyAxisX;
    QValueAxis *accuracyAxisY;

    QValueAxis *totalLossAxisX;
    QValueAxis *totalLossAxisY;

    qreal xStep, yStep;
};

#endif // PROGRESSTRAININGPLOTSDIALOG_H
