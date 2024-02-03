#pragma once

#include "snake.h"
#include "food.h"
#include <glm/glm.hpp>
#include <vector>
#include <thread>
#include <chrono>

struct Vertex {
  glm::vec2 position;
  glm::vec3 color;
};

class Game {
public:
  Game();
  void render();
  void updateVertices(Snake &snake, Food &food);
  void sleep(int milliseconds);
  void checkInput(Snake &snake);
  void checkCollision(Snake &snake, Food &food);
  void debugSnake(Snake &snake, Food &food);

private:
  unsigned int VAO;
  unsigned int VBO;
  unsigned int shaderProgram;
  std::vector<Vertex> vertices;
};

