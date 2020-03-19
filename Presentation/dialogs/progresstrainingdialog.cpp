#include "progresstrainingdialog.h"

#include <QBoxLayout>
#include <QProgressBar>
#include <QTimer>
#include <QLabel>

ProgressTrainingDialog::ProgressTrainingDialog()
{
    setWindowTitle(tr("Training progress"));
    resize(QSize(600, 350));

    layout = new QVBoxLayout();

    initTimer();

    QProgressBar *progressBar = new QProgressBar();
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);

    layout->addWidget(progressBar);

    setLayout(layout);
}

void ProgressTrainingDialog::initTimer() {
    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &ProgressTrainingDialog::timer);
    timer->start(1000);
    seconds = 0;

    QHBoxLayout *timerLayout = new QHBoxLayout;
    QLabel *timerLabel = new QLabel(tr("Time: "));
    time = new QLabel("00:00:00");

    timerLayout->addWidget(timerLabel);
    timerLayout->addWidget(time);


    layout->addLayout(timerLayout);
}

void ProgressTrainingDialog::timer() {
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

    time->setText(hours + ":" + minuts + ":" + second);
}
