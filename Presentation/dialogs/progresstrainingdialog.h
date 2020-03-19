#ifndef PROGRESSTRAININGDIALOG_H
#define PROGRESSTRAININGDIALOG_H

#include <QDialog>

class QBoxLayout;
class QLabel;

class ProgressTrainingDialog : public QDialog
{
    Q_OBJECT
public:
    ProgressTrainingDialog();

private:
    void initTimer();

private:
    QBoxLayout *layout;
    QLabel *time;
    unsigned long seconds;

private slots:
    void timer();
};

#endif // PROGRESSTRAININGDIALOG_H
