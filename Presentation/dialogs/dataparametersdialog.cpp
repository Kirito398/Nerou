#include "dataparametersdialog.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

#include "dialogs/dataaddtableitemdialog.h"

DataParametersDialog::DataParametersDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Data block parameters"));
    resize(QSize(600, 350));

    layout = new QVBoxLayout();
    dialog = nullptr;

    initControllButtons();
    initTable();
    initButtons();

    setLayout(layout);
}

void DataParametersDialog::add() {
    if (dialog == nullptr) {
        dialog = new DataAddTableItemDialog(this);
        connect(dialog, SIGNAL(onApplied()), this, SLOT(addNewSet()));
    }

    dialog->show();
}

void DataParametersDialog::addNewSet() {
    int i = table->rowCount();
    table->insertRow(i);
    table->setItem(i, 0, new QTableWidgetItem(dialog->getTrainingSetPath()));
    table->setItem(i, 1, new QTableWidgetItem(dialog->getTestingSetPath()));
    table->setItem(i, 2, new QTableWidgetItem());

    table->item(i, 0)->setToolTip(dialog->getTrainingSetPath());
    table->item(i, 1)->setToolTip(dialog->getTestingSetPath());

    table->resizeColumnToContents(i);
}

void DataParametersDialog::remove() {

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
    list << tr("TrainingSet") << tr("TestingSet") << tr("Neuron");
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
    connect(pbOk, &QPushButton::clicked, this, &DataParametersDialog::onApplied);
    connect(pbOk, &QPushButton::clicked, this, &QDialog::accept);
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Apply"));
    connect(pbApply, &QPushButton::clicked, this, &DataParametersDialog::onApplied);
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
}
