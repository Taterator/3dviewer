/*!
    @file
    @brief Заголовочный файл с классом, отвечающим за хранение настроек
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#include "view_parameters.h"

namespace s21 {
/*!
  @class Settings
  @brief Класс Settings, отвечающий за сохранение параметров отображения
  (настроек)
*/
class Settings : public QObject {
 public:
  Settings(){};
  Settings(ViewParameters *parameters = nullptr);
  ~Settings() { delete settings_; };

  void SetParameters(s21::ViewParameters *parameters);

  void SettingsRead();
  void SettingsWrite();

 private:
  ViewParameters *parameters_;
  QSettings *settings_ = nullptr;
};

}  // namespace s21

#endif