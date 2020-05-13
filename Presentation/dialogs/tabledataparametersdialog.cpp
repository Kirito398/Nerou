#include "tabledataparametersdialog.h"

#include <QVBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QComboBox>

#include "listeners/tabledataviewlistener.h"

TableDataParametersDialog::TableDataParametersDialog(TableDataViewListener *view)
{
    this->view = view;

    layout = nullptr;
    initLayer();
}

QBoxLayout *TableDataParametersDialog::getMainLayout() {
    initLayer();
    return layout;
}

void TableDataParametersDialog::initLayer() {
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    initActivateFunctionTypeLayer();
    initLossFunctionTypeLayer();
    updateParameters();

    QToolButton *tbOpenSets = new QToolButton();
    tbOpenSets->setText(tr("Training sets"));
    connect(tbOpenSets, SIGNAL(clicked()), this, SLOT(onOpenSetsButtonClicked()));

    layout->addWidget(tbOpenSets);
}

void TableDataParametersDialog::updateParameters() {
    cbLossFunctionType->setCurrentIndex(view->getLossFunctionType());
    cbActivateFunctionType->setCurrentIndex(view->getActivateFunctionType());
}

void TableDataParametersDialog::initActivateFunctionTypeLayer() {
    QBoxLayout *layout = new QHBoxLayout();
    QLabel *lTitle = new QLabel(tr("Activate Function: "));

    cbActivateFunctionType = new QComboBox();
    cbActivateFunctionType->addItem(tr("Sigmoid"));
    cbActivateFunctionType->addItem(tr("Tanh"));
    cbActivateFunctionType->addItem(tr("ReLU"));
    cbActivateFunctionType->addItem(tr("SoftMax"));
    connect(cbActivateFunctionType, SIGNAL(currentIndexChanged(int)), this, SLOT(onActivateFunctionTypeChanged()));

    layout->addWidget(lTitle);
    layout->addWidget(cbActivateFunctionType);

    layout->setStretch(0, 1);
    layout->setStretch(1, 1);

    this->layout->addLayout(layout);
}

void TableDataParametersDialog::initLossFunctionTypeLayer() {
    QBoxLayout *layout = new QHBoxLayout();
    QLabel *lTitle = new QLabel(tr("Loss Function: "));

    cbLossFunctionType = new QComboBox();
    cbLossFunctionType->addItem(tr("MSE"));
    cbLossFunctionType->addItem(tr("Cross Entropy"));
    connect(cbLossFunctionType, SIGNAL(currentIndexChanged(int)), this, SLOT(onLossFunctionTypeChanged()));

    layout->addWidget(lTitle);
    layout->addWidget(cbLossFunctionType);

    layout->setStretch(0, 1);
    layout->setStretch(1, 1);

    this->layout->addLayout(layout);
}

void TableDataParametersDialog::onActivateFunctionTypeChanged() {
    view->onActivateFunctionTypeChanged(cbActivateFunctionType->currentIndex());
}

void TableDataParametersDialog::onLossFunctionTypeChanged() {
    view->onLossFunctionTypeChanged(cbLossFunctionType->currentIndex());
}

void TableDataParametersDialog::onOpenSetsButtonClicked() {
    view->openSetsDialog();
}
