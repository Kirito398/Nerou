#include "datasetsdialog.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QApplication>
#include <QDir>

#include "dialogs/dataaddsetdialog.h"
#include "listeners/dataviewlistener.h"
#include "presenters/datapresentor.h"
#include "interfaces/repositoryinterface.h"

DataSetsDialog::DataSetsDialog(DataViewListener *view, DataPresentor *presentor, QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Data block parameters"));
    resize(QSize(600, 350));

    this->view = view;
    this->presentor = presentor;

    layout = new QVBoxLayout();
    dialog = nullptr;

    initControllButtons();
    initTable();
    initButtons();

    setLayout(layout);
}

void DataSetsDialog::enterEvent(QEvent *event) {
    QDialog::enterEvent(event);
    updateOutputsNeuronsList();
}

void DataSetsDialog::add() {
    if (dialog == nullptr) {
        dialog = new DataAddSetDialog(presentor->getRepository(), this);
        connect(dialog, SIGNAL(onApplied()), this, SLOT(addNewSet()));
    }

    updateOutputsNeuronsList();
    dialog->show();
}

void DataSetsDialog::updateOutputsNeuronsList() {
    if (dialog == nullptr)
        return;

    QStringList list = view->getOutputsNeuronsList();

    for (int i = 0; i < table->rowCount(); i++) {
        QString neuronID = table->item(i, 0)->text();
        if (list.contains(neuronID))
            list.removeAll(neuronID);
    }

    dialog->setOutputsNeuronsList(list);
}

void DataSetsDialog::addNewSet() {
    QString trainingSetPath = dialog->getTrainingSetPath();
    QString testingSetPath = dialog->getTestingSetPath();
    QString neuronID = dialog->getNeuronID();

    if (!testingSetPath.isEmpty())
        testingSetPath += "/";

    if (!trainingSetPath.isEmpty())
        trainingSetPath += "/";

    addNewSet(trainingSetPath, testingSetPath, neuronID);
}

void DataSetsDialog::addNewSet(QString trainingSetPath, QString testingSetPath, QString neuronID) {
    int i = table->rowCount();
    table->insertRow(i);

    table->setItem(i, 0, new QTableWidgetItem(neuronID));
    table->setItem(i, 1, new QTableWidgetItem(trainingSetPath));
    table->setItem(i, 2, new QTableWidgetItem(testingSetPath));

    table->item(i, 0)->setToolTip(neuronID);
    table->item(i, 1)->setToolTip(trainingSetPath);
    table->item(i, 2)->setToolTip(testingSetPath);

    table->resizeColumnToContents(i);
    updateOutputsNeuronsList();
}

void DataSetsDialog::accept() {
    if (checkImageSize()) {
        emit onApplied();
        QDialog::accept();
    }
}

void DataSetsDialog::applied() {
    if (checkImageSize())
        emit onApplied();
}

bool DataSetsDialog::checkImageSize() {
    int n = table->rowCount();
    defaultSize = nullptr;

    for (int i = 0; i < n; i++) {
        QString mainPath = table->item(i, 1)->text().isEmpty() ? table->item(i, 2)->text() : table->item(i, 1)->text();
        QImage image(getPaths(mainPath)[0]);

        if (defaultSize == nullptr)
            defaultSize = new QSize(image.size());

        if (image.size() != *defaultSize) {
            for (int j = 0; j < table->columnCount(); j++)
                table->item(i, j)->setBackground(Qt::red);
            return false;
        }
    }

    return true;
}

QStringList DataSetsDialog::getPaths(QString mainPath) {
    QStringList list;

    if (mainPath.isEmpty())
        return list;

    std::vector<std::string> paths = presentor->getRepository()->getPaths(mainPath.toStdString());

    for (auto path : paths)
        list.append(QString::fromStdString(path));

    return list;
}

void DataSetsDialog::remove() {
    table->model()->removeRow(table->selectionModel()->currentIndex().row());
    updateOutputsNeuronsList();
}

QSize DataSetsDialog::getImageSize() {
    if (defaultSize != nullptr)
        return QSize(*defaultSize);
    else return QSize(0, 0);
}

void DataSetsDialog::getParameters(QStringList *trainingList, QStringList *testingList, QStringList *neuronIDs) {
    int n = table->rowCount();

    for (int i = 0; i < n; i++) {
        neuronIDs->append(table->item(i, 0)->text());
        trainingList->append(table->item(i, 1)->text());
        testingList->append(table->item(i, 2)->text());
    }
}

void DataSetsDialog::updateParameters(QStringList trainingList, QStringList testingList, QStringList neuronIDs) {
    if (table == nullptr)
        return;

    table->clearContents();
    table->setRowCount(0);

    for (int i = 0; i < trainingList.size(); i++)
        addNewSet(trainingList[i], testingList[i], neuronIDs[i]);
}

void DataSetsDialog::initControllButtons() {
    QBoxLayout *tableControllButtonsLayout = new QHBoxLayout();

    QPushButton *pbAdd = new QPushButton(tr("Add"));
    connect(pbAdd, &QPushButton::clicked, this, &DataSetsDialog::add);
    tableControllButtonsLayout->addWidget(pbAdd);

    QPushButton *pbRemove = new QPushButton(tr("Remove"));
    connect(pbRemove, &QPushButton::clicked, this, &DataSetsDialog::remove);
    tableControllButtonsLayout->addWidget(pbRemove);

    layout->addLayout(tableControllButtonsLayout);
}

void DataSetsDialog::initTable() {
    table = new QTableWidget();
    table->setColumnCount(3);

    QStringList list;
    list << tr("Neuron") << tr("TrainingSet") << tr("TestingSet");
    table->setHorizontalHeaderLabels(list);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setShowGrid(true);
    table->setEditTriggers(QTableWidget::NoEditTriggers);
    table->horizontalHeader()->setDefaultSectionSize(table->size().width() / 3);

    layout->addWidget(table);
}

void DataSetsDialog::initButtons() {
    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("OK"));
    connect(pbOk, &QPushButton::clicked, this, &DataSetsDialog::accept);
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Apply"));
    connect(pbApply, &QPushButton::clicked, this, &DataSetsDialog::applied);
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
}
