#include "convolutionparametersdialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

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
    initCoreSizeLayer();
    initPoolCoreSizeLayer();

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

void ConvolutionParametersDialog::initCoreSizeLayer() {
    QBoxLayout *coreSizeLayout = new QHBoxLayout();
    QLabel *lCoreSizeTitle = new QLabel(tr("Core size: "));

    leCoreSize = new QLineEdit();
    connect(leCoreSize, &QLineEdit::editingFinished, this, &ConvolutionParametersDialog::onCoreSizeChanged);

    coreSizeLayout->addWidget(lCoreSizeTitle);
    coreSizeLayout->addWidget(leCoreSize);

    coreSizeLayout->setStretch(0, 2);
    coreSizeLayout->setStretch(1, 1);

    layout->addLayout(coreSizeLayout);
}

void ConvolutionParametersDialog::initPoolCoreSizeLayer() {
    QBoxLayout *poolCoreSizeLayout = new QHBoxLayout();
    QLabel *lPoolCoreSizeTitle = new QLabel(tr("Pool core size: "));

    lePoolCoreSize = new QLineEdit();
    connect(lePoolCoreSize, &QLineEdit::editingFinished, this, &ConvolutionParametersDialog::onPoolCoreSizeChanged);

    poolCoreSizeLayout->addWidget(lPoolCoreSizeTitle);
    poolCoreSizeLayout->addWidget(lePoolCoreSize);

    poolCoreSizeLayout->setStretch(0, 2);
    poolCoreSizeLayout->setStretch(1, 1);

    layout->addLayout(poolCoreSizeLayout);
}

void ConvolutionParametersDialog::updateParameters() {
    cbActivateFunctionType->setCurrentIndex(view->getActivateFunctionType());
    leCoreSize->setText(QString::number(view->getCoreSize()));
    lePoolCoreSize->setText(QString::number(view->getPoolCoreSize()));
}

void ConvolutionParametersDialog::onActivateFunctionTypeChanged() {
    view->onActivateFunctionTypeChanged(cbActivateFunctionType->currentIndex());
}

void ConvolutionParametersDialog::onCoreSizeChanged() {
    QString value = leCoreSize->text();

    if (value.isEmpty())
        return;

    view->onCoreSizeChanged(value.toInt());
}

void ConvolutionParametersDialog::onPoolCoreSizeChanged() {
    QString value = lePoolCoreSize->text();

    if (value.isEmpty())
        return;

    view->onPoolCoreSizeChanged(value.toInt());
}
