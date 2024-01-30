#pragma once

#include "snake.h"
#include <glm/glm.hpp>
#include <vector>

class Game {
public:
  Game();
  void render();
  void updateVertices(Snake &snake);

private:
  unsigned int VAO;
  unsigned int VBO;
  unsigned int shaderProgram;
  glm::vec2 vertices[12]; // borrar depsues
  // std::vector<glm::vec2> vertices;
};

