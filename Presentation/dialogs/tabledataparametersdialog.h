#ifndef TABLEDATAPARAMETERSDIALOG_H
#define TABLEDATAPARAMETERSDIALOG_H

#include <QDialog>

class TableDataViewListener;
class QBoxLayout;
class QComboBox;

class TableDataParametersDialog : public QDialog
{
    Q_OBJECT
public:
    TableDataParametersDialog(TableDataViewListener *view);
    QBoxLayout *getMainLayout();

private:
    void initLayer();
    void updateParameters();
    void initActivateFunctionTypeLayer();
    void initLossFunctionTypeLayer();

private:
    TableDataViewListener *view;
    QBoxLayout *layout;
    QComboBox *cbActivateFunctionType;
    QComboBox *cbLossFunctionType;

private slots:
    void onActivateFunctionTypeChanged();
    void onLossFunctionTypeChanged();
    void onOpenSetsButtonClicked();
};

#endif // TABLEDATAPARAMETERSDIALOG_H
