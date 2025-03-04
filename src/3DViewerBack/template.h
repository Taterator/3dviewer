/*!
    @file
    @brief Заголовочный файл с классом, отвечающим за отрисовку различных
   элементов
*/

#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "controller.h"
#include "openglwidget.h"

namespace s21 {
/*!
  @class GLObject
  @brief Класс GLObject,
  отвечающий за отрисовку элементов в OpenGLWidget
*/
class GLObject {
 public:
  virtual ~GLObject() = default;
  virtual void Draw() = 0;

  explicit GLObject(s21::controller* controller) : controller_(controller) {};

 protected:
  s21::controller* controller_;

  virtual void SetColor() = 0;
};

class GLLines : public GLObject {
 public:
  explicit GLLines(s21::controller* controller) : GLObject(controller) {}

  void Draw() override;

 private:
  void SetColor() override;
  void SetStyle();
  void SetSize();
};

class GLPoints : public GLObject {
 public:
  explicit GLPoints(s21::controller* controller) : GLObject(controller) {}

  void Draw() override;

 private:
  void SetColor() override;
  void SetStyle();
  void SetSize();
};

class GLBackground : public GLObject {
 public:
  explicit GLBackground(s21::controller* controller) : GLObject(controller) {}

  void Draw() override;

 private:
  void SetColor() override;
};

}  // namespace s21

#endif  // TEMPLATE_H_
