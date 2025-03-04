/*!
    @file
    @brief Заголовочный файл с классом, отвечающим за хранение и взаимодействие
   с параметрами отображения моделей
*/

#ifndef VIEW_PARAMETERS_H
#define VIEW_PARAMETERS_H

#include <QColor>
#include <array>

namespace s21 {
/*!
  @class ViewParameters
  @brief Класс ViewParameters, отвечающий за хранение и взаимодействие
   с параметрами отображения моделей
*/
class ViewParameters {
 public:
  ViewParameters() {}
  ~ViewParameters() {}

 public:
  void SetProjectionType(int value);
  void SetLineWidth(float value);
  void SetLineType(int index);
  void SetPointSize(float value);
  void SetPointType(int value);
  void SetBgColor(QColor color);
  void SetLineColor(QColor color);
  void SetPointColor(QColor color);
  int GetProjectionType();
  float GetLineWidth();
  int GetLineType();
  float GetPointSize();
  int GetPointType();
  std::array<float, 4> GetBgColor();
  std::array<float, 4> GetLineColor();
  std::array<float, 4> GetPointColor();
  QColor GetBgQColor();
  QColor GetLineQColor();
  QColor GetPointQColor();

  float GetTranslationSliderPosition(char axis);
  void SetTranslationSliderPosition(float value, char axis);
  void SetTranslationSliderPosition(float value);

  float GetRotationSliderPosition(char axis);
  void SetRotationSliderPosition(float value, char axis);
  void SetRotationSliderPosition(float value);

  float GetScaleSliderValue();
  void SetScaleSliderValue(float value);

  int GetWindowWidth();
  int GetWindowHeight();
  void SetWindowWidth(int value);
  void SetWindowHeight(int value);

 private:
  float line_width_ = 1;
  int line_style_ = 0;
  float point_size_ = 1;
  int point_style_ = 0;
  int projection_type_ = 0;
  std::array<float, 4> bg_color_ = {0, 0, 0, 1};
  std::array<float, 4> line_color_ = {1, 1, 1, 1};
  std::array<float, 4> point_color_ = {0, 1, 0, 1};

  std::array<float, 3> translation_sliders_position_{0, 0, 0};
  std::array<float, 3> rotation_sliders_position_{0, 0, 0};
  float scale_slider_value_ = 200;

  int window_width_ = 100;
  int window_height_ = 100;
};

}  // namespace s21
#endif
