#include "tabledatasetsdialog.h"

#include <QBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QGroupBox>
#include <QCheckBox>
#include <QListWidget>

#include "presenters/tabledatapresentor.h"

TableDataSetsDialog::TableDataSetsDialog(TableDataViewListener *view, TableDataPresentor *presentor, QWidget *parent)
{
    setWindowTitle(tr("Data block parameters"));
    resize(QSize(1024, 720));

    this->view = view;
    this->presentor = presentor;

    mainLayout = new QVBoxLayout();
    leftLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();

    QBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addLayout(leftLayout, 2);
    centerLayout->addLayout(rightLayout, 1);

    initBrowseLayout();
    initTable();
    initInputAndTargetLayout();

    mainLayout->addLayout(centerLayout);

    initControllButtons();

    setLayout(mainLayout);
}

void TableDataSetsDialog::initBrowseLayout() {
    QLabel *title = new QLabel(tr("Data set:"));
    dataPath = new QLineEdit("");
    QPushButton *pbBrowse = new QPushButton(tr("Browse"));
    connect(pbBrowse, &QPushButton::clicked, this, &TableDataSetsDialog::onDataSetBrowseClicked);

    QBoxLayout *browseLayout = new QVBoxLayout();
    browseLayout->addWidget(title);

    QHBoxLayout *browsePathLayout = new QHBoxLayout();
    browsePathLayout->addWidget(dataPath);
    browsePathLayout->addWidget(pbBrowse);
    browseLayout->addLayout(browsePathLayout);

    mainLayout->addLayout(browseLayout);
}

void TableDataSetsDialog::onDataSetBrowseClicked() {
    QString file = QFileDialog::getOpenFileName(nullptr, "", "/home", "*.csv");
    dataPath->setText(file);

    if (file == "")
        return;


    QVector<QStringList> dataList = presentor->loadTableValue(file);

    QStringList tableHeaders;
    for (int i = 0; i < dataList[0].size(); i++)
        tableHeaders << dataList[0][i];

    updateInputsAndTargetsCheckBoxes(tableHeaders);

    csvModel->clear();
    csvModel->setColumnCount(dataList[0].size());
    csvModel->setHorizontalHeaderLabels(tableHeaders);


    for (int i = 1; i < dataList.size(); i++) {
        QList<QStandardItem *> list;

        for (int j = 0; j < dataList[i].size(); j++)
            list.append(new QStandardItem(dataList[i][j]));

        csvModel->insertRow(csvModel->rowCount(), list);
    }
}

void TableDataSetsDialog::updateInputsAndTargetsCheckBoxes(QStringList titles) {
    targetsList->clear();
    inputsList->clear();

    for (auto box : targetsCheckBoxes)
        delete box;
    targetsCheckBoxes.clear();

    for (auto box : inputsCheckBoxes)
        delete box;
    inputsCheckBoxes.clear();

    for (auto title : titles) {
        QCheckBox *newTarget = new QCheckBox(title);
        QCheckBox *newInput = new QCheckBox(title);
        targetsCheckBoxes.append(newTarget);
        inputsCheckBoxes.append(newInput);
        addWidget(inputsList, newInput);
        addWidget(targetsList, newTarget);
    }
}

void TableDataSetsDialog::addWidget(QListWidget *list, QWidget *widget) {
    QListWidgetItem* item = new QListWidgetItem(list);
    item->setSizeHint(widget->sizeHint());
    list->setItemWidget(item, widget);
}

void TableDataSetsDialog::initControllButtons() {
    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("OK"));
    //connect(pbOk, &QPushButton::clicked, this, &DataSetsDialog::accept);
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Apply"));
    //connect(pbApply, &QPushButton::clicked, this, &DataSetsDialog::applied);
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    mainLayout->addLayout(buttonsLayout);
}

void TableDataSetsDialog::initInputAndTargetLayout() {
    QGroupBox *inputsBox = new QGroupBox(tr("Inputs"));
    QGroupBox *targetsBox = new QGroupBox(tr("Targets"));

    targetsList = new QListWidget();
    inputsList = new QListWidget();

    QBoxLayout *targetsBoxLayout = new QVBoxLayout();
    QBoxLayout *inputsBoxLayout = new QVBoxLayout();

    inputsBoxLayout->addWidget(inputsList);
    targetsBoxLayout->addWidget(targetsList);

    inputsBox->setLayout(inputsBoxLayout);
    targetsBox->setLayout(targetsBoxLayout);

    rightLayout->addWidget(inputsBox);
    rightLayout->addWidget(targetsBox);
}


void TableDataSetsDialog::initTable() {
    QTableView *table = new QTableView();

    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(true);
    table->setEditTriggers(QTableWidget::NoEditTriggers);

    csvModel = new QStandardItemModel();
    table->setModel(csvModel);

    leftLayout->addWidget(table);
}
