#pragma once

#include "glm/glm.hpp"
#include <deque>

// size in pixels
const int BOARD_WIDTH = 500;
const int BOARD_HEIGHT = 500;

const int SNAKE_SIZE = 40;
const float SNAKE_VELOCITY = 0.1f;

const int FOOD_SIZE = 10;

const int MAX_SNAKE_SIZE =
    BOARD_HEIGHT * BOARD_WIDTH / (SNAKE_SIZE * SNAKE_SIZE);

enum class Direction { UP = 0, DOWN, LEFT, RIGHT };

struct SnakeSegment {
  glm::vec2 position;
  glm::vec2 vertices[4];
  int size;
};

struct Snake {
  std::deque<SnakeSegment> segments;
  int size;
  int score;
  Direction direction;
};

struct Food {
  glm::vec2 position;
  int points;
};

void initSnake(Snake &snake);
void initFood(Food &food);
void eatFood(Snake &snake, Food &food);
void appendToSnake(Snake &snake);
void moveSnake(Snake &snake);
void changeDirection(Snake &snake, Direction direction);
void checkColisionFood(Snake &snake, Food &food);
void createVertices(SnakeSegment &sSegment);
