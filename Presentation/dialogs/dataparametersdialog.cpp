#include "dataparametersdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>

#include "presenters/datapresentor.h"

DataParametersDialog::DataParametersDialog(DataPresentor *presenter)
{
    this->presenter = presenter;

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
}

QBoxLayout *DataParametersDialog::getMainLayout() {
    initLayer();
    return layout;
}

void DataParametersDialog::updateParameters() {
    cbUseColor->setChecked(presenter->getUseColorModeEnable());
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
    connect(cbActivateFunctionType, SIGNAL(currentIndexChanged(int)), this, SLOT(onActivateFunctionTypeChanged()));

    layout->addWidget(lTitle);
    layout->addWidget(cbActivateFunctionType);

    layout->setStretch(0, 2);
    layout->setStretch(1, 1);

    layout->addLayout(layout);
}

void DataParametersDialog::initLossFunctionTypeLayer() {
    QBoxLayout *layout = new QHBoxLayout();
    QLabel *lTitle = new QLabel(tr("Loss Function: "));

    cbLossFunctionType = new QComboBox();
    connect(cbLossFunctionType, SIGNAL(currentIndexChanged(int)), this, SLOT(onLossFunctionTypeChanged()));

    layout->addWidget(lTitle);
    layout->addWidget(cbLossFunctionType);

    layout->setStretch(0, 2);
    layout->setStretch(1, 1);

    layout->addLayout(layout);
}

void DataParametersDialog::onUseColorEnableChanged() {
    presenter->setUseColorModeEnable(cbUseColor->isChecked());
}

void DataParametersDialog::onActivateFunctionTypeChanged() {
    presenter->setActivateFunctionType(cbActivateFunctionType->currentIndex());
}

void DataParametersDialog::onLossFunctionTypeChanged() {
    presenter->setLossFunctionType(LossFunctionType (cbLossFunctionType->currentIndex()));
}
