/*!
    @file
    @brief Заголовочный файл с классом главного окна
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string.h>

#include <QImage>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QWidget>

#include "../3DViewerControl/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

/*!
  @class MainWindow
  @brief Класс MainWindow, осуществляющий отображение главного окна с моделью и
данными
*/
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_clicked();
  void on_pushScaleButton_clicked();
  void on_pushTranslateButton_clicked();

  void on_horizontalSliderScale_valueChanged(int value);

  void on_horizontalSliderRotateX_valueChanged(int value);
  void on_horizontalSliderRotateY_valueChanged(int value);
  void on_horizontalSliderRotateZ_valueChanged(int value);

  void on_horizontalSliderTranslateX_valueChanged(int value);
  void on_horizontalSliderTranslateY_valueChanged(int value);
  void on_horizontalSliderTranslateZ_valueChanged(int value);

  void on_spinBoxRotateX_valueChanged(int arg1);
  void on_spinBoxRotateY_valueChanged(int arg1);
  void on_spinBoxRotateZ_valueChanged(int arg1);

  void on_radioButtonParallel_toggled(bool checked);
  void on_radioButtonCentral_toggled(bool checked);
  void on_radioButtonStippleLine_toggled(bool checked);
  void on_doubleSpinBoxLineSize_valueChanged(double arg1);

  void on_horizontalSliderLineSize_valueChanged(int value);
  void on_doubleSpinBoxPointSize_valueChanged(double arg1);

  void on_horizontalSliderPointSize_valueChanged(int value);

  void on_radioButtonPointTypeNone_toggled(bool checked);

  void on_radioButtonPointTypeRound_toggled(bool checked);

  void on_radioButtonPointTypeSquare_toggled(bool checked);

  void on_pushButtonPointColor_clicked();

  void on_pushButtonLineColor_clicked();

  void on_pushButtonWidgetColor_clicked();
  void on_pushButtonSaveScreenshot_clicked();

  void on_pushButtonSaveGif_clicked();
  void on_pushButtonContinue();

 signals:
  void signal(QString);
  void signalScale(float scale, char type);
  void signalTranslate(float value, char axis, float mult, char type);
  void signalRotate(float value, char axis);
  void signalProjectionTypeChange(int);
  void signalLineTypeChange(bool);
  void signalLineSizeChange(double);
  void signalPointTypeChange(int);
  void signalPointSizeChange(double);
  void signalPointColorChange(QColor);
  void signalLineColorChange(QColor);
  void signalWidgetColorChange(QColor);

 private:
  QWidget *select_type_image = new QWidget();
  QRadioButton *jpeg_type = new QRadioButton("jpeg", select_type_image);
  QRadioButton *bmp_type = new QRadioButton("bmp", select_type_image);
  QPushButton *b_continue = new QPushButton("Continue", select_type_image);
  QPushButton *b_cancel = new QPushButton("Cancel", select_type_image);
  void SetPointColor(QColor);
  void SetWidgetColor(QColor);
  void SetLineColor(QColor);
  void ResetState();
  void SettingsApply();

  s21::controller *controller_ = nullptr;
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
