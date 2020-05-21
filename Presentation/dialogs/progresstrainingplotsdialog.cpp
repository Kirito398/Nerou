#include "progresstrainingplotsdialog.h"

#include <QBoxLayout>
#include <QChartView>
#include <QValueAxis>

ProgressTrainingPlotsDialog::ProgressTrainingPlotsDialog()
{
    setWindowTitle(tr("Training progress plots"));
    resize(QSize(1024, 720));

    xStep = 25;
    yStep = 0.25;

    layout = new QVBoxLayout();

    initLossChart();
    initAccuracyChart();
    initTotalLossChart();

    setLayout(layout);
}

void ProgressTrainingPlotsDialog::resetData() {
    resetEpohData();
    totalTrainingLossSeries->clear();
    totalTestingLossSeries->clear();
}

void ProgressTrainingPlotsDialog::resetEpohData() {
    lossSeries->clear();
    accuracySeries->clear();
}

void ProgressTrainingPlotsDialog::initLossChart() {
    QChart *lossChart = new QChart();
    lossChart->setAnimationOptions(QChart::NoAnimation);
    lossChart->legend()->setVisible(false);

    QChartView *chartView = new QChartView(lossChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    lossAxisX = new QValueAxis();
    lossAxisX->setTitleText(tr("Iteration"));
    lossAxisX->setRange(0, xStep);

    lossAxisY = new QValueAxis();
    lossAxisY->setTitleText(tr("Loss"));
    lossAxisY->setRange(0, yStep);

    lossSeries = new QLineSeries(this);
    lossSeries->setName(tr("Loss Function"));
    lossSeries->setUseOpenGL(true);

    lossChart->addSeries(lossSeries);
    lossChart->setTitle(tr("Loss function chart"));
    lossChart->addAxis(lossAxisX, Qt::AlignBottom);
    lossChart->addAxis(lossAxisY, Qt::AlignLeft);
    lossSeries->attachAxis(lossAxisX);
    lossSeries->attachAxis(lossAxisY);

    layout->addWidget(chartView);
}

void ProgressTrainingPlotsDialog::initAccuracyChart() {
    QChart *accuracyChart = new QChart();
    accuracyChart->setAnimationOptions(QChart::NoAnimation);
    accuracyChart->legend()->setVisible(false);

    QChartView *chartView = new QChartView(accuracyChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    accuracyAxisX = new QValueAxis();
    accuracyAxisX->setTitleText(tr("Iteration"));
    accuracyAxisX->setRange(0, xStep);

    accuracyAxisY = new QValueAxis();
    accuracyAxisY->setTitleText(tr("Accuracy"));
    accuracyAxisY->setRange(0, 1.0);

    accuracySeries = new QLineSeries(this);
    accuracySeries->setName(tr("Accuracy"));
    accuracySeries->setUseOpenGL(true);

    accuracyChart->addSeries(accuracySeries);
    accuracyChart->setTitle(tr("Accuracy chart"));
    accuracyChart->addAxis(accuracyAxisX, Qt::AlignBottom);
    accuracyChart->addAxis(accuracyAxisY, Qt::AlignLeft);
    accuracySeries->attachAxis(accuracyAxisX);
    accuracySeries->attachAxis(accuracyAxisY);

    layout->addWidget(chartView);
}

void ProgressTrainingPlotsDialog::initTotalLossChart() {
    QChart *totalLossChart = new QChart();
    totalLossChart->setAnimationOptions(QChart::NoAnimation);
    totalLossChart->legend()->setVisible(false);

    QChartView *chartView = new QChartView(totalLossChart);
    chartView->setRenderHint(QPainter::Antialiasing);

    totalLossAxisX = new QValueAxis();
    totalLossAxisX->setTitleText(tr("Epoh"));
    totalLossAxisX->setRange(0, 4);

    totalLossAxisY = new QValueAxis();
    totalLossAxisY->setTitleText(tr("Loss"));
    totalLossAxisY->setRange(0, 0.5);

    totalTrainingLossSeries = new QLineSeries(this);
    totalTrainingLossSeries->setName(tr("Total training Loss"));
    totalTrainingLossSeries->setUseOpenGL(true);

    totalTestingLossSeries = new QLineSeries(this);
    totalTestingLossSeries->setName(tr("Total testing loss"));
    totalTestingLossSeries->setUseOpenGL(true);

    totalLossChart->addSeries(totalTrainingLossSeries);
    totalLossChart->addSeries(totalTestingLossSeries);
    totalLossChart->setTitle(tr("Total loss chart"));
    totalLossChart->addAxis(totalLossAxisX, Qt::AlignBottom);
    totalLossChart->addAxis(totalLossAxisY, Qt::AlignLeft);
    totalTrainingLossSeries->attachAxis(totalLossAxisX);
    totalTrainingLossSeries->attachAxis(totalLossAxisY);
    totalTestingLossSeries->attachAxis(totalLossAxisX);
    totalTestingLossSeries->attachAxis(totalLossAxisY);

    layout->addWidget(chartView);
}

void ProgressTrainingPlotsDialog::addNewTrainingTotalLoss(double value) {
    totalTrainingLossSeries->append(totalTrainingLossSeries->points().size(), value);

    qreal max = totalLossAxisX->max();
    if (totalTrainingLossSeries->points().size() > max)
        totalLossAxisX->setRange(0, max + 3);

    max = totalLossAxisY->max();
    if (value > max)
        totalLossAxisY->setRange(totalLossAxisY->min(), value + yStep);

    qreal min = totalLossAxisY->min();
    if (value < min)
        totalLossAxisY->setRange(value - yStep, totalLossAxisY->max());
}

void ProgressTrainingPlotsDialog::addNewTestingTotalLoss(double value) {
    totalTestingLossSeries->append(totalTestingLossSeries->points().size(), value);

    qreal max = totalLossAxisX->max();
    if (totalTestingLossSeries->points().size() > max)
        totalLossAxisX->setRange(0, max + 3);

    max = totalLossAxisY->max();
    if (value > max)
        totalLossAxisY->setRange(totalLossAxisY->min(), value + yStep);

    qreal min = totalLossAxisY->min();
    if (value < min)
        totalLossAxisY->setRange(value - yStep, totalLossAxisY->max());
}

void ProgressTrainingPlotsDialog::addNewLoss(double value) {
    lossSeries->append(lossSeries->points().size(), value);

    qreal max = lossAxisX->max();
    if (lossSeries->points().size() > max)
        lossAxisX->setRange(0, max + xStep);

    max = lossAxisY->max();
    if (value > max)
        lossAxisY->setRange(lossAxisY->min(), value + yStep);

    qreal min = lossAxisY->min();
    if (value < min)
        lossAxisY->setRange(value - yStep, lossAxisY->max());
}

void ProgressTrainingPlotsDialog::addNewAccuracy(double value) {
    accuracySeries->append(accuracySeries->points().size(), value);

    qreal max = accuracyAxisX->max();
    if (accuracySeries->points().size() > max)
        accuracyAxisX->setRange(0, max + xStep);

    max = accuracyAxisY->max();
    if (value > max)
        accuracyAxisY->setRange(accuracyAxisY->min(), value + yStep);

    qreal min = accuracyAxisY->min();
    if (value < min)
        accuracyAxisY->setRange(value - yStep, accuracyAxisY->max());
}
