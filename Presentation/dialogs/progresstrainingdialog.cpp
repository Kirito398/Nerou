#include "progresstrainingdialog.h"

#include <QBoxLayout>
#include <QProgressBar>
#include <QTimer>
#include <QLabel>

ProgressTrainingDialog::ProgressTrainingDialog()
{
    setWindowTitle(tr("Training progress"));
    setFixedSize(QSize(200, 150));

    layout = new QVBoxLayout();

    initTimer();

    initEpohLayer();
    initIterationLayer();
    initErrorLayer();

    totalProgressBar = new QProgressBar();
    totalProgressBar->setMinimum(0);
    totalProgressBar->setValue(0);

    layout->addWidget(totalProgressBar);

    maxEpoh = 1;
    maxIteration = 1;

    setLayout(layout);
}

void ProgressTrainingDialog::setMaxEpoh(unsigned int maxEpoh) {
    this->maxEpoh = maxEpoh;
}

void ProgressTrainingDialog::setMaxIteration(unsigned int maxIteration) {
    this->maxIteration = maxIteration;
}

void ProgressTrainingDialog::updateTotalProgressBar() {
    totalProgressBar->setValue((currentEpoh - 1) * maxIteration + currentIteration);
}

void ProgressTrainingDialog::setCurrentEpoh(unsigned int currentEpoh) {
    this->currentEpoh = currentEpoh;
    lEpoh->setText(QString::number(currentEpoh) + " / " + QString::number(maxEpoh));
    updateTotalProgressBar();
}

void ProgressTrainingDialog::setCurrentIteration(unsigned int currentIteration) {
    this->currentIteration = currentIteration;
    lIteration->setText(QString::number(currentIteration) + " / " + QString::number(maxIteration));
    updateTotalProgressBar();
}

void ProgressTrainingDialog::setCurrentError(double value) {
    lError->setText(QString::number(value));
}

void ProgressTrainingDialog::onTrainingFinished() {
    timer->stop();
    seconds = 0;
}

void ProgressTrainingDialog::initErrorLayer() {
    QBoxLayout *errorLayout = new QHBoxLayout();

    lError = new QLabel("0.0");
    QLabel *title = new QLabel(tr("Error: "));

    errorLayout->addWidget(title);
    errorLayout->addWidget(lError);
    layout->addLayout(errorLayout);
}

void ProgressTrainingDialog::initEpohLayer() {
    QBoxLayout *epohLayout = new QHBoxLayout();

    lEpoh = new QLabel("0 / 0");
    QLabel *title = new QLabel(tr("Epoh: "));

    epohLayout->addWidget(title);
    epohLayout->addWidget(lEpoh);
    layout->addLayout(epohLayout);
}

void ProgressTrainingDialog::initIterationLayer() {
    QBoxLayout *iterationLayout = new QHBoxLayout();

    lIteration = new QLabel("0 / 0");
    QLabel *title = new QLabel(tr("Iteration: "));

    iterationLayout->addWidget(title);
    iterationLayout->addWidget(lIteration);
    layout->addLayout(iterationLayout);
}

void ProgressTrainingDialog::setTotalProcess(unsigned int total) {
    totalProgressBar->setMaximum(total);
}

void ProgressTrainingDialog::initTimer() {
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ProgressTrainingDialog::onTimeout);
    timer->start(1000);
    seconds = 0;

    QHBoxLayout *timerLayout = new QHBoxLayout;
    QLabel *timerLabel = new QLabel(tr("Time: "));
    lTime = new QLabel("00:00:00");

    timerLayout->addWidget(timerLabel);
    timerLayout->addWidget(lTime);

    layout->addLayout(timerLayout);
}

void ProgressTrainingDialog::onTimeout() {
    seconds += 1;

    QString hours = QString::number(seconds / 3600);
    QString minuts = QString::number(seconds / 60);
    QString second = QString::number(seconds % 60);

    if (hours.length() == 1)
        hours.push_front("0");

    if (minuts.length() == 1)
        minuts.push_front("0");

    if (second.length() == 1)
        second.push_front("0");

    lTime->setText(hours + ":" + minuts + ":" + second);
}

ProgressTrainingDialog::~ProgressTrainingDialog() {
    timer->stop();
    delete timer;
}
