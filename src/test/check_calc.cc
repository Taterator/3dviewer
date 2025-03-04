#include <gtest/gtest.h>
#include <stdlib.h>

#include <QString>
#include <QVector3D>
#include <vector>

#include "../3DViewerBack/object3d.h"

#define tol 1e-7

TEST(fill_struct, Subtest_1) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  ASSERT_TRUE(object->GetVerticesCount() == 8);
  ASSERT_TRUE(object->GetEdgesCount() == 36);
  ASSERT_TRUE(object->GetPolygonCount() == 12);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  delete object;
}

TEST(fill_struct, Subtest_2) {
  QString str = "../src/test/materials/example";
  s21::Object3D *object = new s21::Object3D(str);
  ASSERT_TRUE(object->GetVerticesCount() == 3);
  ASSERT_TRUE(object->GetEdgesCount() == 3);
  ASSERT_TRUE(object->GetPolygonCount() == 1);
  auto vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {0.0, 0.0, 0.0, 0.5, 0.5,
                                           0.0, 0.0, 0.5, 0.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  auto edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {1, 2, 2, 3, 3, 1};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  delete object;
}

TEST(rotate, Subtest_1) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Rotate(90, 'x');
  std::vector<float> vert_data_new = {0, 0, 0, 0, -1, 0, 0, 0, 1, 0, -1, 1,
                                      1, 0, 0, 1, -1, 0, 1, 0, 1, 1, -1, 1};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}

TEST(rotate, Subtest_2) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Rotate(90, 'y');
  std::vector<float> vert_data_new = {0, 0, 0,  1, 0, 0,  0, 1, 0,  1, 1, 0,
                                      0, 0, -1, 1, 0, -1, 0, 1, -1, 1, 1, -1};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}

TEST(rotate, Subtest_3) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Rotate(90, 'z');
  std::vector<float> vert_data_new = {0, 0, 0, 0, 0, 1, -1, 0, 0, -1, 0, 1,
                                      0, 1, 0, 0, 1, 1, -1, 1, 0, -1, 1, 1};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}

TEST(translate, Subtest_1) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Translate(1, 'x');
  std::vector<float> vert_data_new = {1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0,
                                      0.0, 1.0, 1.0, 1.0, 2.0, 0.0, 0.0, 2.0,
                                      0.0, 1.0, 2.0, 1.0, 0.0, 2.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}

TEST(translate, Subtest_2) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Translate(1, 'y');
  std::vector<float> vert_data_new = {0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 2.0,
                                      0.0, 0.0, 2.0, 1.0, 1.0, 1.0, 0.0, 1.0,
                                      1.0, 1.0, 1.0, 2.0, 0.0, 1.0, 2.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}

TEST(translate, Subtest_3) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Translate(1, 'z');
  std::vector<float> vert_data_new = {0.0, 0.0, 1.0, 0.0, 0.0, 2.0, 0.0, 1.0,
                                      1.0, 0.0, 1.0, 2.0, 1.0, 0.0, 1.0, 1.0,
                                      0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}

TEST(scale, Subtest_1) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Scale(2);
  std::vector<float> vert_data_new = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                      0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                      0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}

TEST(scale, Subtest_2) {
  QString str = "../src/test/materials/cube.obj";
  s21::Object3D *object = new s21::Object3D(str);
  float *vert_data = object->GetVertices();
  std::vector<float> vert_data_original = {
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,
      1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_EQ(vert_data[i + 3], vert_data_original[i]);
  }
  int *edges_data = object->GetEdges();
  std::vector<int> edges_data_original = {
      1, 7, 7, 5, 5, 1, 1, 3, 3, 7, 7, 1, 1, 4, 4, 3, 3, 1, 1, 2, 2, 4, 4, 1,
      3, 8, 8, 7, 7, 3, 3, 4, 4, 8, 8, 3, 5, 7, 7, 8, 8, 5, 5, 8, 8, 6, 6, 5,
      1, 5, 5, 6, 6, 1, 1, 6, 6, 2, 2, 1, 2, 6, 6, 8, 8, 2, 2, 8, 8, 4, 4, 2};
  for (int i = 0; i < edges_data_original.size(); ++i) {
    ASSERT_EQ(edges_data[i], edges_data_original[i]);
  }
  object->Scale(0.5);
  std::vector<float> vert_data_new = {0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5,
                                      0.0, 0.0, 0.5, 0.5, 0.5, 0.0, 0.0, 0.5,
                                      0.0, 0.5, 0.5, 0.5, 0.0, 0.5, 0.5, 0.5};
  for (int i = 0; i < vert_data_original.size(); ++i) {
    ASSERT_NEAR(vert_data[i + 3], vert_data_new[i], tol);
  }
  delete object;
}