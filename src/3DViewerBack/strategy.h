/*!
    @file
    @brief Заголовочный файл с классом, отвечающим за изменение проекции
*/

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "controller.h"
#include "openglwidget.h"
#include "template.h"

namespace s21 {
/*!
  @class ProjectionStrategy
  @brief Класс ProjectionStrategy,
  отвечает за изменение проекции
*/
class ProjectionStrategy {
 public:
  virtual ~ProjectionStrategy() = default;
  virtual void DrawAll() = 0;

 protected:
  s21::controller* controller_;
  s21::GLObject* lines_;
  s21::GLObject* points_;
  s21::GLObject* background_;

  explicit ProjectionStrategy(s21::controller* controller)
      : controller_(controller),
        lines_(new s21::GLLines(controller)),
        points_(new s21::GLPoints(controller)),
        background_(new s21::GLBackground(controller)) {}

  void DrawElements();
};

class OrthographicProjection : public ProjectionStrategy {
 public:
  explicit OrthographicProjection(s21::controller* controller)
      : ProjectionStrategy(controller) {}

  void DrawAll() override;
};

class PerspectiveProjection : public ProjectionStrategy {
 public:
  explicit PerspectiveProjection(s21::controller* controller)
      : ProjectionStrategy(controller) {}

  void DrawAll() override;
};

}  // namespace s21

#endif  // STRATEGY_H_
