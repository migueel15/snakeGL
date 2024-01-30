#include "snake.h"
#include <iostream>

void initSnake(Snake &snake) {
  snake.segments.clear();
  snake.size = 1;
  snake.score = 0;
  snake.direction = Direction::RIGHT;
  SnakeSegment segment;
  segment.position = glm::vec2(BOARD_WIDTH / 2, BOARD_HEIGHT / 2);
  segment.size = SNAKE_SIZE;
  createVertices(segment);
  snake.segments.push_back(segment);
}

void initFood(Food &food) {
  // random position
  food.position = glm::vec2(rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT);
  food.points = 1;
}

void appendToSnake(Snake &snake) {
  SnakeSegment segment;
  segment.position = snake.segments.back().position;
  segment.size = SNAKE_SIZE;
  createVertices(segment);
  snake.segments.push_back(segment);
}

void eatFood(Snake &snake, Food &food) {
  snake.size++;
  snake.score += food.points;
  appendToSnake(snake);
  initFood(food);
}

void checkColisionFood(Snake &snake, Food &food) {
  bool colision = false;
  for (const auto &element : snake.segments) {
    // lo mismo hay que añadir el size/2 al check para la colision
    if (element.position == food.position) {
      colision = true;
    }
  }

  if (colision) {
    eatFood(snake, food);
  }
}

void moveSnake(Snake &snake) {
  SnakeSegment &currentHead = snake.segments.front();
  SnakeSegment &currentTail = snake.segments.back();
  currentTail.position = currentHead.position;

  switch (snake.direction) {
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
  createVertices(currentTail);

  snake.segments.pop_back();
  snake.segments.push_front(currentTail);
}

void changeDirection(Snake &snake, Direction newDirection) {
  Direction currentDirection = snake.direction;
  switch (newDirection) {
  case Direction::UP:
    if (currentDirection != Direction::DOWN) {
      snake.direction = newDirection;
    }
    break;
  case Direction::DOWN:
    if (currentDirection != Direction::UP) {
      snake.direction = newDirection;
    }
    break;
  case Direction::LEFT:
    if (currentDirection != Direction::RIGHT) {
      snake.direction = newDirection;
    }
    break;
  case Direction::RIGHT:
    if (currentDirection != Direction::LEFT) {
      snake.direction = newDirection;
    }
    break;
  }
}

void createVertices(SnakeSegment &sSegment) {
  float x = sSegment.position.x;
  float y = sSegment.position.y;
  float halfSize = sSegment.size/2.0;
  glm::vec2 a = glm::vec2(x, y);
  sSegment.vertices[0] = glm::vec2((x - halfSize -(BOARD_WIDTH/2.0))/BOARD_WIDTH, (y + halfSize-(BOARD_HEIGHT/2.0))/BOARD_HEIGHT); // Top-left}
  sSegment.vertices[1] = glm::vec2((x + halfSize -(BOARD_WIDTH/2.0))/BOARD_WIDTH, (y + halfSize-(BOARD_HEIGHT/2.0))/BOARD_HEIGHT); // Top-right
  sSegment.vertices[2] = glm::vec2((x + halfSize -(BOARD_WIDTH/2.0))/BOARD_WIDTH, (y - halfSize-(BOARD_HEIGHT/2.0))/BOARD_HEIGHT); // Bottom-right
  sSegment.vertices[3] = glm::vec2((x - halfSize -(BOARD_WIDTH/2.0))/BOARD_WIDTH, (y - halfSize-(BOARD_HEIGHT/2.0))/BOARD_HEIGHT); // Bottom-left
}
