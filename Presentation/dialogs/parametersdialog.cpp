#include "parametersdialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

#include "interactors/maininteractor.h"

ParametersDialog::ParametersDialog(MainInteractor* interactor)
{
    this->interactor = interactor;

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);

    initEpohLayer();
    initLearningRangeLayer();
    initEnableMomentLayer();
    initAlphaLayer();
    updateParameters();
}

void ParametersDialog::updateParameters() {
    leEpohNumber->setText(QString::number(interactor->getEpohNumber()));
    leLearningRange->setText(QString::number(interactor->getLearningRange()));

    double alpha = interactor->getAlpha();
    if (alpha > 0.0)
        cbMoment->setEnabled(true);

    leAlpha->setText(QString::number(alpha));
}

QBoxLayout *ParametersDialog::getMainLayout() {
    return layout;
}

void ParametersDialog::initEpohLayer() {
    QBoxLayout *epohLayout = new QHBoxLayout();
    QLabel *lEpohNumberTitle = new QLabel(tr("Epoh number: "));

    leEpohNumber = new QLineEdit();
    connect(leEpohNumber, SIGNAL(editingFinished()), this, SLOT(onEpohNumberChanged()));

    epohLayout->addWidget(lEpohNumberTitle);
    epohLayout->addWidget(leEpohNumber);

    epohLayout->setStretch(0, 2);
    epohLayout->setStretch(1, 1);

    layout->addLayout(epohLayout);
}

void ParametersDialog::initLearningRangeLayer() {
    QBoxLayout *learningRangeLayout = new QHBoxLayout();
    QLabel *lLearningRangeTitle = new QLabel(tr("Learning range: "));

    leLearningRange = new QLineEdit();
    connect(leLearningRange, SIGNAL(editingFinished()), this, SLOT(onLearningRangeChanged()));

    learningRangeLayout->addWidget(lLearningRangeTitle);
    learningRangeLayout->addWidget(leLearningRange);

    learningRangeLayout->setStretch(0, 2);
    learningRangeLayout->setStretch(1, 1);

    layout->addLayout(learningRangeLayout);
}

void ParametersDialog::initAlphaLayer() {
    QBoxLayout *alphaLayout = new QHBoxLayout();
    QLabel *lAlphaTitle = new QLabel(tr("Alpha: "));

    leAlpha = new QLineEdit();
    leAlpha->setEnabled(false);
    connect(leAlpha, SIGNAL(editingFinished()), this, SLOT(onAlphaChanged()));

    alphaLayout->addWidget(lAlphaTitle);
    alphaLayout->addWidget(leAlpha);

    alphaLayout->setStretch(0, 2);
    alphaLayout->setStretch(1, 1);

    layout->addLayout(alphaLayout);
}

void ParametersDialog::initEnableMomentLayer() {
    QBoxLayout *momentLayout = new QHBoxLayout();
    QLabel *lMomentTitle = new QLabel(tr("Use moment: "));

    cbMoment = new QCheckBox();
    connect(cbMoment, SIGNAL(stateChanged(int)), this, SLOT(onMomentEnableChanged()));

    momentLayout->addWidget(lMomentTitle);
    momentLayout->addWidget(cbMoment);

    momentLayout->setStretch(0, 2);
    momentLayout->setStretch(1, 1);

    layout->addLayout(momentLayout);
}

void ParametersDialog::onEpohNumberChanged() {
    QString value = leEpohNumber->text();

    if (value.isEmpty())
        return;

    interactor->setEpohNumber(value.toULong());
}

void ParametersDialog::onLearningRangeChanged() {
    QString value = leLearningRange->text();

    if (value.isEmpty())
        return;

    interactor->setLearningRange(value.toULong());
}

void ParametersDialog::onAlphaChanged() {
    QString value = leAlpha->text();

    if (value.isEmpty())
        return;

    interactor->setAlpha(value.toULong());
}

void ParametersDialog::onMomentEnableChanged() {
    leAlpha->setEnabled(cbMoment->isEnabled());
}
