#ifndef TABLEDATASETSDIALOG_H
#define TABLEDATASETSDIALOG_H

#include <QDialog>
#include <QList>

class TableDataViewListener;
class TableDataPresentor;
class QBoxLayout;
class QStandardItemModel;
class QLineEdit;
class QCheckBox;
class QListWidget;
class QLabel;

class TableDataSetsDialog : public QDialog
{
    Q_OBJECT
public:
    TableDataSetsDialog(TableDataViewListener *view, TableDataPresentor *presentor, QWidget *parent = nullptr);
    void loadDataSet(QString file);
    ~TableDataSetsDialog();

private:
    void initTable();
    void initBrowseLayout();
    void initInputAndTargetLayout();
    void initControllButtons();
    void updateInputsAndTargetsCheckBoxes(QStringList titles);
    void addWidget(QListWidget *list, QWidget *widget);
    void updateTargetCheckBoxesEnabled();
    void updateInputCheckBoxesEnabled();

private:
    QBoxLayout *mainLayout, *rightLayout, *leftLayout;
    QList<QCheckBox *> targetsCheckBoxes, inputsCheckBoxes;
    TableDataViewListener *view;
    TableDataPresentor *presentor;
    QStandardItemModel *csvModel;
    QLineEdit *dataPath;
    QListWidget *targetsList, *inputsList;
    QVector<QStringList> dataList;
    QLabel *targetNeuronNumberLabel, *inputNeuronNumberLabel;
    size_t targetNeuronNumber, inputNeuronNumber;

private slots:
    void onDataSetBrowseClicked();
    void accept();
    void applied();
    void onTargetCheckBoxStateChanged(int state);
    void onInputCheckBoxStateChanged(int state);
};

#endif // TABLEDATASETSDIALOG_H
