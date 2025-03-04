#include "object3d.h"

#include <QTextStream>
#include <thread>

s21::Object3D::Object3D(const QString &file_name) {
  ReadObjectFromFile(file_name);
}

void s21::Object3D::ReadObjectFromFile(const QString &file_name) {
  QFile f_object(file_name);
  if (f_object.open(QIODevice::ReadOnly)) {
    QByteArray b_object = f_object.readAll();
    QString s_object = QString(b_object);
    QStringList sl_object = s_object.split("\n");
    sl_object.removeAll(QString(""));
    vertices_.push_back(QVector3D(0.0, 0.0, 0.0));
    CountData(sl_object);
    vertices_.reserve(c_of_v_ + 1);
    edges_.reserve(c_of_f_ * 3);
    auto it_1 = sl_object.begin();
    auto it_2 = sl_object.begin();
    std::thread t_1([&] {
      for (; it_1 != sl_object.end(); it_1++) {
        if (it_1[0][0] == 'v') {
          StringTo3DPoint(it_1[0]);
        }
      }
    });
    std::thread t_2([&] {
      for (; it_2 != sl_object.end(); it_2++) {
        if (it_2[0][0] == 'f' && it_2[0][1] == ' ') {
          FillPolygon(it_2[0]);
        } else if (it_2[0] == "g" || (it_2[0][0] == 'g' && it_2[0][1] == ' ')) {
          ++current_group_;
        }
      }
    });
    t_1.join();
    t_2.join();
  }
  vertices_count_ = vertices_.size();
  edges_count_ = edges_.size();
}

void s21::Object3D::CountData(const QStringList &data) {
  auto it = data.begin();
  for (; it != data.end(); it++) {
    if (it[0][0] == 'v' && it[0][1] == ' ') {
      ++vertices_in_groups_[c_of_g_];
      ++c_of_v_;
    } else if (it[0][0] == 'f' && it[0][1] == ' ') {
      ++c_of_f_;
    } else if (it[0] == "g" || (it[0][0] == 'g' && it[0][1] == ' ')) {
      ++c_of_g_;
      vertices_in_groups_.append(0);
    }
  }
}

void s21::Object3D::StringTo3DPoint(const QString &str) {
  QStringList sl_point = str.split(" ");
  sl_point.removeAll("");
  auto it = sl_point.begin();
  switch (str[1].unicode()) {
    case ' ':
      vertices_.emplace_back(it[1].toFloat(), it[2].toFloat(), it[3].toFloat());
      break;
    case 'n':
      normals_.emplace_back(it[1].toFloat(), it[2].toFloat(), it[3].toFloat());
      break;
    case 't':
      textures_.emplace_back(it[1].toFloat(), it[2].toFloat());
      break;
    default:
      break;
  }
}

void s21::Object3D::FillPolygon(const QString &str) {
  QStringList sl_poligon = str.split(" ");
  auto it_p = sl_poligon.begin();
  it_p++;
  int first = 0, second = 0;
  int first_vertice = 0;
  for (; it_p != sl_poligon.end(); it_p++) {
    int vert_num = (it_p[0].split("/").begin())[0].toInt();
    if (vert_num) {
      if (vert_num < 0) {
        for (int j = 0; j < current_group_ + 1; j++)
          vert_num += vertices_in_groups_[j];
        vert_num++;
      }
      switch (first) {
        case 0:
          first = vert_num;
          first_vertice = first;
          break;
        default:
          second = vert_num;
          edges_.push_back(qMakePair(first, second));
          first = second;
          break;
      }
    }
  }
  edges_.push_back(qMakePair(second, first_vertice));
}

float *s21::Object3D::GetVertices() { return &vertices_[0][0]; }
int *s21::Object3D::GetEdges() { return &(edges_[0].first); }
int s21::Object3D::GetEdgesCount() { return edges_count_; }
int s21::Object3D::GetVerticesCount() { return c_of_v_; }

std::array<float, 3> s21::Object3D::GetPosition() { return position_; }
std::array<float, 3> s21::Object3D::GetRotation() { return rotation_; }
void s21::Object3D::SetRotation(const std::array<float, 3> &rotation) {
  rotation_ = rotation;
}

float s21::Object3D::GetScale() { return scale_; }

void s21::Object3D::ScaleThread(float scale, int total_thread_number,
                                int current_thread_index) {
  for (int i = current_thread_index + 1; i < vertices_count_;
       i += total_thread_number) {
    vertices_[i] *= scale;
  }
}

void s21::Object3D::Scale(float scale) {
  for (int i = 1; i < vertices_count_; i++) {
    for (int j = 0; j < 3; ++j)
      vertices_[i][j] = (vertices_[i][j] - position_[j]) * scale + position_[j];
  }
  scale_ *= scale;
}

