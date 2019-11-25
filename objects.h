#pragma once

#include <QGLWidget>
#include <QObject>

class Objects : public QObject {
public:
  Objects(QGLWidget *parent = nullptr);
  // routines for drawing geometric primitives :  platonic solids
  void drawTetrahedron();
  void drawCube();
  void drawOctahedron();
  void drawCone(float radius, float height, int nSlices);
  void drawSphere(float radius, int nSegments, int nSlices);
  void drawCylinder(float radius, float height, int nSegments);
  void drawQuad();

private:
  QGLWidget *qGLWidget;
};
