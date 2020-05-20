#ifndef CONVOLUTIONPARAMETERSDIALOG_H
#define CONVOLUTIONPARAMETERSDIALOG_H

#include <QDialog>

class ConvolutionViewListener;
class QBoxLayout;
class QComboBox;
class QLineEdit;

class ConvolutionParametersDialog : public QDialog
{
    Q_OBJECT
public:
    ConvolutionParametersDialog(ConvolutionViewListener *view);
    QBoxLayout *getMainLayout();

private:
    void initLayer();
    void updateParameters();
    void initActivateFunctionTypeLayer();
    void initCoreSizeLayer();
    void initPoolCoreSizeLayer();

private:
    ConvolutionViewListener *view;
    QBoxLayout *layout;
    QComboBox *cbActivateFunctionType;
    QLineEdit *leCoreSize, *lePoolCoreSize;

private slots:
    void onActivateFunctionTypeChanged();
    void onCoreSizeChanged();
    void onPoolCoreSizeChanged();
};

#endif // CONVOLUTIONPARAMETERSDIALOG_H
