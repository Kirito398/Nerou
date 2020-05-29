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
#include "listeners/tabledataviewlistener.h"

TableDataSetsDialog::TableDataSetsDialog(TableDataViewListener *view, TableDataPresentor *presentor, QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Data block parameters"));
    resize(QSize(1024, 720));

    this->view = view;
    this->presentor = presentor;

    mainLayout = new QVBoxLayout();
    leftLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();

    targetNeuronNumber = view->getOutputsNeuronsList().size();
    inputNeuronNumber = presentor->getOutputsNeuronNumber();

    QBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addLayout(leftLayout, 2);
    centerLayout->addLayout(rightLayout, 1);

    initBrowseLayout();
    initTable();
    initInputAndTargetLayout();

    mainLayout->addLayout(centerLayout);

    initControllButtons();

    setLayout(mainLayout);

    loadDataSet(presentor->getDataSetMainPath());
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
    loadDataSet(file);
}

void TableDataSetsDialog::loadDataSet(QString file) {
    if (file == "")
        return;

    dataPath->setText(file);

    dataList.clear();
    dataList = presentor->loadTableValue(file);

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

        connect(newTarget, &QCheckBox::stateChanged, this, &TableDataSetsDialog::onTargetCheckBoxStateChanged);
        connect(newInput, &QCheckBox::stateChanged, this, &TableDataSetsDialog::onInputCheckBoxStateChanged);

        targetsCheckBoxes.append(newTarget);
        inputsCheckBoxes.append(newInput);
        addWidget(inputsList, newInput);
        addWidget(targetsList, newTarget);
    }

    updateTargetCheckBoxesEnabled();
    updateInputCheckBoxesEnabled();

    QStringList headers = presentor->getInputsTitles();

    for (auto header : headers)
        for (auto item : inputsCheckBoxes)
            if (header.contains(item->text())) {
                item->setChecked(true);
                break;
            }

    headers.clear();
    headers = presentor->getTargetTitles();

    for (auto header : headers)
        for (auto item : targetsCheckBoxes)
            if (header.contains(item->text())) {
                item->setChecked(true);
                break;
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
    connect(pbOk, &QPushButton::clicked, this, &TableDataSetsDialog::accept);
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Apply"));
    connect(pbApply, &QPushButton::clicked, this, &TableDataSetsDialog::applied);
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    mainLayout->addLayout(buttonsLayout);
}

void TableDataSetsDialog::accept() {
    applied();

    emit QDialog::accept();
}

void TableDataSetsDialog::applied() {
    double delimiter = 0.7;
    int trainingSetSize = (dataList.size() - 1) * delimiter;

    presentor->clearDataSet();
    presentor->setDataSetMainPath(dataPath->text());

    //Training input sets
    QStringList tableHeaders;
    for (auto item : inputsCheckBoxes)
        if (item->isChecked())
            tableHeaders.append(item->text());

    presentor->setInputsTitles(tableHeaders);

    for (int i = 1; i <= trainingSetSize; i++) {
        QStringList list;

        for (int j = 0; j < dataList[i].size(); j++)
            if (tableHeaders.contains(dataList[0][j]))
                list.append(dataList[i][j]);

        presentor->addTrainingInputSet(list);
    }

    //Testing input sets
    for (int i = trainingSetSize + 1; i < dataList.size(); i++) {
        QStringList list;

        for (int j = 0; j < dataList[i].size(); j++)
            if (tableHeaders.contains(dataList[0][j]))
                list.append(dataList[i][j]);

        presentor->addTestingInputSet(list);
    }

    //Training target sets
    tableHeaders.clear();
    for (auto item : targetsCheckBoxes)
        if (item->isChecked())
            tableHeaders.append(item->text());

    presentor->setTargetTitles(tableHeaders, view->getOutputsNeuronsList());

    for (int i = 1; i <= trainingSetSize; i++) {
        QStringList list;

        for (int j = 0; j < dataList[i].size(); j++)
            if (tableHeaders.contains(dataList[0][j]))
                list.append(dataList[i][j]);

        presentor->addTrainingTargetSet(list);
    }

    //Testing target sets
    for (int i = trainingSetSize + 1; i < dataList.size(); i++) {
        QStringList list;

        for (int j = 0; j < dataList[i].size(); j++)
            if (tableHeaders.contains(dataList[0][j]))
                list.append(dataList[i][j]);

        presentor->addTestingTargetSet(list);
    }
}

void TableDataSetsDialog::onTargetCheckBoxStateChanged(int state) {
    if (state)
        targetNeuronNumber--;
    else
        targetNeuronNumber++;

    updateTargetCheckBoxesEnabled();
}

void TableDataSetsDialog::onInputCheckBoxStateChanged(int state) {
    if (state)
        inputNeuronNumber--;
    else
        inputNeuronNumber++;

    updateInputCheckBoxesEnabled();
}

void TableDataSetsDialog::updateTargetCheckBoxesEnabled() {
    bool enable = true;

    if (targetNeuronNumber <= 0)
        enable = false;

    for (auto box : targetsCheckBoxes)
        if (!box->isChecked())
            box->setEnabled(enable);

    targetNeuronNumberLabel->setText(tr("You have output neurons: ") + QString::number(targetNeuronNumber));
}

void TableDataSetsDialog::updateInputCheckBoxesEnabled() {
    bool enable = true;

    if (inputNeuronNumber <= 0)
        enable = false;

    for (auto box : inputsCheckBoxes)
        if (!box->isChecked())
            box->setEnabled(enable);

    inputNeuronNumberLabel->setText(tr("You have input neurons: ") + QString::number(inputNeuronNumber));
}

void TableDataSetsDialog::initInputAndTargetLayout() {
    QGroupBox *inputsBox = new QGroupBox(tr("Inputs"));
    QGroupBox *targetsBox = new QGroupBox(tr("Targets"));

    targetsList = new QListWidget();
    inputsList = new QListWidget();

    targetNeuronNumberLabel = new QLabel(tr("You have output neurons: ") + QString::number(targetNeuronNumber));
    inputNeuronNumberLabel = new QLabel(tr("You have input neurons: ") + QString::number(inputNeuronNumber));

    QBoxLayout *targetsBoxLayout = new QVBoxLayout();
    QBoxLayout *inputsBoxLayout = new QVBoxLayout();

    inputsBoxLayout->addWidget(inputNeuronNumberLabel);
    targetsBoxLayout->addWidget(targetNeuronNumberLabel);

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

TableDataSetsDialog::~TableDataSetsDialog() {
    targetsCheckBoxes.clear();
    inputsCheckBoxes.clear();
    csvModel->clear();
    targetsList->clear();
    inputsList->clear();
    dataList.clear();

    delete dataPath;
    delete rightLayout;
    delete leftLayout;
    delete mainLayout;
}
