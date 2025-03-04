/*!
    @file
    @brief Заголовочный файл с GL виджетом
*/

#ifndef SRC_CONTROLLER_S21_OPENGL_H_
#define SRC_CONTROLLER_S21_OPENGL_H_

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWidget>

namespace s21 {
enum class Projection;
class controller;
class ProjectionStrategy;

/*!
    @class OpenGLWidget
    @brief Класс OpenGLWidget, отвечающий за отрисовку фигуры в окне программы
*/
class OpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  explicit OpenGLWidget(QWidget* parent = nullptr);
  void SetController(s21::controller* controller);
  void UpdateStrategy();
  ~OpenGLWidget();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;

 private:
  s21::controller* controller_ = nullptr;
  s21::ProjectionStrategy* strategy_ = nullptr;
  QPoint lastPos;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_S21_OPENGL_H_
