#ifndef DATAPARAMETERSDIALOG_H
#define DATAPARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;
class QCheckBox;
class QComboBox;
class DataPresentor;

class DataParametersDialog : public QDialog
{
    Q_OBJECT
public:
    DataParametersDialog(DataPresentor *presenter);

private:
    void updateParameters();
    void initUseColorLayer();
    void initActivateFunctionTypeLayer();
    void initLossFunctionTypeLayer();

private:
    DataPresentor *presenter;
    QBoxLayout *layout;
    QCheckBox *cbUseColor;
    QComboBox *cbActivateFunctionType;
    QComboBox *cbLossFunctionType;

private slots:
    void onUseColorEnableChanged();
    void onActivateFunctionTypeChanged();
    void onLossFunctionTypeChanged();
};

#endif // DATAPARAMETERSDIALOG_H
