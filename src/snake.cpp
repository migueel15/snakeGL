#include "snake.h"
#include <iostream>

Snake::Snake() {
  init();
}

void Snake::init() {
  segments.clear();
  size = 1;
  score = 0;
  direction = Direction::RIGHT;
  SnakeSegment segment;
  segment.position = glm::vec2(BOARD_WIDTH / 2, BOARD_HEIGHT / 2);
  segments.push_back(segment);
}

void Snake::appendToSnake() {
  SnakeSegment segment;
  segment.position = segments.back().position;
  segments.push_back(segment);
}

void Snake::move() {
  SnakeSegment &currentHead = segments.front();
  SnakeSegment &currentTail = segments.back();
  currentTail.position = currentHead.position;

  switch (direction) {
  case Direction::UP:
    currentTail.position.y += SNAKE_SIZE;
    break;
  case Direction::DOWN:
    currentTail.position.y -= SNAKE_SIZE;
    break;
  case Direction::LEFT:
    currentTail.position.x -= SNAKE_SIZE;
    break;
  case Direction::RIGHT:
    currentTail.position.x += SNAKE_SIZE;
    break;
  }

  segments.pop_back();
  segments.push_front(currentTail);
}

void Snake::changeDirection(Direction newDirection) {
  Direction currentDirection = direction;
  switch (newDirection) {
  case Direction::UP:
    if (currentDirection != Direction::DOWN) {
      direction = newDirection;
    }
    break;
  case Direction::DOWN:
    if (currentDirection != Direction::UP) {
      direction = newDirection;
    }
    break;
  case Direction::LEFT:
    if (currentDirection != Direction::RIGHT) {
      direction = newDirection;
    }
    break;
  case Direction::RIGHT:
    if (currentDirection != Direction::LEFT) {
      direction = newDirection;
    }
    break;
  }
}

std::vector<glm::vec2> Snake::getSnakePositions() {
  std::vector<glm::vec2> positions;
  for (const auto &segment : segments) {
    float x = segment.position.x;
    float y = segment.position.y;
    // normalize to -1 to 1
    x = (x / BOARD_WIDTH) * 2 - 1;
    y = (y / BOARD_HEIGHT) * 2 - 1;
    positions.push_back(glm::vec2(x, y));
  }
  return positions;
}
