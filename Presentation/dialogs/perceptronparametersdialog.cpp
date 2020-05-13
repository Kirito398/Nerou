#include "perceptronparametersdialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>

#include "listeners/perceptronviewlistener.h"

PerceptronParametersDialog::PerceptronParametersDialog(PerceptronViewListener *view)
{
    this->view = view;

    layout = nullptr;
    initLayer();
}

QBoxLayout *PerceptronParametersDialog::getMainLayout() {
    initLayer();
    return layout;
}

void PerceptronParametersDialog::initLayer() {
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    initActivateFunctionTypeLayer();
    updateParameters();
}

void PerceptronParametersDialog::initActivateFunctionTypeLayer() {
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

void PerceptronParametersDialog::updateParameters() {
    cbActivateFunctionType->setCurrentIndex(view->getActivateFunctionType());
}

void PerceptronParametersDialog::onActivateFunctionTypeChanged() {
    view->onActivateFunctionTypeChanged(cbActivateFunctionType->currentIndex());
}
