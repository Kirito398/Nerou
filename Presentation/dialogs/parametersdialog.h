#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;

class ParametersDialog : public QDialog
{
    Q_OBJECT
public:
    ParametersDialog();
    QBoxLayout *getMainLayout();
    void updateParameters();

private:
    QBoxLayout *layout;
};

#endif // PARAMETERSDIALOG_H
