#include "template.h"

namespace s21 {

// Lines
void GLLines::Draw() {
  SetColor();
  SetStyle();
  SetSize();
  auto edges = controller_->ModelGetEdges();
  auto edges_count = controller_->ModelGetEdgesCount() * 2;
  glDrawElements(GL_LINES, edges_count, GL_UNSIGNED_INT, edges);
}

void GLLines::SetColor() {
  std::array<float, 4> line = controller_->GetLineColor();
  glColor4f(line[0], line[1], line[2], line[3]);
}

void GLLines::SetStyle() {
  glEnable(GL_LINE_STIPPLE);
  switch (controller_->GetLineType()) {
    case 1:
      glLineStipple(1, 0xF0F0);
      break;
    default:
      glDisable(GL_LINE_STIPPLE);
      break;
  }
}

void GLLines::SetSize() {
  glEnable(GL_LINE_WIDTH);
  glLineWidth(controller_->GetLineSize());
}

// Points
void GLPoints::Draw() {
  switch (controller_->GetPointType()) {
    case 0:
      break;
    default:
      SetColor();
      SetStyle();
      SetSize();
      auto vertices_count = controller_->ModelGetVerticesCount();
      glDrawArrays(GL_POINTS, 1, vertices_count);
      break;
  }
}

void GLPoints::SetColor() {
  std::array<float, 4> point = controller_->GetPointColor();
  glColor4f(point[0], point[1], point[2], point[3]);
}

void GLPoints::SetStyle() {
  switch (controller_->GetPointType()) {
    case 1:
      glEnable(GL_POINT_SMOOTH);
      break;
    case 2:
      glDisable(GL_POINT_SMOOTH);
      break;
    default:
      glPointSize(1);
      glDisable(GL_POINT_SMOOTH);
      break;
  }
}

void GLPoints::SetSize() { glPointSize(controller_->GetPointSize()); }

// Points
void GLBackground::Draw() {
  SetColor();
  glClear(GL_COLOR_BUFFER_BIT);
}

void GLBackground::SetColor() {
  std::array<float, 4> bg = controller_->GetBgColor();
  glClearColor(bg[0], bg[1], bg[2], bg[3]);
}

}  // namespace s21