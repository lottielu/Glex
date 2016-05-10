#ifndef PYRAMID_H
#define PYRAMID_H

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class Pyramid : public GameAsset {
 public:
  Pyramid(float x, float y, float z);
  ~Pyramid();
  virtual void Draw(GLuint);
  void rotateX(float);
  glm::mat4 animate;
  GLfloat angle;

 private:
  GLuint element_buffer_length;
  GLuint vertex_buffer_token, element_buffer_token;
  glm::mat4 model_matrix;

  GLuint colour_buffer_length;
  GLuint colour_buffer_token;

  void checkError(std::string file, int line);
};

#endif // Pyramid_H
