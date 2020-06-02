#include "addoutputneuronsdialog.h"

#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>

AddOutputNeuronsDialog::AddOutputNeuronsDialog(QWidget *parent) : QDialog(parent)
{   
    setWindowTitle(tr("Добавление выходных нейронов"));
    setFixedSize(QSize(300,150));

    layout = new QVBoxLayout();

    initNeuronTypeLayer();
    initNeuronNumberLayer();
    initControlLayer();

    setLayout(layout);
}

void AddOutputNeuronsDialog::initNeuronTypeLayer() {
    QBoxLayout *neuronTypeLayout = new QHBoxLayout();
    QLabel *lTitle = new QLabel(tr("Тип нейрона: "));

    cbNeuronType = new QComboBox();
    cbNeuronType->addItem(tr("Перцептрон"));
    cbNeuronType->addItem(tr("Сверточный"));

    neuronTypeLayout->addWidget(lTitle);
    neuronTypeLayout->addWidget(cbNeuronType);

    layout->addLayout(neuronTypeLayout);
}

void AddOutputNeuronsDialog::initNeuronNumberLayer() {
    leNeuronsNumber = new QLineEdit();
    leNeuronsNumber->setPlaceholderText(tr("Количество нейронов"));
    layout->addWidget(leNeuronsNumber);
}

void AddOutputNeuronsDialog::initControlLayer() {
    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("Добавить"));
    connect(pbOk, SIGNAL(clicked()), SLOT(accept()));
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbCancel = new QPushButton(tr("Отмена"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
}

int AddOutputNeuronsDialog::getNeuronType() const {
    return cbNeuronType->currentIndex();
}

QString AddOutputNeuronsDialog::getNeuronsNumber() const {
    return leNeuronsNumber->text();
}
