#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <cstring>
#include <iostream>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  controller_ = new s21::controller();

  ui->horizontalLayout->insertWidget(0, controller_->WidgetGet());

  select_type_image->setFixedSize(220, 60);
  jpeg_type->move(110, 10);
  bmp_type->move(50, 10);
  b_continue->setGeometry(140, 30, 70, 25);
  b_cancel->setGeometry(60, 30, 70, 25);
  b_continue->setDisabled(true);
  connect(jpeg_type, &QRadioButton::clicked, b_continue,
          &QPushButton::setEnabled);
  connect(bmp_type, &QRadioButton::clicked, b_continue,
          &QPushButton::setEnabled);
  connect(b_continue, &QPushButton::clicked, this,
          &MainWindow::on_pushButtonContinue);
  connect(b_cancel, &QPushButton::clicked, select_type_image, &QWidget::close);
  connect(this, &MainWindow::signal, controller_, &s21::controller::slot);
  connect(this, &MainWindow::signalScale, controller_,
          &s21::controller::slotScale);
  connect(this, &MainWindow::signalTranslate, controller_,
          &s21::controller::slotTranslate);
  connect(this, &MainWindow::signalRotate, controller_,
          &s21::controller::slotRotate);
  connect(this, &MainWindow::signalProjectionTypeChange, controller_,
          &s21::controller::slotProjectionTypeChange);
  connect(this, &MainWindow::signalLineTypeChange, controller_,
          &s21::controller::slotLineTypeChange);
  connect(this, &MainWindow::signalLineSizeChange, controller_,
          &s21::controller::slotLineSizeChange);
  connect(this, &MainWindow::signalPointTypeChange, controller_,
          &s21::controller::slotPointTypeChange);
  connect(this, &MainWindow::signalPointSizeChange, controller_,
          &s21::controller::slotPointSizeChange);
  connect(this, &MainWindow::signalPointColorChange, controller_,
          &s21::controller::slotPointColorChange);
  connect(this, &MainWindow::signalLineColorChange, controller_,
          &s21::controller::slotLineColorChange);
  connect(this, &MainWindow::signalWidgetColorChange, controller_,
          &s21::controller::slotWidgetColorChange);

  controller_->SettingsRead();
  SettingsApply();
}

MainWindow::~MainWindow() {
  controller_->SettingsWrite();
  delete controller_;
  delete ui;
}

void MainWindow::ResetState() {
  ui->horizontalSliderScale->setSliderPosition(200);
  ui->horizontalSliderTranslateX->setSliderPosition(0);
  ui->horizontalSliderTranslateY->setSliderPosition(0);
  ui->horizontalSliderTranslateZ->setSliderPosition(0);
  ui->horizontalSliderRotateX->setSliderPosition(0);
  ui->horizontalSliderRotateY->setSliderPosition(0);
  ui->horizontalSliderRotateZ->setSliderPosition(0);
  ui->doubleTranslateKSpinBox->setValue(0.0);
}

void MainWindow::SettingsApply() {
  if (controller_->GetProjectionType()) {
    ui->radioButtonCentral->setChecked(true);
  } else {
    ui->radioButtonParallel->setChecked(true);
  }
  ui->labelBackgroundColor->setStyleSheet(
      "background-color : " + controller_->GetBgQColor().name() + "");
  ui->labelPointColor->setStyleSheet(
      "background-color : " + controller_->GetPointQColor().name() + "");
  ui->labelLineColor->setStyleSheet(
      "background-color : " + controller_->GetLineQColor().name() + "");
  if (controller_->GetPointType() == 0) {
    ui->labelPointSize->setEnabled(false);
    ui->doubleSpinBoxPointSize->setEnabled(false);
    ui->horizontalSliderPointSize->setEnabled(false);
    ui->radioButtonPointTypeNone->setChecked(true);
  } else if (controller_->GetPointType() == 1) {
    ui->radioButtonPointTypeRound->setChecked(true);
  } else {
    ui->radioButtonPointTypeSquare->setChecked(true);
  }
  if (controller_->GetLineType() == 0) {
    ui->radioButtonSolidLine->setChecked(true);
  } else {
    ui->radioButtonStippleLine->setChecked(true);
  }
  ui->horizontalSliderPointSize->setValue(controller_->GetPointSize() * 10);
  ui->horizontalSliderLineSize->setValue(controller_->GetLineSize() * 10);
}

