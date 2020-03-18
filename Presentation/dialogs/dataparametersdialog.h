#ifndef DATAPARAMETERSDIALOG_H
#define DATAPARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;
class QTableWidget;
class DataAddTableItemDialog;
class DataViewListener;
class QSize;
class DataPresentor;

class DataParametersDialog : public QDialog
{
    Q_OBJECT
public:
    DataParametersDialog(DataViewListener *view, DataPresentor *presentor, QWidget *parent = nullptr);
    void initControllButtons();
    void initTable();
    void initButtons();
    void getParameters(QStringList *trainingList, QStringList *testingList, QStringList *neuronIDs);
    QSize getImageSize();
    void updateParameters(QStringList trainingList, QStringList testingList, QStringList neuronIDs);

private:
    void updateOutputsNeuronsList();
    bool checkImageSize();
    void addNewSet(QString trainingSetPath, QString testingSetPath, QString neuronID);
    void enterEvent(QEvent *event) override;
    QStringList getPaths(QString mainPath);

private:
    QSize *defaultSize;
    DataViewListener *view;
    DataPresentor *presentor;
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
