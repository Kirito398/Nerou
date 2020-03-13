#ifndef ADDOUTPUTNEURONSDIALOG_H
#define ADDOUTPUTNEURONSDIALOG_H

#include <QDialog>

class QLineEdit;

class AddOutputNeuronsDialog : public QDialog
{
public:
    AddOutputNeuronsDialog(QWidget *parent = nullptr);
    QString getNeuronsNumber() const;

private:
    QLineEdit *leNeuronsNumber;
};

#endif // ADDOUTPUTNEURONSDIALOG_H