// Кнопка открыть файл
void MainWindow::on_pushButton_clicked() {
  QString qstr = QFileDialog::getOpenFileName(this, "Выбрать файл",
                                              "../obj_files", ".obj (*.obj)");
  if (strlen(qPrintable(qstr))) {
    ResetState();
    ui->label->setText(qstr);
    emit signal(qstr);
    char str[256] = {'\0'};
    strcat(str, qPrintable(qstr));
    ui->statusbar->showMessage(
        QString("File name: %1   Vertexes: %2   Polygons: %3   Edges: %4")
            .arg(strrchr(str, '/') + 1)
            .arg(controller_->ModelGetVerticesCount())
            .arg(controller_->ModelGetPolygonCount())
            .arg(controller_->ModelGetEdgesCount()));
    ui->labelScaleValue->setText(
        QString::number(controller_->ModelGetScale(), 'f', 2));
    ui->labelTranslateValueX->setText(
        QString::number(controller_->ModelGetPosition('x'), 'f', 2));
    ui->labelTranslateValueY->setText(
        QString::number(controller_->ModelGetPosition('y'), 'f', 2));
    ui->labelTranslateValueZ->setText(
        QString::number(controller_->ModelGetPosition('z'), 'f', 2));
  }
}

// Кнопка масштаба(применить)
void MainWindow::on_pushScaleButton_clicked() {
  emit signalScale((float)ui->doubleScaleSpinBox->value(), 'b');
  ui->labelScaleValue->setText(
      QString::number(controller_->ModelGetScale(), 'f', 2));
}

// Кнопка движения(применить)
void MainWindow::on_pushTranslateButton_clicked() {
  emit signalTranslate((float)ui->doubleTranslateXSpinBox->value(), 'x', 1,
                       'b');
  emit signalTranslate((float)ui->doubleTranslateYSpinBox->value(), 'y', 1,
                       'b');
  emit signalTranslate((float)ui->doubleTranslateZSpinBox->value(), 'z', 1,
                       'b');
  ui->labelTranslateValueX->setText(
      QString::number(controller_->ModelGetPosition('x'), 'f', 2));
  ui->labelTranslateValueY->setText(
      QString::number(controller_->ModelGetPosition('y'), 'f', 2));
  ui->labelTranslateValueZ->setText(
      QString::number(controller_->ModelGetPosition('z'), 'f', 2));
}

// Слайдер масштаба
void MainWindow::on_horizontalSliderScale_valueChanged(int value) {
  emit signalScale((float)value, 's');
  ui->labelScaleValue->setText(
      QString::number(controller_->ModelGetScale(), 'f', 2));
}

// Слайдер вращения по X
void MainWindow::on_horizontalSliderRotateX_valueChanged(int value) {
  int last_pos = controller_->GetRotationSliderPosition('x');
  controller_->SetRotationSliderPosition(value, 'x');
  ui->spinBoxRotateX->setValue(ui->spinBoxRotateX->value() + value - last_pos);
}

// Слайдер вращения по Y
void MainWindow::on_horizontalSliderRotateY_valueChanged(int value) {
  int last_pos = controller_->GetRotationSliderPosition('y');
  controller_->SetRotationSliderPosition(value, 'y');
  ui->spinBoxRotateY->setValue(ui->spinBoxRotateY->value() + value - last_pos);
}

// Слайдер вращения по Z
void MainWindow::on_horizontalSliderRotateZ_valueChanged(int value) {
  int last_pos = controller_->GetRotationSliderPosition('z');
  controller_->SetRotationSliderPosition(value, 'z');
  ui->spinBoxRotateZ->setValue(ui->spinBoxRotateZ->value() + value - last_pos);
}

// Слайдер движения по X
void MainWindow::on_horizontalSliderTranslateX_valueChanged(int value) {
  emit signalTranslate(value, 'x', ui->doubleTranslateKSpinBox->value(), 's');
  ui->labelTranslateValueX->setText(
      QString::number(controller_->ModelGetPosition('x'), 'f', 2));
}

// Слайдер движения по Y
void MainWindow::on_horizontalSliderTranslateY_valueChanged(int value) {
  emit signalTranslate(value, 'y', ui->doubleTranslateKSpinBox->value(), 's');
  ui->labelTranslateValueY->setText(
      QString::number(controller_->ModelGetPosition('y'), 'f', 2));
}

// Слайдер движения по Z
void MainWindow::on_horizontalSliderTranslateZ_valueChanged(int value) {
  emit signalTranslate(value, 'z', ui->doubleTranslateKSpinBox->value(), 's');
  ui->labelTranslateValueZ->setText(
      QString::number(controller_->ModelGetPosition('z'), 'f', 2));
}

