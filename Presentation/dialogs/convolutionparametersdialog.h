#ifndef CONVOLUTIONPARAMETERSDIALOG_H
#define CONVOLUTIONPARAMETERSDIALOG_H

#include <QDialog>

class ConvolutionViewListener;
class QBoxLayout;
class QComboBox;

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

private:
    ConvolutionViewListener *view;
    QBoxLayout *layout;
    QComboBox *cbActivateFunctionType;

private slots:
    void onActivateFunctionTypeChanged();
};

#endif // CONVOLUTIONPARAMETERSDIALOG_H
