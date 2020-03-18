#ifndef DATAADDTABLEITEMDIALOG_H
#define DATAADDTABLEITEMDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QBoxLayout;
class QComboBox;

class DataAddTableItemDialog : public QDialog
{
    Q_OBJECT
public:
    DataAddTableItemDialog(QWidget *parent = nullptr);
    QString getTrainingSetPath();
    QString getTestingSetPath();
    QString getNeuronID();
    QSize *getDefaultImageSize();
    void setOutputsNeuronsList(QStringList list);

private:
    void initTrainingLayout();
    void initTestingLayout();
    void initControllButtons();
    bool testImageSize(QString mainPath, QStringList listPath);

private:
    QBoxLayout *layout;
    QLabel *trainingSetTitle;
    QLabel *testingSetTitle;
    QLabel *trainingSetPathErrors;
    QLabel *testingSetPathErrors;
    QLabel *neuronTitle;
    QLineEdit *trainingSetPath;
    QLineEdit *testingSetPath;
    QPushButton *pbBrowseTrainingPath;
    QPushButton *pbBrowseTestingPath;
    QSize *defaultImageSize;
    QComboBox *neuronsComboBox;
    QStringList neuronsList;

private slots:
    void onTrainingSetBrowseClicked();
    void onTestingSetBrowseClicked();
    void onAccept();
    bool onAddButtonClicked();

signals:
    void onApplied();
};

#endif // DATAADDTABLEITEMDIALOG_H
