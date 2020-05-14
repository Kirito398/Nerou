#include "paintscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QCoreApplication>
#include <QFileDialog>
#include <QBoxLayout>
#include <QGroupBox>

#include "views/dataview.h"
#include "views/arrowview.h"
#include "views/perceptronview.h"
#include "views/convolutionview.h"
#include "views/tabledataview.h"
#include "models/selectoritem.h"
#include "interactors/maininteractor.h"
#include "repositories/mainrepository.h"
#include "interfaces/mainwindowinterface.h"
#include "dialogs/addoutputneuronsdialog.h"
#include "dialogs/progresstrainingdialog.h"
#include "dialogs/parametersdialog.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    interactor = MainInteractor::getInstance(new MainRepository());
    interactor->setView(this);

    line = nullptr;
    selector = nullptr;
    progressDialog = nullptr;
    parametersDialog = nullptr;
    propertiesBox = nullptr;

    mode = PaintScene::Selector;
    viewType = MovingView::Perceptron;
}

void PaintScene::onTrainingStarted(unsigned int iterationCount) {
    progressDialog->setMaxIteration(iterationCount);
}

void PaintScene::onTestingStarted(unsigned int iterationCount) {
    progressDialog->setMaxIteration(iterationCount);
}

void PaintScene::onProcessStarted(unsigned int iterationCount, unsigned int epohCount) {
    if (progressDialog == nullptr)
        progressDialog = new ProgressTrainingDialog();

    progressDialog->resetData();
    progressDialog->setMaxEpoh(epohCount);
    progressDialog->setTotalProcess(iterationCount * epohCount);

//    QPointF position = view->getSceneTop();
//    progressDialog->setGeometry(position.x() + 50, position.y() + 95, progressDialog->width(), progressDialog->height());
    progressDialog->onProcessStarted();
}

void PaintScene::onEpohChanged(unsigned int currentEpoh) {
    progressDialog->resetEpohData();
    progressDialog->setCurrentEpoh(currentEpoh);
}

void PaintScene::onIterationChanged(unsigned int currentIteration) {
    progressDialog->setCurrentIteration(currentIteration);
}

void PaintScene::onErrorValueChanged(double value) {
    progressDialog->setCurrentError(value);
}

void PaintScene::onTrainingTotalLossValueChanged(double value) {
    progressDialog->setCurrentTrainingTotalLossValue(value);
}

void PaintScene::onTestingTotalLossValueChanged(double value) {
    progressDialog->setCurrentTestingTotalLossValue(value);
}

void PaintScene::onAccuracyChanged(double value) {
    progressDialog->setCurrentAccuracy(value);
}

void PaintScene::onProcessFinished() {
    progressDialog->onProcessFinished();
}

void PaintScene::onLoadingActionClicked() {
    QString file = QFileDialog::getOpenFileName(nullptr, "", "/home", "*.nro");
    if (file != "")
        interactor->load(file.toStdString());
}

void PaintScene::onSavingActionClicked() {
    QString file = QString::fromStdString(interactor->getCurrentProjectName());

    if (file == "Untitled")
        file = QFileDialog::getSaveFileName(nullptr, tr("Save project"), "/home", "*.nro");

    if (file != "")
        interactor->save(file.toStdString());
}

void PaintScene::onProjectNameChanged(std::string name) {
    view->setProjectName(QString::fromStdString(name));
}

QString PaintScene::getProjectName() {
    return QString::fromStdString(interactor->getCurrentProjectName());
}

void PaintScene::onNewPerceptronAdded(PerceptronInteractorListener *perceptron) {
    PerceptronView *view = new PerceptronView(perceptron);

    view->setView(this);
    view->setSelected(true);

    addItem(view);
}

void PaintScene::onNewDataAdded(DataInteractorListener *data) {
    DataView *view = new DataView(data);

    view->setView(this);
    view->setSelected(true);

    addItem(view);
}

void PaintScene::onNewConvolutionAdded(ConvolutionInteractorListener *convolution) {
    ConvolutionView *view = new ConvolutionView(convolution);

    view->setView(this);
    view->setSelected(true);

    addItem(view);
}

void PaintScene::onNewTableDataAdded(TableDataInteractorListener *tableData) {
    TableDataView *view = new TableDataView(tableData);

    view->setView(this);
    view->setSelected(true);

    addItem(view);
}

