#ifndef DATAPARAMETERSDIALOG_H
#define DATAPARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;
class QTableWidget;
class DataAddTableItemDialog;

class DataParametersDialog : public QDialog
{
    Q_OBJECT
public:
    DataParametersDialog(QWidget *parent = nullptr);
    void initControllButtons();
    void initTable();
    void initButtons();

private:
    DataAddTableItemDialog *dialog;
    QBoxLayout *layout;
    QTableWidget *table;

private slots:
    void add();
    void remove();
    void addNewSet();

signals:
    void onApplied();
};

#endif // DATAPARAMETERSDIALOG_H
