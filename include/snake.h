#pragma once

#include "glm/glm.hpp"
#include <deque>
#include <vector>

// size in pixels
const int BOARD_WIDTH = 500;
const int BOARD_HEIGHT = 500;

const int SNAKE_SIZE = 25;
const float SNAKE_VELOCITY = 0.1f; // each 100ms

const int FOOD_SIZE = 10;
const glm::vec3 SNAKE_COLOR = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 FOOD_COLOR = glm::vec3(1.0f, 0.0f, 0.0f);

const int MAX_SNAKE_SIZE =
    BOARD_HEIGHT * BOARD_WIDTH / (SNAKE_SIZE * SNAKE_SIZE);

enum Direction { UP = 0, LEFT , DOWN , RIGHT };

struct SnakeSegment {
  glm::vec2 position;
};


class Snake {
public:
  Snake();
  void init();
  void appendToSnake();
  void move();
  void changeDirection(Direction direction);
  std::vector<glm::vec2> getSnakePositions();
  //TODO: getters and setters
  // int getScore();
  // int getSize();
  // std::deque<SnakeSegment> getSegments();

  float width;
  int score;
  Direction direction;
  int size;
  std::deque<SnakeSegment> segments;
private:
};
