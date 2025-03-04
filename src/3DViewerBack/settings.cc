#include "settings.h"

s21::Settings::Settings(ViewParameters *parameters) {
  SetParameters(parameters);
  settings_ = new QSettings("Settings.ini", QSettings::IniFormat, this);
}

void s21::Settings::SetParameters(s21::ViewParameters *parameters) {
  parameters_ = parameters;
}

void s21::Settings::SettingsRead() {
  QColor color;
  settings_->beginGroup("ProjectionType");
  parameters_->SetProjectionType(settings_->value("Central", 0).toInt());
  settings_->endGroup();
  settings_->beginGroup("LineSettings");
  settings_->beginGroup("LineType");
  parameters_->SetLineType(settings_->value("StippleLine", 0).toInt());
  settings_->endGroup();
  settings_->beginGroup("LineSize");
  parameters_->SetLineWidth(settings_->value("LineSize", 1).toFloat());
  settings_->endGroup();
  settings_->beginGroup("LineColor");
  color.setRgbF(settings_->value("LineColorRed", 1).toFloat(),
                settings_->value("LineColorGreen", 1).toFloat(),
                settings_->value("LineColorBlue", 1).toFloat(),
                settings_->value("LineColorAlpha", 1).toFloat());
  parameters_->SetLineColor(color);
  settings_->endGroup();
  settings_->endGroup();
  settings_->beginGroup("VertexSettings");
  settings_->beginGroup("VertexType");
  parameters_->SetPointType(settings_->value("Type", 0).toInt());
  settings_->endGroup();
  settings_->beginGroup("VertexSize");
  parameters_->SetPointSize(settings_->value("VertexSize", 1).toFloat());
  settings_->endGroup();
  settings_->beginGroup("VertexColor");
  color.setRgbF(settings_->value("VertexColorRed", 0).toFloat(),
                settings_->value("VertexColorGreen", 1).toFloat(),
                settings_->value("VertexColorBlue", 0).toFloat(),
                settings_->value("VertexColorAlpha", 1).toFloat());
  parameters_->SetPointColor(color);
  settings_->endGroup();
  settings_->endGroup();
  settings_->beginGroup("BackgroundColor");
  color.setRgbF(settings_->value("BackgroundColorRed", 0).toFloat(),
                settings_->value("BackgroundColorGreen", 0).toFloat(),
                settings_->value("BackgroundColorBlue", 0).toFloat(),
                settings_->value("BackgroundColorAlpha", 1).toFloat());
  parameters_->SetBgColor(color);
  settings_->endGroup();
}

void s21::Settings::SettingsWrite() {
  std::array<float, 4> color;
  settings_->beginGroup("ProjectionType");
  settings_->setValue("Central", parameters_->GetProjectionType());
  settings_->endGroup();
  settings_->beginGroup("LineSettings");
  settings_->beginGroup("LineType");
  settings_->setValue("StippleLine", parameters_->GetLineType());
  settings_->endGroup();
  settings_->beginGroup("LineSize");
  settings_->setValue("LineSize", parameters_->GetLineWidth());
  settings_->endGroup();
  settings_->beginGroup("LineColor");
  color = parameters_->GetLineColor();
  settings_->setValue("LineColorRed", color[0]);
  settings_->setValue("LineColorGreen", color[1]);
  settings_->setValue("LineColorBlue", color[2]);
  settings_->setValue("LineColorAlpha", color[3]);
  settings_->endGroup();
  settings_->endGroup();
  settings_->beginGroup("VertexSettings");
  settings_->beginGroup("VertexType");
  settings_->setValue("Type", parameters_->GetPointType());
  settings_->endGroup();
  settings_->beginGroup("VertexSize");
  settings_->setValue("VertexSize", parameters_->GetPointSize());
  settings_->endGroup();
  settings_->beginGroup("VertexColor");
  color = parameters_->GetPointColor();
  settings_->setValue("VertexColorRed", color[0]);
  settings_->setValue("VertexColorGreen", color[1]);
  settings_->setValue("VertexColorBlue", color[2]);
  settings_->setValue("VertexColorAlpha", color[3]);
  settings_->endGroup();
  settings_->endGroup();
  settings_->beginGroup("BackgroundColor");
  color = parameters_->GetBgColor();
  settings_->setValue("BackgroundColorRed", color[0]);
  settings_->setValue("BackgroundColorGreen", color[1]);
  settings_->setValue("BackgroundColorBlue", color[2]);
  settings_->setValue("BackgroundColorAlpha", color[3]);
  settings_->endGroup();
  settings_->sync();
}