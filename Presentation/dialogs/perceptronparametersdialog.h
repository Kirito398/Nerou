#ifndef PERCEPTRONPARAMETERSDIALOG_H
#define PERCEPTRONPARAMETERSDIALOG_H

#include <QDialog>

class PerceptronViewListener;
class QBoxLayout;
class QComboBox;

class PerceptronParametersDialog : public QDialog
{
    Q_OBJECT
public:
    PerceptronParametersDialog(PerceptronViewListener *view);
    QBoxLayout *getMainLayout();

private:
    void initLayer();
    void updateParameters();
    void initActivateFunctionTypeLayer();

private:
    PerceptronViewListener *view;
    QBoxLayout *layout;
    QComboBox *cbActivateFunctionType;

private slots:
    void onActivateFunctionTypeChanged();
};

#endif // PERCEPTRONPARAMETERSDIALOG_H

