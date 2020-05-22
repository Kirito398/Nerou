#ifndef ADDOUTPUTNEURONSDIALOG_H
#define ADDOUTPUTNEURONSDIALOG_H

#include <QDialog>

class QLineEdit;
class QBoxLayout;
class QComboBox;

class AddOutputNeuronsDialog : public QDialog
{
public:
    AddOutputNeuronsDialog(QWidget *parent = nullptr);
    void initNeuronNumberLayer();
    void initNeuronTypeLayer();
    void initControlLayer();
    QString getNeuronsNumber() const;
    int getNeuronType() const;

private:
    QLineEdit *leNeuronsNumber;
    QBoxLayout *layout;
    QComboBox *cbNeuronType;
};

#endif // ADDOUTPUTNEURONSDIALOG_H
