#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>

class QBoxLayout;
class MainInteractor;
class QLineEdit;
class QCheckBox;

class ParametersDialog : public QDialog
{
    Q_OBJECT
public:
    ParametersDialog(MainInteractor* interactor);
    QBoxLayout *getMainLayout();
    void updateParameters();

private:
    void initEpohLayer();
    void initLearningRangeLayer();
    void initAlphaLayer();
    void initEnableMomentLayer();

private:
    QBoxLayout *layout, *leftLayout, *rightLayout;
    MainInteractor* interactor;
    QLineEdit *leEpohNumber;
    QLineEdit *leLearningRange;
    QLineEdit *leAlpha;
    QCheckBox *cbMoment;

private slots:
    void onEpohNumberChanged();
    void onLearningRangeChanged();
    void onAlphaChanged();
    void onMomentEnableChanged();
};

#endif // PARAMETERSDIALOG_H
