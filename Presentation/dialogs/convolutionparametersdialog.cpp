#include "convolutionparametersdialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>

#include "listeners/convolutionviewlistener.h"

ConvolutionParametersDialog::ConvolutionParametersDialog(ConvolutionViewListener *view)
{
    this->view = view;

    layout = nullptr;
    initLayer();
}

QBoxLayout *ConvolutionParametersDialog::getMainLayout() {
    initLayer();
    return layout;
}

void ConvolutionParametersDialog::initLayer() {
    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    initActivateFunctionTypeLayer();
    updateParameters();
}

void ConvolutionParametersDialog::initActivateFunctionTypeLayer() {
    QBoxLayout *layout = new QHBoxLayout();
    QLabel *lTitle = new QLabel(tr("Activate Function: "));

    cbActivateFunctionType = new QComboBox();
    cbActivateFunctionType->addItem(tr("Sigmoid"));
    cbActivateFunctionType->addItem(tr("Tanh"));
    cbActivateFunctionType->addItem(tr("ReLU"));
    connect(cbActivateFunctionType, SIGNAL(currentIndexChanged(int)), this, SLOT(onActivateFunctionTypeChanged()));

    layout->addWidget(lTitle);
    layout->addWidget(cbActivateFunctionType);

    layout->setStretch(0, 1);
    layout->setStretch(1, 1);

    this->layout->addLayout(layout);
}

void ConvolutionParametersDialog::updateParameters() {
    cbActivateFunctionType->setCurrentIndex(view->getActivateFunctionType());
}

void ConvolutionParametersDialog::onActivateFunctionTypeChanged() {
    view->onActivateFunctionTypeChanged(cbActivateFunctionType->currentIndex());
}
