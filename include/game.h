#pragma once

#include "snake.h"
#include <glm/glm.hpp>
#include <vector>
#include <thread>
#include <chrono>

class Game {
public:
  Game();
  void render();
  void updateVertices(Snake &snake);
  void sleep(int milliseconds);
  void checkInput(Snake &snake);

private:
  unsigned int VAO;
  unsigned int VBO;
  unsigned int shaderProgram;
  std::vector<glm::vec2> vertices;
};

