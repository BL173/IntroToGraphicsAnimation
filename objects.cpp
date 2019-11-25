#include "objects.h"
#include "point.h"
#include <cmath>

const float PI = 3.1415926f;

static GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat grey[] = {0.5, 0.5, 0.5, 1.0};

Objects::Objects(QGLWidget *parent) : QObject(parent) { qGLWidget = parent; }

/*
 * Implement all the subsequent functions routines for drawing geometric
 * primitives
 * platonic solids
 */

void Objects::drawTetrahedron() {
  Point vertices[4] = {
      Point(-1.0, -1.0, -1.0), // 0
      Point(-1.0, 1.0, 1.0), // 1
      Point(1.0, -1.0, 1.0),  // 2
      Point(1.0, 1.0, -1.0) // 3
  };

  // Define faces based on sets of vertices from the vertices array
  int faces[4][3] = {
      {0, 2, 1}, // face 0
      {1, 3, 0}, // face 1
      {2, 3, 1}, // face 2
      {3, 2, 0}  // face 3
  };

  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 4; i++) { // loop through the faces
    Vector v = vertices[faces[i][1]] - vertices[faces[i][0]];
    Vector w = vertices[faces[i][2]] - vertices[faces[i][0]];
    Vector normal = v.cross(w).normalised();
    glNormal3f(normal.dx, normal.dy, normal.dz);
    for (int j = 0; j < 3; j++){
        int vertexIndex = faces[i][j];
        glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);
    }
  }
  glEnd();
}