void PaintScene::onNewWeightAdded(ArrowInteractorListener *arrow, unsigned long startNeuronID, unsigned long endNeuronID) {
    addArrow(arrow, findView(startNeuronID), findView(endNeuronID));
}

void PaintScene::onNewCoreAdded(ArrowInteractorListener *arrow, unsigned long startNeuronID, unsigned long endNeuronID) {
    addArrow(arrow, findView(startNeuronID), findView(endNeuronID));
}

MovingView *PaintScene::findView(unsigned long neuronID) {
    MovingView *view = nullptr;

    QList<QGraphicsItem *> items = this->items();
    for (auto item : items) {
        view = dynamic_cast<MovingView *>(item);

        if (view == nullptr)
            continue;

        if (view->getID() == neuronID)
            break;
    }

    return view;
}

void PaintScene::moveSelectedItem(QPointF delta) {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    for (auto item : selectedItems) {
        MovingView *view = dynamic_cast<MovingView *>(item);
        if (view != nullptr)
            view->setPosition(item->pos() + delta);
    }
}

void PaintScene::onViewsModePress(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item =  this->itemAt(event->scenePos(), QTransform());
    if (item == nullptr)
        addMovingView(event->scenePos());
    else
        item->setSelected(true);
}

void PaintScene::onArrowsModePress(QGraphicsSceneMouseEvent *event) {
    line = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
    addItem(line);
}

void PaintScene::onSelectorModePress(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item =  this->itemAt(event->scenePos(), QTransform());
    if (item == nullptr) {
        selector = new SelectorItem(event->scenePos());
        selector->setView(this);
        addItem(selector);
    } else {
        if (!item->isSelected()) {
            this->clearSelection();
            item->setSelected(true);
        }
    }
}

