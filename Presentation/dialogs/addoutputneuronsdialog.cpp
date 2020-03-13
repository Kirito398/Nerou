#include "addoutputneuronsdialog.h"

#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>

AddOutputNeuronsDialog::AddOutputNeuronsDialog(QWidget *parent) : QDialog(parent)
{   
    setWindowTitle(tr("Add output neurons"));
    setFixedSize(QSize(200,100));

    QBoxLayout *layout = new QVBoxLayout();
    leNeuronsNumber = new QLineEdit();
    leNeuronsNumber->setPlaceholderText(tr("Neurons number"));
    layout->addWidget(leNeuronsNumber);

    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("OK"));
    connect(pbOk, SIGNAL(clicked()), SLOT(accept()));
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
    setLayout(layout);
}

QString AddOutputNeuronsDialog::getNeuronsNumber() const {
    return leNeuronsNumber->text();
}