void Objects::drawCube() {

  Point vertices[8] = {
      Point(-1.0, -1.0, -1.0, 0.0), Point(-1.0, -1.0, 1.0, 0.0),
      Point(-1.0, 1.0, -1.0, 0.0),  Point(-1.0, 1.0, 1.0, 0.0),
      Point(1.0, -1.0, -1.0, 0.0),  Point(1.0, -1.0, 1.0, 0.0),
      Point(1.0, 1.0, -1.0, 0.0),   Point(1.0, 1.0, 1.0, 0.0)
  };

  int faces[6][4] = {{0, 4, 5, 1}, {0, 2, 6, 4}, {0, 1, 3, 2},
                     {4, 6, 7, 5}, {1, 5, 7, 3}, {2, 3, 7, 6}};

  glBegin(GL_QUADS);
  for (int i = 0; i < 6; i++) { // loop through the faces
    Vector v = vertices[faces[i][1]] - vertices[faces[i][0]];
    Vector w = vertices[faces[i][3]] - vertices[faces[i][0]];
    Vector normal = v.cross(w).normalised();
    // Same normal but different texture coordinate for each vertex
    glNormal3f(normal.dx, normal.dy, normal.dz);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(vertices[faces[i][0]].x, vertices[faces[i][0]].y, vertices[faces[i][0]].z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(vertices[faces[i][1]].x, vertices[faces[i][1]].y, vertices[faces[i][1]].z);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(vertices[faces[i][2]].x, vertices[faces[i][2]].y, vertices[faces[i][2]].z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(vertices[faces[i][3]].x, vertices[faces[i][3]].y, vertices[faces[i][3]].z);
  }
  glEnd();
}

void Objects::drawOctahedron() {

  Point vertices[6] = {Point(-1.0, 0.0, 0.0, 0.0), Point(0.0, -1.0, 0.0, 0.0),
                       Point(0.0, 0.0, -1.0, 0.0), Point(1.0, 0.0, 0.0, 0.0),
                       Point(0.0, 1.0, 0.0, 0.0),  Point(0.0, 0.0, 1.0, 0.0)};

  int faces[8][3] = {{3, 4, 5}, {4, 0, 5}, {0, 1, 5}, {1, 4, 5},
                     {0, 4, 2}, {4, 3, 2}, {3, 1, 2}, {1, 0, 2}};

  glBegin(GL_TRIANGLES);
  for (int i = 0; i < 8; i++) { // loop through the faces
    Vector v = vertices[faces[i][1]] - vertices[faces[i][0]];
    Vector w = vertices[faces[i][2]] - vertices[faces[i][0]];
    Vector normalised = v.cross(w).normalised();
    glNormal3f(normalised.dx, normalised.dy, normalised.dz);
    for (int j = 0; j < 3; j++){
        int vertexIndex = faces[i][j];
        glVertex3f(vertices[vertexIndex].x, vertices[vertexIndex].y, vertices[vertexIndex].z);
    }
  }
  glEnd();
}

void Objects::drawCone(float radius, float height, int nSlices) {
    glBegin(GL_TRIANGLES);
    for (float i = 0.0; i <= static_cast<float>(nSlices); i += 1.0f) {
        // a loop around circumference
        float angle = (PI * i * 2.0f) / static_cast<float>(nSlices);
        float nextAngle = (PI * (i+1) * 2.0f) / static_cast<float>(nSlices);
        float x1 = sin(angle) * radius, y1 = cos(angle) * radius;
        float x2 = sin(nextAngle) * radius, y2 = cos(nextAngle) * radius;

        // Side
        glNormal3f(x1, y1, 0);
        glVertex3f(x1, y1, -height / 2);
        glNormal3f(x2, y2, 0);
        glVertex3f(x2, y2, -height / 2);
        glNormal3f(x2, y2, 0);
        glVertex3f(0, 0, height / 2);

        // Bottom
        glNormal3f(0.0f, 0.0f, -1.0f); // point down
        glVertex3f(x1, y1, -height / 2);
        glVertex3f(x2, y2, -height / 2);
        glVertex3f(0, 0, -height / 2);
    }
    glEnd();

}

void Objects::drawCylinder(float radius, float height, int nSegments) {

    glBegin(GL_TRIANGLES);
    for (float i = 0.0; i <= nSegments; i += 1.0f) {
        // a loop around circumference
        float angle = (PI * i * 2.0f) / static_cast<float>(nSegments);
        float nextAngle = (PI * (i+1) * 2.0f) / static_cast<float>(nSegments);
        float x1 = sin(angle) * radius, y1 = cos(angle) * radius;
        float x2 = sin(nextAngle) * radius, y2 = cos(nextAngle) * radius;

        // Draw the top triangle (green) - normal and position for each vertex
        glNormal3f(x1, y1, 0);
        glVertex3f(x1, y1, 0);
        glNormal3f(x2, y2, 0);
        glVertex3f(x2, y2, height);
        glNormal3f(x1, y1, 0);
        glVertex3f(x1, y1, height);

        // Draw bottom triangle (red) - normal and position for each vertex
        glNormal3f(x1, y1, 0);
        glVertex3f(x1, y1, 0);
        glNormal3f(x2, y2, 0);
        glVertex3f(x2, y2, 0);
        glNormal3f(x2, y2, 0);
        glVertex3f(x2, y2, height);

        // for a closed cylinder: bottom triangle
        glNormal3f(0.0f, 0.0f, -1.0f); // point down
        glVertex3f(x1, y1, 0);
        glVertex3f(x2, y2, 0);
        glVertex3f(0, 0, 0);

        // for a closed cylinder: top triangle
        glNormal3f(0.0f, 0.0f, 1.0f); // point up
        glVertex3f(x1, y1, height);
        glVertex3f(x2, y2, height);
        glVertex3f(0.0f, 0.0f, height);
    }
    glEnd();
}

void Objects::drawSphere(float radius, int nSegments, int nSlices) {
  float x, y, z;
  float s, t; // texture coordinates

  float theta_step = (2.0f * PI) /  static_cast<float>(nSlices);
  float phi_step = PI /  static_cast<float>(nSegments);

  glBegin(GL_QUADS);
  for (float theta = -PI; theta < PI; theta += theta_step) {
    for (float phi = -(PI / 2.0f); phi < (PI / 2.0f); phi += phi_step) {
      // Calculate the four vertex corners of the quad:
      //1
      x = cos(phi) * cos(theta) * radius;
      y = cos(phi) * sin(theta) * radius;
      z = sin(phi) * radius;
      t = (phi / PI) + 0.5f;
      s = (theta / (PI * 2.0f)) + 0.5f;
      glTexCoord2f(s, t);
      glNormal3f(x, y, z);
      glVertex3f(x, y, z);
      // 2
      x = cos(phi) * cos(theta + theta_step) * radius;
      y = cos(phi) * sin(theta + theta_step) * radius;
      z = sin(phi) * radius;
      t = (phi / PI) + 0.5f;
      s = ((theta + theta_step) / (PI * 2.0f)) + 0.5f;
      glTexCoord2f(s, t);
      glNormal3f(x, y, z);
      glVertex3f(x, y, z);
      // 3
      x = cos(phi + phi_step) * cos(theta + theta_step) * radius;
      y = cos(phi + phi_step) * sin(theta + theta_step) * radius;
      z = sin(phi + phi_step) * radius;
      t = ((phi + phi_step) / PI) + 0.5f;
      s = ((theta + theta_step) / (PI * 2.0f)) + 0.5f;
      glTexCoord2f(s, t);
      glNormal3f(x, y, z);
      glVertex3f(x, y, z);
      // 4
      x = cos(phi + phi_step) * cos(theta) * radius;
      y = cos(phi + phi_step) * sin(theta) * radius;
      z = sin(phi + phi_step) * radius;
      t = ((phi + phi_step) / PI) + 0.5f;
      s = (theta / (PI * 2.0f)) + 0.5f;
      glTexCoord2f(s, t);
      glNormal3f(x, y, z);
      glVertex3f(x, y, z);
    }
  }

  glEnd();
}

void Objects::drawQuad() {
  glBegin(GL_QUADS);
  glNormal3f(0.0f, 0.0f, 1.0f);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 0.0f);
  glEnd();
}
