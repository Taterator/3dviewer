/*!
    @file
    @brief Заголовочный файл с классами, содржащими 3д объект
*/

#ifndef OBJECT3D_H
#define OBJECT3D_H
#include <QByteArray>
#include <QFile>
#include <QPair>
#include <QString>
#include <QVector2D>
#include <QVector3D>

namespace s21 {

/*!
    @class Object3D
    @brief Класс, определяющий 3д объекты и способы взаимодействия с ними
*/
class Object3D {
 public:
  Object3D() = default;
  Object3D(const QString &file_name);
  ~Object3D() = default;

 public:
  /*!
   @brief Парсинг файла
   @param[in] file_name Название файла
 */
  void ReadObjectFromFile(const QString &file_name);

  /*!
  @brief Получение указателя на массив узлов
  @return Указатель на нулевой элемент массива узлов
*/
  float *GetVertices();
  /*!
  @brief Получение указателя на массив граней
  @return Указатель на нулевой элемент массива граней
*/
  int *GetEdges();
  /*!
  @brief Получение количества граней
  @return Возвращает количество граней модели
*/
  int GetEdgesCount();
  /*!
  @brief Получение количества узлов
  @return Возвращает количество узлов модели
*/
  int GetVerticesCount();
  /*!
  @brief Получение количества полигонов
  @return Возвращает количество полигонов модели
*/
  int GetPolygonCount();

  /*!
  @brief Получение текущего смещения модели
  @return Возвращает массив смещений модели в формате {x,y,z}
*/
  std::array<float, 3> GetPosition();
  /*!
  @brief Получение текущего поворота модели
  @return Возвращает массив поворотов модели в формате {x,y,z} в градусах
*/
  std::array<float, 3> GetRotation();
  /*!
  @brief Установить значения поворота
  @param[in] rotation Массив поворотов в формате {x,y,z} в градусах
*/
  void SetRotation(const std::array<float, 3> &rotation);

  /*!
  @brief Получить текущий масштаб
  @return Возвращает текущий масштаб модели
*/
  float GetScale();

  /*!
  @brief Масштабировать модель
  @param[in] scale Коэффициент масштабирования
*/
  void Scale(float scale);

  /*!
  @brief Переместить модель по конкретной оси
  @param[in] change Величина смещения
  @param[in] axis Ось
*/
  void Translate(float change, char axis);

  /*!
  @brief Переместить модель
  @param[in] dx,dy,dz Величины смещения по осям x,y,z соответственно
*/
  void Translate(float dx, float dy, float dz);

  /*!
  @brief Повернуть модель вокруг конкретной оси
  @param[in] value Величина поворота в градусах
  @param[in] axis Ось
*/
  void Rotate(float value, char axis);

  /*!
  @brief Повернуть модель
  @param[in] dx,dy,dz Величины поворота в градусах по осям x,y,z соответственно
*/
  void Rotate(float dx, float dy, float dz);

  /*!
  @brief Нормализовать значения координат модели и привести модель в центр
*/
  void ScaleAndCenter();

 private:
  void ScaleThread(float scale, int total_thread_number,
                   int current_thread_index);
  void CountData(const QStringList &data);

  void StringTo3DPoint(const QString &str);
  void FillPolygon(const QString &str);

  void FindMinMax(float *min_max_xyz);

  QVector<QVector3D> vertices_;
  QVector<QVector3D> normals_;
  QVector<QVector2D> textures_;
  QVector<QPair<int, int>> edges_;
  int edges_count_;
  int vertices_count_;
  int current_group_ = 0;
  QVector<int> vertices_in_groups_ = {0};
  int c_of_v_ = 0;
  int c_of_f_ = 0;
  int c_of_g_ = 0;

  std::array<float, 3> position_ = {0};
  std::array<float, 3> rotation_ = {0};

  float scale_ = 1.0;
};

}  // namespace s21
#endif  // OBJECT3D_H
