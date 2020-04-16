#include "dataparametersdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QToolButton>

#include "listeners/dataviewlistener.h"

DataParametersDialog::DataParametersDialog(DataViewListener *view)
{
    this->view = view;

    layout = nullptr;
    initLayer();
}

void DataParametersDialog::initLayer() {
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    initActivateFunctionTypeLayer();
    initLossFunctionTypeLayer();
    initUseColorLayer();
    updateParameters();

    QToolButton *tbOpenSets = new QToolButton();
    tbOpenSets->setText(tr("Training sets"));
    connect(tbOpenSets, SIGNAL(clicked()), this, SLOT(onOpenSetsButtonClicked()));

    layout->addWidget(tbOpenSets);
}

QBoxLayout *DataParametersDialog::getMainLayout() {
    initLayer();
    return layout;
}

void DataParametersDialog::updateParameters() {
    cbUseColor->setChecked(view->getUseColorModeEnable());
    cbLossFunctionType->setCurrentIndex(view->getLossFunctionType());
    cbActivateFunctionType->setCurrentIndex(view->getActivateFunctionType());
}

void DataParametersDialog::initUseColorLayer() {
    QBoxLayout *colorLayout = new QHBoxLayout();
    QLabel *lColorTitle = new QLabel(tr("Color: "));

    cbUseColor = new QCheckBox();
    connect(cbUseColor, &QCheckBox::stateChanged, this, &DataParametersDialog::onUseColorEnableChanged);

    colorLayout->addWidget(lColorTitle);
    colorLayout->addWidget(cbUseColor);

    colorLayout->setStretch(0, 2);
    colorLayout->setStretch(1, 1);

    layout->addLayout(colorLayout);
}

void DataParametersDialog::initActivateFunctionTypeLayer() {
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

void DataParametersDialog::initLossFunctionTypeLayer() {
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

void DataParametersDialog::onUseColorEnableChanged() {
    view->onUseColorModeEnableChanged(cbUseColor->isChecked());
}

void DataParametersDialog::onActivateFunctionTypeChanged() {
    view->onActivateFunctionTypeChanged(cbActivateFunctionType->currentIndex());
}

void DataParametersDialog::onLossFunctionTypeChanged() {
    view->onLossFunctionTypeChanged(cbLossFunctionType->currentIndex());
}

void DataParametersDialog::onOpenSetsButtonClicked() {
    view->openSetsDialog();
}
