#ifndef DATAPARAMETERSDIALOG_H
#define DATAPARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;
class QCheckBox;
class QComboBox;
class DataViewListener;

class DataParametersDialog : public QDialog
{
    Q_OBJECT
public:
    DataParametersDialog(DataViewListener *view);
    QBoxLayout *getMainLayout();

private:
    void initLayer();
    void updateParameters();
    void initUseColorLayer();
    void initActivateFunctionTypeLayer();
    void initLossFunctionTypeLayer();

private:
    DataViewListener *view;
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