// Вращение на величину по X
void MainWindow::on_spinBoxRotateX_valueChanged(int arg1) {
  emit signalRotate((float)arg1, 'x');
}

// Вращение на величину по Y
void MainWindow::on_spinBoxRotateY_valueChanged(int arg1) {
  emit signalRotate((float)arg1, 'y');
}

// Вращение на величину по Z
void MainWindow::on_spinBoxRotateZ_valueChanged(int arg1) {
  emit signalRotate((float)arg1, 'z');
}

// Выбор паралелльного вида
void MainWindow::on_radioButtonParallel_toggled(bool checked) {
  if (checked == true) {
    emit signalProjectionTypeChange(0);
  }
}

// Выбор центрального вида
void MainWindow::on_radioButtonCentral_toggled(bool checked) {
  if (checked == true) {
    emit signalProjectionTypeChange(1);
  }
}

// Выбор пунктирной линии
void MainWindow::on_radioButtonStippleLine_toggled(bool checked) {
  emit signalLineTypeChange(checked);
}

// Толшина линии вручную
void MainWindow::on_doubleSpinBoxLineSize_valueChanged(double arg1) {
  ui->horizontalSliderLineSize->setValue(arg1 * 10);
}

// Толщина линии слайдер
void MainWindow::on_horizontalSliderLineSize_valueChanged(int value) {
  emit signalLineSizeChange((double)value / 10);
  ui->doubleSpinBoxLineSize->setValue((double)value / 10);
}
// Размер вершины вручную
void MainWindow::on_doubleSpinBoxPointSize_valueChanged(double arg1) {
  ui->horizontalSliderPointSize->setValue(arg1 * 10);
}

// Размер вершины слайдер
void MainWindow::on_horizontalSliderPointSize_valueChanged(int value) {
  emit signalPointSizeChange((double)value / 10);
  ui->doubleSpinBoxPointSize->setValue((double)value / 10);
}

// Выбрано без вершин
void MainWindow::on_radioButtonPointTypeNone_toggled(bool checked) {
  ui->labelPointSize->setEnabled(!checked);
  ui->doubleSpinBoxPointSize->setEnabled(!checked);
  ui->horizontalSliderPointSize->setEnabled(!checked);
  if (checked) {
    emit signalPointTypeChange(0);
  }
}

// Выбраны круглые вершины
void MainWindow::on_radioButtonPointTypeRound_toggled(bool checked) {
  if (checked) {
    emit signalPointTypeChange(1);
  }
}

// Выбраны квадратные вершины
void MainWindow::on_radioButtonPointTypeSquare_toggled(bool checked) {
  if (checked) {
    emit signalPointTypeChange(2);
  }
}

// Выбор цвета вершин
void MainWindow::on_pushButtonPointColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    SetPointColor(color);
  }
}

// Индикатор выбранного цвета вершин
void MainWindow::SetPointColor(QColor color) {
  ui->labelPointColor->setStyleSheet("background-color : " + color.name() + "");
  emit signalPointColorChange(color);
}

// Выбор цвета линий
void MainWindow::on_pushButtonLineColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    SetLineColor(color);
  }
}

// Индикатор выбранного цвета линий
void MainWindow::SetLineColor(QColor color) {
  ui->labelLineColor->setStyleSheet("background-color : " + color.name() + "");
  emit signalLineColorChange(color);
}

// Выбор цвета фона
void MainWindow::on_pushButtonWidgetColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    SetWidgetColor(color);
  }
}

// Индикатор выбранного цвета фона
void MainWindow::SetWidgetColor(QColor color) {
  ui->labelBackgroundColor->setStyleSheet("background-color : " + color.name() +
                                          "");
  emit signalWidgetColorChange(color);
}

// Нажание кнопки скриншота
void MainWindow::on_pushButtonSaveScreenshot_clicked() {
  select_type_image->show();
}

// Нажатие кнопки сохранить gif файл
void MainWindow::on_pushButtonSaveGif_clicked() {
  ui->pushButtonSaveGif->setText("Recording");
  ui->pushButtonSaveGif->setEnabled(false);
  controller_->MakeGif(this);
  ui->pushButtonSaveGif->setText("Save as gif");
  ui->pushButtonSaveGif->setEnabled(true);
}

// Выбор расширения скриншота
void MainWindow::on_pushButtonContinue() {
  select_type_image->close();
  int type = 0;
  if (bmp_type->isChecked())
    type = 1;
  else if (jpeg_type->isChecked())
    type = 2;
  controller_->MakeScreenshot(this, type);
}