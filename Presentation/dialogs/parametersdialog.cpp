#include "parametersdialog.h"

#include <QBoxLayout>
#include <QLabel>

ParametersDialog::ParametersDialog()
{
    layout = new QVBoxLayout();

    QBoxLayout *epohLayout = new QHBoxLayout();
    QLabel *lEpohNumberTitle = new QLabel(tr("Epoh number: "));

    epohLayout->addWidget(lEpohNumberTitle);

    layout->addLayout(epohLayout);
}

void ParametersDialog::updateParameters() {

}

QBoxLayout *ParametersDialog::getMainLayout() {
    return layout;
}
