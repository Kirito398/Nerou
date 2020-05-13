#ifndef DATASETSDIALOG_H
#define DATASETSDIALOG_H

#include <QDialog>

class QBoxLayout;
class QTableWidget;
class DataAddSetDialog;
class DataViewListener;
class QSize;
class DataPresentor;

class DataSetsDialog : public QDialog
{
    Q_OBJECT
public:
    DataSetsDialog(DataViewListener *view, DataPresentor *presentor, QWidget *parent = nullptr);
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
    DataAddSetDialog *dialog;
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

#endif // DATASETSDIALOG_H
