#include "dataparametersdialog.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QApplication>
#include <QDir>

#include "dialogs/dataaddtableitemdialog.h"
#include "listeners/dataviewlistener.h"

DataParametersDialog::DataParametersDialog(DataViewListener *view, QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Data block parameters"));
    resize(QSize(600, 350));

    this->view = view;
    layout = new QVBoxLayout();
    dialog = nullptr;

    initControllButtons();
    initTable();
    initButtons();

    setLayout(layout);
}

void DataParametersDialog::enterEvent(QEvent *event) {
    QDialog::enterEvent(event);
    updateOutputsNeuronsList();
}

void DataParametersDialog::add() {
    if (dialog == nullptr) {
        dialog = new DataAddTableItemDialog(this);
        connect(dialog, SIGNAL(onApplied()), this, SLOT(addNewSet()));
    }

    updateOutputsNeuronsList();
    dialog->show();
}

void DataParametersDialog::updateOutputsNeuronsList() {
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

void DataParametersDialog::addNewSet() {
    int i = table->rowCount();
    table->insertRow(i);

    QString trainingSetPath = dialog->getTrainingSetPath();
    QString testingSetPath = dialog->getTestingSetPath();
    QString neuronID = dialog->getNeuronID();

    if (!testingSetPath.isEmpty())
        testingSetPath += "/";

    if (!trainingSetPath.isEmpty())
        trainingSetPath += "/";

    table->setItem(i, 0, new QTableWidgetItem(neuronID));
    table->setItem(i, 1, new QTableWidgetItem(trainingSetPath));
    table->setItem(i, 2, new QTableWidgetItem(testingSetPath));

    table->item(i, 0)->setToolTip(neuronID);
    table->item(i, 1)->setToolTip(trainingSetPath);
    table->item(i, 2)->setToolTip(testingSetPath);

    table->resizeColumnToContents(i);
    updateOutputsNeuronsList();
}

void DataParametersDialog::accept() {
    if (checkImageSize()) {
        emit onApplied();
        QDialog::accept();
    }
}

void DataParametersDialog::applied() {
    if (checkImageSize())
        emit onApplied();
}

bool DataParametersDialog::checkImageSize() {
    int n = table->rowCount();
    QStringList entryList;
    entryList << "*.jpg" << "*.png";
    defaultSize = nullptr;

    for (int i = 0; i < n; i++) {
        QString mainPath = table->item(i, 1)->text().isEmpty() ? table->item(i, 2)->text() : table->item(i, 1)->text();
        QDir dir(mainPath);
        QStringList pathsList = dir.entryList(entryList);
        QImage image(mainPath + pathsList[0]);

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

void DataParametersDialog::remove() {
    table->model()->removeRow(table->selectionModel()->currentIndex().row());
    updateOutputsNeuronsList();
}

QSize DataParametersDialog::getImageSize() {
    return QSize(*defaultSize);
}

void DataParametersDialog::getParameters(QStringList *trainingList, QStringList *testingList, QStringList *neuronIDs) {
    int n = table->rowCount();

    for (int i = 0; i < n; i++) {
        neuronIDs->append(table->item(i, 0)->text());
        trainingList->append(table->item(i, 1)->text());
        testingList->append(table->item(i, 2)->text());
    }
}

void DataParametersDialog::initControllButtons() {
    QBoxLayout *tableControllButtonsLayout = new QHBoxLayout();

    QPushButton *pbAdd = new QPushButton(tr("Add"));
    connect(pbAdd, &QPushButton::clicked, this, &DataParametersDialog::add);
    tableControllButtonsLayout->addWidget(pbAdd);

    QPushButton *pbRemove = new QPushButton(tr("Remove"));
    connect(pbRemove, &QPushButton::clicked, this, &DataParametersDialog::remove);
    tableControllButtonsLayout->addWidget(pbRemove);

    layout->addLayout(tableControllButtonsLayout);
}

void DataParametersDialog::initTable() {
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

void DataParametersDialog::initButtons() {
    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("OK"));
    connect(pbOk, &QPushButton::clicked, this, &DataParametersDialog::accept);
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Apply"));
    connect(pbApply, &QPushButton::clicked, this, &DataParametersDialog::applied);
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
}
