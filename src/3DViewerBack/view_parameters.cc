#include "view_parameters.h"

void s21::ViewParameters::SetProjectionType(int value) {
  projection_type_ = value;
}
void s21::ViewParameters::SetLineWidth(float value) { line_width_ = value; }
void s21::ViewParameters::SetLineType(int index) { line_style_ = index; }
void s21::ViewParameters::SetPointSize(float value) { point_size_ = value; }
void s21::ViewParameters::SetPointType(int value) { point_style_ = value; }
void s21::ViewParameters::SetBgColor(QColor color) {
  bg_color_[0] = color.redF();
  bg_color_[1] = color.greenF();
  bg_color_[2] = color.blueF();
  bg_color_[3] = color.alphaF();
}
void s21::ViewParameters::SetLineColor(QColor color) {
  line_color_[0] = color.redF();
  line_color_[1] = color.greenF();
  line_color_[2] = color.blueF();
  line_color_[3] = color.alphaF();
}
void s21::ViewParameters::SetPointColor(QColor color) {
  point_color_[0] = color.redF();
  point_color_[1] = color.greenF();
  point_color_[2] = color.blueF();
  point_color_[3] = color.alphaF();
}
int s21::ViewParameters::GetProjectionType() { return projection_type_; }
float s21::ViewParameters::GetLineWidth() { return line_width_; }
int s21::ViewParameters::GetLineType() { return line_style_; }
float s21::ViewParameters::GetPointSize() { return point_size_; }
int s21::ViewParameters::GetPointType() { return point_style_; }
std::array<float, 4> s21::ViewParameters::GetBgColor() { return bg_color_; }
std::array<float, 4> s21::ViewParameters::GetLineColor() { return line_color_; }
std::array<float, 4> s21::ViewParameters::GetPointColor() {
  return point_color_;
}

QColor s21::ViewParameters::GetBgQColor() {
  QColor color;
  color.setRgbF(bg_color_[0], bg_color_[1], bg_color_[2], bg_color_[3]);
  return color;
}
QColor s21::ViewParameters::GetLineQColor() {
  QColor color;
  color.setRgbF(line_color_[0], line_color_[1], line_color_[2], line_color_[3]);
  return color;
}
QColor s21::ViewParameters::GetPointQColor() {
  QColor color;
  color.setRgbF(point_color_[0], point_color_[1], point_color_[2],
                point_color_[3]);
  return color;
}

float s21::ViewParameters::GetTranslationSliderPosition(char axis) {
  switch (axis) {
    case 'x':
      return translation_sliders_position_[0];
    case 'y':
      return translation_sliders_position_[1];
    case 'z':
      return translation_sliders_position_[2];
    default:
      break;
  }
  return 0;
}
void s21::ViewParameters::SetTranslationSliderPosition(float value, char axis) {
  switch (axis) {
    case 'x':
      translation_sliders_position_[0] = value;
      break;
    case 'y':
      translation_sliders_position_[1] = value;
      break;
    case 'z':
      translation_sliders_position_[2] = value;
      break;
    default:
      break;
  }
}

void s21::ViewParameters::SetTranslationSliderPosition(float value) {
  translation_sliders_position_.fill({value});
}

float s21::ViewParameters::GetRotationSliderPosition(char axis) {
  switch (axis) {
    case 'x':
      return rotation_sliders_position_[0];
    case 'y':
      return rotation_sliders_position_[1];
    case 'z':
      return rotation_sliders_position_[2];
    default:
      break;
  }
  return 0;
}
void s21::ViewParameters::SetRotationSliderPosition(float value, char axis) {
  switch (axis) {
    case 'x':
      rotation_sliders_position_[0] = value;
      break;
    case 'y':
      rotation_sliders_position_[1] = value;
      break;
    case 'z':
      rotation_sliders_position_[2] = value;
      break;
    default:
      break;
  }
}

void s21::ViewParameters::SetRotationSliderPosition(float value) {
  rotation_sliders_position_.fill({value});
}

float s21::ViewParameters::GetScaleSliderValue() { return scale_slider_value_; }
void s21::ViewParameters::SetScaleSliderValue(float value) {
  scale_slider_value_ = value;
}

int s21::ViewParameters::GetWindowWidth() { return window_width_; }
int s21::ViewParameters::GetWindowHeight() { return window_height_; }
void s21::ViewParameters::SetWindowWidth(int value) { window_width_ = value; }
void s21::ViewParameters::SetWindowHeight(int value) { window_height_ = value; }