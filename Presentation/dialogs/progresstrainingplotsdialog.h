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

private:
    void initLossChart();
    void initAccuracyChart();

private:
    QBoxLayout *layout;
    QLineSeries *lossSeries;
    QLineSeries *accuracySeries;
    QValueAxis *lossAxisX;
    QValueAxis *lossAxisY;
    QValueAxis *accuracyAxisX;
    QValueAxis *accuracyAxisY;
    qreal xStep, yStep;
};

#endif // PROGRESSTRAININGPLOTSDIALOG_H
