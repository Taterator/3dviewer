#include "recording.h"

#include <QCoreApplication>
#include <QFileDialog>
#include <QThread>

void s21::Recorder::MakeScreenshot(QWidget *window, int type) {
  QImage img = controller_->getFramebuffer();
  char str[16] = "";
  QString default_name = "/noname";
  if (type == 1) {
    strcat(str, "Images (*.bmp)");
    default_name.append(".bmp");
  } else {
    strcat(str, "Images (*.jpeg)");
    default_name.append(".jpeg");
  }
  QString fileName = QFileDialog::getSaveFileName(
      window, tr("Save File"), QDir::currentPath().append(default_name),
      tr((const char *)str));
  if (!fileName.isNull()) {
    img.save(fileName);
  }
}

void s21::Recorder::MakeGif(QWidget *window) {
  miliseconds_ = 0;
  frame_ = new QImage();
  gif_ = new QGifImage();
  QString default_name = "/noname.gif";
  QString file_name = QFileDialog::getSaveFileName(
      window, tr("Save GIF"), QDir::currentPath().append(default_name),
      tr("Gif (*.gif)"));
  if (!file_name.isNull()) {
    for (int i = 0; i < 50; ++i) {
      ConstructGif(file_name);
      QCoreApplication::processEvents();
      QThread::msleep(100);
    }
  }
};

void s21::Recorder::ConstructGif(QString file_name) {
  *frame_ = controller_->getFramebuffer();
  double rotate_speed = 360 / (10 * 5);
  controller_->slotRotateDelta(rotate_speed, 'y');
  *frame_ = frame_->scaled(640, 480);
  gif_->addFrame(*frame_, 100);
  miliseconds_ += 100;
  if (miliseconds_ >= 5000) {
    gif_->save(file_name);
  }
};