void PaintScene::onViewsModeMove(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::onArrowsModeMove(QGraphicsSceneMouseEvent *event) {
    if (line == nullptr)
        return;

    QLineF newLine(line->line().p1(), event->scenePos());
    line->setLine(newLine);
}

void PaintScene::onSelectorModeMove(QGraphicsSceneMouseEvent *event) {
    if (selector != nullptr)
        selector->setEndPoint(event->scenePos());

    QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::onViewsModeRelease(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintScene::onArrowsModeRelease(QGraphicsSceneMouseEvent *event) {
    if (line == nullptr)
        return;

    addArrow();

    Q_UNUSED(event)
}

void PaintScene::onSelectorModeRelease(QGraphicsSceneMouseEvent *event) {
    if (selector == nullptr)
        return;

    QList<QGraphicsItem *> selectedItems = items(selector->boundingRect());

    for (auto item : selectedItems)
        item->setSelected(true);

    removeItem(selector);
    delete selector;

    Q_UNUSED(event)
}

void PaintScene::setMode(Mode mode) {
    this->mode = mode;
}

void PaintScene::setViewType(MovingView::ViewType type) {
    viewType = type;
}

MovingView::ViewType PaintScene::getViewType() {
    return viewType;
}

void PaintScene::addArrow() {
    QList<QGraphicsItem *> startItems = items(line->line().p1());
    if (startItems.count() && startItems.first() == line)
        startItems.removeFirst();

    QList<QGraphicsItem *> endItems = items(line->line().p2());
    if (endItems.count() && endItems.first() == line)
        endItems.removeFirst();

    if (startItems.count() && endItems.count() && startItems.first() != endItems.first()) {
        MovingView *startView = qgraphicsitem_cast<MovingView *>(startItems.first());
        MovingView *endView = qgraphicsitem_cast<MovingView *>(endItems.first());
        addArrow(startView, endView);
    }

    removeItem(line);
    delete line;
    line = nullptr;
}

void PaintScene::addArrow(MovingView *startView, MovingView *endView) {
    ArrowInteractorListener *listener = nullptr;

    if (startView->isOutputNeuron())
        return;

    if (startView->getType() == endView->getType()) {
        if (startView->getType() == MovingView::Perceptron)
            listener = interactor->createNewWeight(startView->getID(), endView->getID());

        if (startView->getType() == MovingView::Convolution)
            listener = interactor->createNewCore(startView->getID(), endView->getID());
    }

    if (startView->getType() != endView->getType()) {
        if (startView->getType() == MovingView::Data && endView->getType() == MovingView::Perceptron)
            listener = interactor->createNewWeight(startView->getID(), endView->getID());

        if (startView->getType() == MovingView::Data && endView->getType() == MovingView::Convolution)
            listener = interactor->createNewCore(startView->getID(), endView->getID());

        if (startView->getType() == MovingView::Convolution && endView->getType() == MovingView::Perceptron)
            listener = interactor->createNewWeight(startView->getID(), endView->getID());

        if (startView->getType() == MovingView::TableData && endView->getType() == MovingView::Perceptron)
            listener = interactor->createNewWeight(startView->getID(), endView->getID());
    }

    if (listener != nullptr)
        addArrow(listener, startView, endView);
}

void PaintScene::addArrow(ArrowInteractorListener *listener, MovingView *startView, MovingView *endView) {
    ArrowView *arrow = new ArrowView(listener, startView, endView);
    startView->addArrow(arrow);
    endView->addArrow(arrow);
    arrow->setZValue(-1000.0);
    arrow->updatePosition();
    arrow->setView(this);
    addItem(arrow);
}

void PaintScene::addMovingView(QPointF position) {
    switch (viewType) {
    case MovingView::Perceptron : {
        interactor->createNewPerceptron(position.x(), position.y());
        break;
    }
    case MovingView::Convolution : {
        interactor->createNewConvolution(position.x(), position.y());
        break;
    }
    case MovingView::Data : {
        interactor->createNewData(position.x(), position.y());
        break;
    }
    case MovingView::TableData : {
        interactor->createNewTableData(position.x(), position.y());
        break;
    }
    }
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton)
        return;

    if (mode != Selector)
        this->clearSelection();

    switch (mode) {
    case ScroolHandDrag:
        onSelectorModePress(event);
        break;
    case Selector:
        onSelectorModePress(event);
        break;
    case Views:
        onViewsModePress(event);
        break;
    case Arrows:
        onArrowsModePress(event);
        break;
    }

    QGraphicsScene::mousePressEvent(event);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    switch (mode) {
    case ScroolHandDrag:
        onSelectorModeMove(event);
        break;
    case Selector:
        onSelectorModeMove(event);
        break;
    case Arrows:
        onArrowsModeMove(event);
        break;
    case Views:
        onViewsModeMove(event);
        break;
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    switch (mode) {
    case ScroolHandDrag:
        onSelectorModeRelease(event);
        break;
    case Selector:
        onSelectorModeRelease(event);
        break;
    case Arrows:
        onArrowsModeRelease(event);
        break;
    case Views:
        onViewsModeRelease(event);
        break;
    }

    updatePropertiesBox();

    selector = nullptr;
    line = nullptr;
}

QPixmap PaintScene::getPerceptronIcon() const {
    return PerceptronView().getItemIcon();
}

QPixmap PaintScene::getDataIcon() const {
    return DataView().getItemIcon();
}

QPixmap PaintScene::getTableDataIcon() const {
    return TableDataView().getItemIcon();
}

QPixmap PaintScene::getConvolutionIcon() const {
    return ConvolutionView().getItemIcon();
}

void PaintScene::onDeleteBtnClicked() {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    for (auto item : selectedItems) {
        ArrowView * arrowView = dynamic_cast<ArrowView *>(item);
        if (arrowView == nullptr)
            continue;
        delete item;
    }

    selectedItems = this->selectedItems();
    for (auto item : selectedItems) {
        MovingView *moveItem = dynamic_cast<MovingView *>(item);
        if (moveItem == nullptr)
            continue;
        delete item;
    }

    updatePropertiesBox();
}

void PaintScene::onAddOutputNeuronsActionClicked() {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    QList<MovingView *> inputsView;

    for (auto item : selectedItems) {
        MovingView *view = dynamic_cast<MovingView*>(item);
        if (view == nullptr)
            continue;
        if (!view->isOutputNeuron())
            inputsView.append(view);
    }

    if (inputsView.empty())
        return;

    QPointF position = inputsView[0]->pos();
    double maxX = position.x();
    double maxY = position.y();
    double minY = maxY;
    for (auto item : inputsView) {
        QPointF position = item->pos();

        if (position.x() > maxX)
            maxX = position.x();

        if (position.y() > maxY)
            maxY = position.y();

        if (position.y() < minY)
            minY = position.y();
    }

    AddOutputNeuronsDialog dlg;
    int result = dlg.exec();

    if (result == QDialog::Rejected)
        return;

    int number = dlg.getNeuronsNumber().toInt();

    if (number <= 0)
        return;

    clearSelectedItem();

    double deltaY = (maxY - minY) < 0.05 ? maxY : (maxY + minY) / 2.0;
    double delta = 120;
    double posX = maxX + 60 * number;
    double posY = deltaY - ((number - 1) * delta) / 2.0;

    for (int i = 0; i < number; i++)
        interactor->createNewPerceptron(posX, posY + delta * i);

    selectedItems.clear();
    selectedItems = this->selectedItems();
    QList<MovingView *> outputsView;

    for (auto item : selectedItems) {
        MovingView *view = dynamic_cast<MovingView *>(item);
        if (item != nullptr)
            outputsView.append(view);
    }

    for (auto inputView : inputsView) {
        for (auto outputView : outputsView) {
            addArrow(inputView, outputView);
        }
    }
}

void PaintScene::onRunBtnClicked() {
    interactor->run();
}

void PaintScene::onStopActionClicked() {
    interactor->stop();
}

void PaintScene::onPauseActionClicked() {
    interactor->pause();
}

void PaintScene::onDebugActionClicked() {
    interactor->debugRun();
}

void PaintScene::setSelectedItemOutputsEnable(bool enable) {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    QList<PerceptronView *> perceptronList;

    for (auto item : selectedItems) {
        PerceptronView *perceptron = dynamic_cast<PerceptronView *>(item);

        if (perceptron == nullptr)
            continue;

        perceptronList.append(perceptron);
    }

    for (auto perceptron : perceptronList)
        perceptron->setOutputNeuron(enable);

    this->clearSelectedItem();
}

void PaintScene::setView(MainWindowInterface *interfaces) {
    view = interfaces;
}

void PaintScene::setPropertiesLayout(QBoxLayout *layout) {
    propertiesLayout = layout;

    if (progressDialog == nullptr)
        progressDialog = new ProgressTrainingDialog();

    QGroupBox *progress = new QGroupBox(tr("Progress"));
    progress->setLayout(progressDialog->getMainLayout());

    if (parametersDialog == nullptr)
        parametersDialog = new ParametersDialog(interactor);

    propertiesBox = new QGroupBox(tr("Properties"));
    propertiesBox->setLayout(parametersDialog->getMainLayout());

    propertiesLayout->insertWidget(0, progress);
    propertiesLayout->insertWidget(1, propertiesBox);

    updatePropertiesBox();
}

void PaintScene::updatePropertiesBox() {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    QList<MovingView *> inputsView;
    QBoxLayout *layout = nullptr;

    for (auto item : selectedItems) {
        MovingView *view = dynamic_cast<MovingView*>(item);
        if (view == nullptr)
            continue;

        inputsView.append(view);
    }

    if (inputsView.isEmpty()) {
        layout = parametersDialog->getMainLayout();
    } else {
        layout = inputsView.at(0)->getPropertiesLayout();
    }

    propertiesBox->hide();
    delete propertiesBox->layout();
    delete propertiesBox;

    propertiesBox = new QGroupBox(tr("Properties"));
    propertiesBox->setLayout(layout);

    propertiesLayout->addWidget(propertiesBox);

    propertiesLayout->setStretch(0, 1);
    propertiesLayout->setStretch(1, 3);

    propertiesLayout->update();
    view->updateWindow();
}

QStringList PaintScene::getOutputsNeuronsList() {
    std::vector<unsigned long> list = interactor->getOutputsNeuronsList();
    QStringList neuronsList;

    for (auto neuron : list)
        neuronsList << "Neuron_" + QString::number(neuron);

    return neuronsList;
}

QList<QGraphicsItem *> PaintScene::getSelectedMovingView() {
    return this->selectedItems();
}

QAction *PaintScene::getAction(int type) {
    return view->getAction(type);
}

void PaintScene::clearSelectedItem() {
    clearSelection();
}

void PaintScene::updateScene() {
    this->update();
}

void PaintScene::updateItem(QGraphicsItem *item) {
    QSizeF size = item->boundingRect().size();
    update(QRectF(item->pos() - QPointF(-size.width() / 2.0, -size.height() / 2.0), size));
    QCoreApplication::processEvents(QEventLoop::AllEvents);
}

void PaintScene::deleteItem(QGraphicsItem *item) {
    removeItem(item);
}
