#pragma once

#include <QGLWidget>
#include <QKeyEvent>
#include <QMainWindow>
#include <QtOpenGL>
#include <cmath>
#include <vector>
#include "vector.h"
using namespace std;
#include "objects.h"

class arcBall;

class GLWidget : public QGLWidget {
  Q_OBJECT

public:
  GLWidget(QWidget *parent = 0);
  Objects *objects;

  void loadTextures();
  void setOrtho();
  void initializeGL();
  void paintGL();
  void resizeGL(int w, int h);
  void keyPressEvent(QKeyEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void drawAxes();
  void drawGrid(GLfloat *colour, int nGridlines);
  void drawHuman();
  void animate(int time);
  virtual ~GLWidget();
public slots:
  void resetArc();
  void resetPos();
  void resetZoom();

protected:
  arcBall *arc;
  bool resetArcBall;
  bool axes;
  bool grid;
  bool wframe;
  bool animation;

  // Animation parameters
  int time;
  int nframes;

  // model position
  float posn_x = 2, posn_z =0, posn_y = 1.5, bodyThetaX = 0,bodyThetaY = 0,bodyThetaZ = 0;
  Vector left_arm = Vector(0.5,0.4,0), left_arm_rotation = Vector(90,45,0);
  Vector left_forearm = Vector(0.0f, 0.0f, 0.6f), left_forearm_rotation = Vector(0,0,0);
  Vector right_arm = Vector(-0.5,0.4,0), right_arm_rotation = Vector(45,-45,0);
  Vector right_forearm = Vector(0.0f, 0.0f, 0.6f), right_forearm_rotation = Vector(270,0,0);
  float left_leg_rotation = 45, right_leg_rotation = 135;
  float left_lowerleg_rotation = 0, right_lowerleg_rotation = 0;


  GLuint textures[10];

  int nGridlines;

  // the viewing area dimensions
  int viewWidth;
  int viewHeight;

  // the zoom factor
  float zoomFactor = 5.f;

  float ortho = 5.0f;
  float orthoNear = -100.0f;
  float orthoFar = 100.0f;

  bool drag;
  bool pull;
  float pullX = 0.0;
  float pullY = 0.0;
  float moveX = 0.0;
  float moveY = 0.0;

public slots:
  void idle();
  void saveImage();
};