void s21::Object3D::Translate(float change, char axis) {
  switch (axis) {
    case 'x': {
      position_[0] += change;
      for (int i = 1; i < vertices_count_; i++) {
        vertices_[i][0] += change;
      }
      break;
    }
    case 'y': {
      position_[1] += change;
      for (int i = 1; i < vertices_count_; i++) {
        vertices_[i][1] += change;
      }
      break;
    }
    case 'z': {
      position_[2] += change;
      for (int i = 1; i < vertices_count_; i++) {
        vertices_[i][2] += change;
      }
      break;
    }
  }
}

void s21::Object3D::Translate(float dx, float dy, float dz) {
  position_[0] += dx;
  position_[1] += dy;
  position_[2] += dz;
  for (int i = 1; i < vertices_count_; i++) {
    vertices_[i][0] += dx;
    vertices_[i][1] += dy;
    vertices_[i][2] += dz;
  }
}

void s21::Object3D::Rotate(float value, char axis) {
  double angle = (double)value / 180 * M_PI;
  switch (axis) {
    case 'x': {
      rotation_[0] += value;
      float sin_x_tmp = sinf(angle);
      float cos_x_tmp = cosf(angle);
      float temp_y = 0;
      float temp_z = 0;
      for (int i = 1; i < vertices_count_; i++) {
        // вращение по оси x
        temp_y = vertices_[i][1] - position_[1];
        temp_z = vertices_[i][2] - position_[2];
        vertices_[i][1] =
            temp_y * cos_x_tmp - temp_z * sin_x_tmp + position_[1];
        vertices_[i][2] =
            temp_y * sin_x_tmp + temp_z * cos_x_tmp + position_[2];
      }
      break;
    }
    case 'y': {
      rotation_[1] += value;
      double sin_y_tmp = sin(angle);
      double cos_y_tmp = cos(angle);
      double temp_x = 0;
      double temp_z = 0;
      for (int i = 1; i < vertices_count_; i++) {
        // вращение по оси y
        temp_x = vertices_[i][0] - position_[0];
        temp_z = vertices_[i][2] - position_[2];
        vertices_[i][0] =
            temp_x * cos_y_tmp + temp_z * sin_y_tmp + position_[0];
        vertices_[i][2] =
            -temp_x * sin_y_tmp + temp_z * cos_y_tmp + position_[2];
      }
      break;
    }
    case 'z': {
      rotation_[2] += value;
      double sin_z_tmp = sin(angle);
      double cos_z_tmp = cos(angle);
      double temp_x = 0;
      double temp_y = 0;
      for (int i = 1; i < vertices_count_; i++) {
        // вращение по оси z
        temp_x = vertices_[i][0] - position_[0];
        temp_y = vertices_[i][1] - position_[1];
        vertices_[i][0] =
            temp_x * cos_z_tmp - temp_y * sin_z_tmp + position_[0];
        vertices_[i][1] =
            temp_x * sin_z_tmp + temp_y * cos_z_tmp + position_[1];
      }
      break;
    }
  }
}

void s21::Object3D::Rotate(float dx, float dy, float dz) {
  Rotate(dx, 'x');
  Rotate(dy, 'y');
  Rotate(dz, 'z');
}

void s21::Object3D::ScaleAndCenter() {
  float min_max_xyz[6] = {0};
  FindMinMax(&min_max_xyz[0]);
  float shift[3] = {0};
  for (int i = 0; i < 3; i++) {
    shift[i] = -1 * (min_max_xyz[i] + min_max_xyz[i + 3]) / 2;
  }
  Translate(shift[0], shift[1], shift[2]);
  for (int i = 0; i < 6; ++i) min_max_xyz[i] += shift[i % 3];
  float scale_val =
      (1 / std::max({min_max_xyz[3], min_max_xyz[4], min_max_xyz[5]})) * 0.5;
  position_ = {0};
  Scale(scale_val);
  scale_ = 1.0;
  Translate(-1 + std::max(min_max_xyz[5], min_max_xyz[3]) * scale_val * -1.5,
            'z');
}

void s21::Object3D::FindMinMax(float *min_max_xyz) {
  for (int i = 0; i < 6; i++) {
    min_max_xyz[i] = vertices_[1][i % 3];
  }
  for (int i = 1; i < vertices_count_; i++) {
    for (int j = 0; j < 3; j++) {
      if (vertices_[i][j] < min_max_xyz[j]) min_max_xyz[j] = vertices_[i][j];
      if (vertices_[i][j] > min_max_xyz[j + 3])
        min_max_xyz[j + 3] = vertices_[i][j];
    }
  }
}

int s21::Object3D::GetPolygonCount() { return c_of_f_; }