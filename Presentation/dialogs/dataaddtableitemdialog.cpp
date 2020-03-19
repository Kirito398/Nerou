#include "dataaddtableitemdialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QFileDialog>
#include <QImageReader>
#include <QComboBox>

#include "interfaces/repositoryinterface.h"

DataAddTableItemDialog::DataAddTableItemDialog(RepositoryInterface *repository, QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Add new set"));
    setFixedSize(QSize(350, 250));

    layout = new QVBoxLayout();
    defaultImageSize = nullptr;

    neuronTitle = new QLabel(tr("Neuron class:"));
    neuronsComboBox = new QComboBox();

    layout->addWidget(neuronTitle);
    layout->addWidget(neuronsComboBox);

    this->repository = repository;

    initTrainingLayout();
    initTestingLayout();
    initControllButtons();

    setLayout(layout);
}

void DataAddTableItemDialog::onAccept() {
    if (onAddButtonClicked())
        emit QDialog::accept();
}

bool DataAddTableItemDialog::onAddButtonClicked() {
    QString trainingPath = trainingSetPath->text();
    QString testingPath = testingSetPath->text();

    if (neuronsComboBox->itemText(neuronsComboBox->currentIndex()).isEmpty())
        return false;

    if (trainingPath.isEmpty() && testingPath.isEmpty())
        return false;

    QStringList listPath = getPaths(trainingPath + "/");

    if (listPath.isEmpty() && !trainingPath.isEmpty()) {
        trainingSetPathErrors->setText(tr("Image not found!"));
        return false;
    }

    if (!testImageSize(listPath)) {
        trainingSetPathErrors->setText(tr("Image must have the same size!"));
        return false;
    }

    listPath.clear();
    listPath = getPaths(testingPath + "/");

    if (listPath.isEmpty() && !testingPath.isEmpty()) {
        testingSetPathErrors->setText(tr("Image not found!"));
        return false;
    }

    if (!testImageSize(listPath)) {
        testingSetPathErrors->setText(tr("Image must have the same size!"));
        return false;
    }

    emit onApplied();

    trainingSetPath->setText("");
    testingSetPath->setText("");
    trainingSetPathErrors->setText("");
    testingSetPathErrors->setText("");

    return true;
}

QStringList DataAddTableItemDialog::getPaths(QString mainPath) {
    QStringList list;

    if (mainPath.isEmpty())
        return list;

    std::vector<std::string> paths = repository->getPaths(mainPath.toStdString());

    for (auto path : paths)
        list.append(QString::fromStdString(path));

    return list;
}

bool DataAddTableItemDialog::testImageSize(QStringList listPath) {
    if (listPath.isEmpty())
        return true;

    QImageReader reader(listPath.first());
    QImage image = reader.read();

    if (defaultImageSize == nullptr)
        defaultImageSize = new QSize(image.size());

    if (!listPath.isEmpty()) {
        for (auto path : listPath) {
            reader.setFileName(path);
            image = reader.read();

            if (defaultImageSize->width() != image.size().width() || defaultImageSize->height() != image.size().height())
                return false;
        }
    }

    return true;
}

void DataAddTableItemDialog::onTrainingSetBrowseClicked() {
    QFileDialog dialog(this);
    dialog.setOptions(QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);
    QString path = dialog.getExistingDirectory(this, tr("Set folder"), QDir::currentPath());

    if (defaultImageSize != nullptr) {
        delete defaultImageSize;
        defaultImageSize = nullptr;
    }

    if (path.isEmpty())
        return;

    trainingSetPath->setText(path);
}

void DataAddTableItemDialog::onTestingSetBrowseClicked() {
    QString path = QFileDialog::getExistingDirectory(this, tr("Set folder"), QDir::currentPath());

    if (defaultImageSize != nullptr) {
        delete defaultImageSize;
        defaultImageSize = nullptr;
    }

    if (path.isEmpty())
        return;

    testingSetPath->setText(path);
}

void DataAddTableItemDialog::initControllButtons() {
    QBoxLayout *buttonsLayout = new QHBoxLayout();

    QPushButton *pbOk = new QPushButton(tr("OK"));
    connect(pbOk, &QPushButton::clicked, this, &DataAddTableItemDialog::onAccept);
    buttonsLayout->addWidget(pbOk);

    QPushButton *pbApply = new QPushButton(tr("Add"));
    connect(pbApply, &QPushButton::clicked, this, &DataAddTableItemDialog::onAddButtonClicked);
    buttonsLayout->addWidget(pbApply);

    QPushButton *pbCancel = new QPushButton(tr("Cancel"));
    connect(pbCancel, SIGNAL(clicked()), SLOT(reject()));
    buttonsLayout->addWidget(pbCancel);

    layout->addLayout(buttonsLayout);
}

void DataAddTableItemDialog::initTrainingLayout() {
    trainingSetTitle = new QLabel(tr("Training class set:"));
    trainingSetPath = new QLineEdit("");
    trainingSetPathErrors = new QLabel();
    trainingSetPathErrors->setStyleSheet("QLabel {color : red;}");
    pbBrowseTrainingPath = new QPushButton(tr("Browse"));
    connect(pbBrowseTrainingPath, &QPushButton::clicked, this, &DataAddTableItemDialog::onTrainingSetBrowseClicked);

    QBoxLayout *trainingLayout = new QVBoxLayout();
    trainingLayout->addWidget(trainingSetTitle);

    QHBoxLayout *trainingPathLayout = new QHBoxLayout();
    trainingPathLayout->addWidget(trainingSetPath);
    trainingPathLayout->addWidget(pbBrowseTrainingPath);
    trainingLayout->addLayout(trainingPathLayout);
    trainingLayout->addWidget(trainingSetPathErrors);

    layout->addLayout(trainingLayout);
}

void DataAddTableItemDialog::initTestingLayout() {
    testingSetTitle = new QLabel(tr("Testing class set:"));
    testingSetPath = new QLineEdit("");
    testingSetPathErrors = new QLabel();
    testingSetPathErrors->setStyleSheet("QLabel {color : red;}");
    pbBrowseTestingPath = new QPushButton(tr("Browse"));
    connect(pbBrowseTestingPath, &QPushButton::clicked, this, &DataAddTableItemDialog::onTestingSetBrowseClicked);

    QBoxLayout *testingLayout = new QVBoxLayout();
    testingLayout->addWidget(testingSetTitle);

    QHBoxLayout *testingPathLayout = new QHBoxLayout();
    testingPathLayout->addWidget(testingSetPath);
    testingPathLayout->addWidget(pbBrowseTestingPath);
    testingLayout->addLayout(testingPathLayout);
    testingLayout->addWidget(testingSetPathErrors);

    layout->addLayout(testingLayout);
}

void DataAddTableItemDialog::setOutputsNeuronsList(QStringList list) {
    QString currentItem = neuronsComboBox->itemText(neuronsComboBox->currentIndex());

    neuronsList.clear();
    neuronsList.append(list);

    neuronsComboBox->clear();
    neuronsComboBox->addItems(neuronsList);

    if (neuronsList.contains(currentItem))
        neuronsComboBox->setCurrentIndex(neuronsComboBox->findText(currentItem));
}

QSize *DataAddTableItemDialog::getDefaultImageSize() {
    return defaultImageSize;
}

QString DataAddTableItemDialog::getTrainingSetPath() {
    return trainingSetPath->text();
}

QString DataAddTableItemDialog::getTestingSetPath() {
    return testingSetPath->text();
}

QString DataAddTableItemDialog::getNeuronID() {
    return neuronsComboBox->itemText(neuronsComboBox->currentIndex());
}