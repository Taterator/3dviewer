/*!
    @file
    @brief Заголовочный файл с классом контроллера
*/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../3DViewerBack/object3d.h"
#include "../3DViewerBack/openglwidget.h"
#include "../3DViewerBack/recording.h"
#include "../3DViewerBack/settings.h"
#include "../3DViewerBack/view_parameters.h"

namespace s21 {
class OpenGLWidget;
class Recorder;
/*!
  @class controller
  @brief Класс controller, являющийся интерфейсом взаимодействия view и model
*/
class controller : public QObject {
 public:
  controller();
  ~controller();

  // Model access
  void ModelInitializer(QString str);
  void ModelDestructor();

  bool ModelIsNull();

  float *ModelGetVertices();
  int ModelGetVerticesCount();

  int *ModelGetEdges();
  int ModelGetEdgesCount();

  int ModelGetPolygonCount();

  void ModelScale(float scale);
  void ModelTranslate(float dx, float dy, float dz);
  void ModelTranslate(float value, char axis);
  void ModelRotate(float value, char axis);
  void ModelRotateDelta(float value, char axis);

  std::array<float, 3> ModelGetPosition();
  float ModelGetPosition(char axis);
  std::array<float, 3> ModelGetRotation();
  float ModelGetRotation(char axis);
  void ModelSetRotation(std::array<float, 3> rotation);
  float ModelGetScale();

  // OpenGL access
  OpenGLWidget *WidgetGet();
  QImage getFramebuffer();

  // Settings writing/reading
  void SettingsRead();
  void SettingsWrite();

  // Parameters access
  std::array<float, 4> GetPointColor();
  std::array<float, 4> GetLineColor();
  std::array<float, 4> GetBgColor();
  QColor GetBgQColor();
  QColor GetLineQColor();
  QColor GetPointQColor();
  int GetProjectionType();
  int GetPointType();
  int GetLineType();
  float GetPointSize();
  float GetLineSize();

  float GetRotationSliderPosition(char axis);
  void SetRotationSliderPosition(float val, char axis);

  int GetWindowWidth();
  int GetWindowHeight();
  void SetWindowWidth(int value);
  void SetWindowHeight(int value);

  void MakeGif(QWidget *window);
  void MakeScreenshot(QWidget *window, int type);

 public slots:
  void slot(QString);
  void slotScale(float scale, char type);
  void slotTranslate(float value, char axis, float mult, char type);
  void slotRotate(float value, char axis);
  void slotRotateDelta(float value, char axis);
  void slotProjectionTypeChange(int);
  void slotLineTypeChange(bool);
  void slotLineSizeChange(double);
  void slotPointSizeChange(double);
  void slotPointTypeChange(int);
  void slotPointColorChange(QColor);
  void slotLineColorChange(QColor);
  void slotWidgetColorChange(QColor);

 private:
  Object3D *object_ = nullptr;
  OpenGLWidget *openGLWidget_ = nullptr;
  ViewParameters *parameters_ = nullptr;
  Settings *settings_ = nullptr;
  Recorder *recorder_ = nullptr;
  // QPoint lastPos;
};

}  // namespace s21

#endif