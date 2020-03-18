#ifndef DATAPARAMETERSDIALOG_H
#define DATAPARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;
class QTableWidget;
class DataAddTableItemDialog;
class DataViewListener;
class QSize;

class DataParametersDialog : public QDialog
{
    Q_OBJECT
public:
    DataParametersDialog(DataViewListener *view, QWidget *parent = nullptr);
    void initControllButtons();
    void initTable();
    void initButtons();
    void getParameters(QStringList *trainingList, QStringList *testingList, QStringList *neuronIDs);
    QSize getImageSize();

private:
    void updateOutputsNeuronsList();
    bool checkImageSize();
    void enterEvent(QEvent *event) override;

private:
    QSize *defaultSize;
    DataViewListener *view;
    DataAddTableItemDialog *dialog;
    QBoxLayout *layout;
    QTableWidget *table;

private slots:
    void add();
    void remove();
    void addNewSet();
    void accept() override;
    void applied();

signals:
    void onApplied();
};

#endif // DATAPARAMETERSDIALOG_H
