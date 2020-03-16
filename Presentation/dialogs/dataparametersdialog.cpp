#include "dataparametersdialog.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

DataParametersDialog::DataParametersDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Data block parameters"));
    setFixedSize(QSize(350, 500));

    layout = new QVBoxLayout();

    initControllButtons();
    initTable();
    initButtons();

    setLayout(layout);
}

void DataParametersDialog::onApplied() {

}

void DataParametersDialog::onAccept() {
    onApplied();
    emit QDialog::accept();
}

void DataParametersDialog::add() {

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
    QTableWidget *table = new QTableWidget();
    table->setColumnCount(3);

    QStringList list;
    list << tr("TrainingSet") << tr("TestingSet") << tr("Neuron");
    table->setHorizontalHeaderLabels(list);
    table->horizontalHeader()->setStretchLastSection(true);

    layout->addWidget(table);
}

void DataParametersDialog::initButtons() {
    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("OK"));
    connect(pbOk, &QPushButton::clicked, this, &DataParametersDialog::onAccept);
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Apply"));
    connect(pbApply, &QPushButton::clicked, this, &DataParametersDialog::onApplied);
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
}
