#include "strategy.h"

namespace s21 {

// Применяет настройки линий и фона
void ProjectionStrategy::DrawElements() {
  auto vertices = controller_->ModelGetVertices();
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  background_->Draw();
  lines_->Draw();
  points_->Draw();
}

// Применяет настройки проекции
void OrthographicProjection::DrawAll() {
  glLoadIdentity();
  qreal aspectratio = qreal(controller_->GetWindowWidth()) /
                      qreal(controller_->GetWindowHeight());
  glOrtho(-aspectratio, aspectratio, -1.0, 1.0, 1.0, 4000.0);
  DrawElements();
}

// Применяет настройки проекции
void PerspectiveProjection::DrawAll() {
  glLoadIdentity();
  qreal aspectratio = qreal(controller_->GetWindowWidth()) /
                      qreal(controller_->GetWindowHeight());
  glFrustum(-aspectratio, aspectratio, -1.0, 1.0, 1.0, 4000.0);
  DrawElements();
}

}  // namespace s21
