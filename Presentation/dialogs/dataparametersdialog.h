#ifndef DATAPARAMETERSDIALOG_H
#define DATAPARAMETERSDIALOG_H

#include <QDialog>

class DataParametersDialog : public QDialog
{
public:
    DataParametersDialog(QWidget *parent = nullptr);

signals:
    void applied();
};

#endif // DATAPARAMETERSDIALOG_H
