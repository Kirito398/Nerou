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

class TableDataSetsDialog : public QDialog
{
    Q_OBJECT
public:
    TableDataSetsDialog(TableDataViewListener *view, TableDataPresentor *presentor, QWidget *parent = nullptr);
    void initTable();
    void initBrowseLayout();
    void initInputAndTargetLayout();
    void initControllButtons();
    void updateInputsAndTargetsCheckBoxes(QStringList titles);
    void addWidget(QListWidget *list, QWidget *widget);

private:
    QBoxLayout *mainLayout, *rightLayout, *leftLayout;
    QList<QCheckBox *> targetsCheckBoxes, inputsCheckBoxes;
    TableDataViewListener *view;
    TableDataPresentor *presentor;
    QStandardItemModel *csvModel;
    QLineEdit *dataPath;
    QListWidget *targetsList, *inputsList;

private slots:
    void onDataSetBrowseClicked();
};

#endif // TABLEDATASETSDIALOG_H
