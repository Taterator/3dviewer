#include "controller.h"

#include <QFileDialog>
#include <array>
#include <iostream>

s21::controller::controller() {
  openGLWidget_ = new OpenGLWidget();
  openGLWidget_->SetController(this);
  parameters_ = new ViewParameters();
  settings_ = new Settings(parameters_);
  recorder_ = new Recorder(this);
};
s21::controller::~controller() {
  delete object_;
  delete openGLWidget_;
  delete parameters_;
  delete settings_;
};

void s21::controller::ModelInitializer(QString str) {
  if (object_) delete object_;
  object_ = new s21::Object3D(str);
  object_->ScaleAndCenter();
  parameters_->SetTranslationSliderPosition(0);
  parameters_->SetScaleSliderValue(200);
}
void s21::controller::ModelDestructor() { delete object_; }

bool s21::controller::ModelIsNull() { return (object_ == nullptr); }

float *s21::controller::ModelGetVertices() {
  if (ModelIsNull()) return nullptr;
  return object_->GetVertices();
}
int s21::controller::ModelGetVerticesCount() {
  if (ModelIsNull()) return 0;
  return object_->GetVerticesCount();
}

int *s21::controller::ModelGetEdges() {
  if (ModelIsNull()) return nullptr;
  return object_->GetEdges();
}
int s21::controller::ModelGetEdgesCount() {
  if (ModelIsNull()) return 0;
  return object_->GetEdgesCount();
}

int s21::controller::ModelGetPolygonCount() {
  if (ModelIsNull()) return 0;
  return object_->GetPolygonCount();
}

void s21::controller::ModelScale(float scale) {
  if (!ModelIsNull()) object_->Scale(scale);
}
void s21::controller::ModelTranslate(float dx, float dy, float dz) {
  if (!ModelIsNull()) object_->Translate(dx, dy, dz);
}

void s21::controller::ModelTranslate(float value, char axis) {
  if (!ModelIsNull()) object_->Translate(value, axis);
}

void s21::controller::ModelRotate(float value, char axis) {
  if (!ModelIsNull()) {
    value = value - ModelGetRotation(axis);

    object_->Rotate(value, axis);
  }
}

void s21::controller::ModelRotateDelta(float value, char axis) {
  if (!ModelIsNull()) {
    object_->Rotate(value, axis);
  }
}

std::array<float, 3> s21::controller::ModelGetPosition() {
  if (ModelIsNull()) {
    std::array<float, 3> temp{0, 0, 0};
    return temp;
  }
  return object_->GetPosition();
}

float s21::controller::ModelGetPosition(char axis) {
  switch (axis) {
    case 'x':
      return ModelGetPosition()[0];
      break;
    case 'y':
      return ModelGetPosition()[1];
      break;
    case 'z':
      return ModelGetPosition()[2];
      break;
    default:
      break;
  }
  return 0;
}

std::array<float, 3> s21::controller::ModelGetRotation() {
  if (ModelIsNull()) {
    std::array<float, 3> temp{0, 0, 0};
    return temp;
  }
  return object_->GetRotation();
}

float s21::controller::ModelGetRotation(char axis) {
  switch (axis) {
    case 'x':
      return ModelGetRotation()[0];
      break;
    case 'y':
      return ModelGetRotation()[1];
      break;
    case 'z':
      return ModelGetRotation()[2];
      break;
    default:
      break;
  }
  return 0;
}

void s21::controller::ModelSetRotation(std::array<float, 3> rotation) {
  if (!ModelIsNull()) {
    object_->SetRotation(rotation);
  }
}

float s21::controller::ModelGetScale() {
  if (ModelIsNull()) return 0;
  return object_->GetScale();
}

s21::OpenGLWidget *s21::controller::WidgetGet() { return openGLWidget_; }

QImage s21::controller::getFramebuffer() {
  return openGLWidget_->grabFramebuffer();
}

void s21::controller::slot(QString qstr) {
  ModelInitializer(qstr);
  openGLWidget_->update();
}

void s21::controller::slotScale(float scale, char type) {
  if (ModelGetVertices() != nullptr) {
    double dScale = scale;
    switch (type) {
      case 's':
        dScale = ((scale / parameters_->GetScaleSliderValue()) + 1.) / 2.;
        ModelScale(dScale);
        parameters_->SetScaleSliderValue(parameters_->GetScaleSliderValue() *
                                         dScale);
        break;
      case 'b':
        ModelScale(dScale);
      default:
        break;
    }

    openGLWidget_->update();
  }
}

