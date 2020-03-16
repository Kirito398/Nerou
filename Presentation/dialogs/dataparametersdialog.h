#ifndef DATAPARAMETERSDIALOG_H
#define DATAPARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;
class QTableWidget;

class DataParametersDialog : public QDialog
{
public:
    DataParametersDialog(QWidget *parent = nullptr);
    void initControllButtons();
    void initTable();
    void initButtons();

private:
    QBoxLayout *layout;
    QTableWidget *table;

private slots:
    void onApplied();
    void onAccept();
    void add();
    void remove();
};

#endif // DATAPARAMETERSDIALOG_H
