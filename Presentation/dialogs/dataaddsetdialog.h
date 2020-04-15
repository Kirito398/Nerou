#ifndef DATAADDSETDIALOG_H
#define DATAADDSETDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;
class QBoxLayout;
class QComboBox;
class RepositoryInterface;

class DataAddSetDialog : public QDialog
{
    Q_OBJECT
public:
    DataAddSetDialog(RepositoryInterface *repository, QWidget *parent = nullptr);
    QString getTrainingSetPath();
    QString getTestingSetPath();
    QString getNeuronID();
    QSize *getDefaultImageSize();
    void setOutputsNeuronsList(QStringList list);

private:
    void initTrainingLayout();
    void initTestingLayout();
    void initControllButtons();
    bool testImageSize(QStringList listPath);
    QStringList getPaths(QString mainPath);

private:
    RepositoryInterface *repository;
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

#endif // DATAADDSETDIALOG_H
