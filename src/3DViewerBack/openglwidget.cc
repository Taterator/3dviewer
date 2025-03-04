#include "openglwidget.h"

#include "../3DViewerControl/controller.h"
#include "strategy.h"

// Конструктор принимает родительский виджет
s21::OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

void s21::OpenGLWidget::SetController(s21::controller* controller) {
  controller_ = controller;
};

void s21::OpenGLWidget::UpdateStrategy() {
  switch (controller_->GetProjectionType()) {
    case 0:
      delete strategy_;
      strategy_ = new s21::OrthographicProjection(controller_);
      break;
    case 1:
      delete strategy_;
      strategy_ = new s21::PerspectiveProjection(controller_);
      break;
  }
};

// Деструктор
s21::OpenGLWidget::~OpenGLWidget() { delete strategy_; }

// выполняет начальную настройку OpenGL
void s21::OpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glEnableClientState(GL_VERTEX_ARRAY);
  glMatrixMode(GL_PROJECTION);
}

// Устанавливает область просмотра окна рендеринга
void s21::OpenGLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  controller_->SetWindowWidth(width);
  controller_->SetWindowHeight(height);
}

// рисование
void s21::OpenGLWidget::paintGL() { strategy_->DrawAll(); }
