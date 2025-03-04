/*!
    @file
    @brief Заголовочный файл с классом, отвечающим за запись изображений
*/

#ifndef RECORDING_H
#define RECORDING_H

#include "../3DViewerControl/controller.h"
#include "gif/qtgifimage/src/gifimage/qgifimage.h"

namespace s21 {
class controller;

/*!
    @class Recorder
    @brief Класс Recorder, отвечающий за получение изображений из OpenGLWidget и
   их последующую запись
*/
class Recorder : public QObject {
 public:
  Recorder() = default;
  ~Recorder() = default;
  Recorder(controller *controller) : controller_(controller){};

  void MakeScreenshot(QWidget *window, int type);
  void MakeGif(QWidget *window);

 private:
  void ConstructGif(QString file_name);

  controller *controller_ = nullptr;

  QGifImage *gif_;
  QImage *frame_;
  int miliseconds_;
};
}  // namespace s21

#endif