void s21::controller::slotTranslate(float value, char axis, float mult,
                                    char type) {
  if (ModelGetVertices() != nullptr) {
    float shift = 0;
    switch (type) {
      case 's':
        shift = (value - parameters_->GetTranslationSliderPosition(axis)) / 100;
        parameters_->SetTranslationSliderPosition(value, axis);
        break;
      case 'b':
        shift = value;
      default:
        break;
    }
    ModelTranslate(shift * mult, axis);
    openGLWidget_->update();
  }
}

void s21::controller::slotRotate(float value, char axis) {
  if (ModelGetVertices() != nullptr) {
    if (value != ModelGetRotation(axis)) ModelRotate(value, axis);
    openGLWidget_->update();
  }
}

void s21::controller::slotRotateDelta(float value, char axis) {
  if (ModelGetVertices() != nullptr) {
    ModelRotateDelta(value, axis);
    openGLWidget_->update();
  }
}

void s21::controller::slotProjectionTypeChange(int value) {
  parameters_->SetProjectionType(value);
  openGLWidget_->UpdateStrategy();
  openGLWidget_->update();
}

void s21::controller::slotLineTypeChange(bool checked) {
  parameters_->SetLineType(checked);
  openGLWidget_->update();
}

void s21::controller::slotLineSizeChange(double value) {
  parameters_->SetLineWidth(value);
  openGLWidget_->update();
}

void s21::controller::slotPointTypeChange(int value) {
  parameters_->SetPointType(value);
  openGLWidget_->update();
}

void s21::controller::slotPointSizeChange(double value) {
  parameters_->SetPointSize(value);
  openGLWidget_->update();
}

void s21::controller::slotPointColorChange(QColor color) {
  parameters_->SetPointColor(color);
  openGLWidget_->update();
}

void s21::controller::slotLineColorChange(QColor color) {
  parameters_->SetLineColor(color);
  openGLWidget_->update();
}

void s21::controller::slotWidgetColorChange(QColor color) {
  parameters_->SetBgColor(color);
  openGLWidget_->update();
}

void s21::controller::SettingsRead() {
  settings_->SettingsRead();
  openGLWidget_->UpdateStrategy();
}

void s21::controller::SettingsWrite() { settings_->SettingsWrite(); }

std::array<float, 4> s21::controller::GetPointColor() {
  return parameters_->GetPointColor();
}
std::array<float, 4> s21::controller::GetLineColor() {
  return parameters_->GetLineColor();
}
std::array<float, 4> s21::controller::GetBgColor() {
  return parameters_->GetBgColor();
}

QColor s21::controller::GetPointQColor() {
  return parameters_->GetPointQColor();
}
QColor s21::controller::GetLineQColor() { return parameters_->GetLineQColor(); }
QColor s21::controller::GetBgQColor() { return parameters_->GetBgQColor(); }

int s21::controller::GetProjectionType() {
  return parameters_->GetProjectionType();
}

int s21::controller::GetPointType() { return parameters_->GetPointType(); }
int s21::controller::GetLineType() { return parameters_->GetLineType(); }

float s21::controller::GetPointSize() { return parameters_->GetPointSize(); }
float s21::controller::GetLineSize() { return parameters_->GetLineWidth(); }

int s21::controller::GetWindowWidth() { return parameters_->GetWindowWidth(); }
int s21::controller::GetWindowHeight() {
  return parameters_->GetWindowHeight();
}
void s21::controller::SetWindowWidth(int value) {
  parameters_->SetWindowWidth(value);
}
void s21::controller::SetWindowHeight(int value) {
  parameters_->SetWindowHeight(value);
}

void s21::controller::MakeGif(QWidget *window) { recorder_->MakeGif(window); }

void s21::controller::MakeScreenshot(QWidget *window, int type) {
  recorder_->MakeScreenshot(window, type);
}

float s21::controller::GetRotationSliderPosition(char axis) {
  return parameters_->GetRotationSliderPosition(axis);
}

void s21::controller::SetRotationSliderPosition(float val, char axis) {
  parameters_->SetRotationSliderPosition(val, axis);
}