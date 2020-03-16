#include "dataparametersdialog.h"

#include <QBoxLayout>
#include <QPushButton>

DataParametersDialog::DataParametersDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Data block parameters"));
    setFixedSize(QSize(350, 500));

    QBoxLayout *layout = new QVBoxLayout();

    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("OK"));
    connect(pbOk, SIGNAL(clicked()), SLOT(accept()));
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Apply"));
    connect(pbApply, SIGNAL(clicked()), SIGNAL(applied()));
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
    setLayout(layout);
}
