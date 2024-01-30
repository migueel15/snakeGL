#include "snake.h"
#include "food.h"
#include <iostream>
#include <vector>

int main (int argc, char *argv[]) {
  Snake snake;
  snake.init();
  snake.appendToSnake();
  snake.move();
  snake.appendToSnake();
  snake.move();
  snake.changeDirection(Direction::UP);
  snake.move();
  snake.move();

  Food food;
  food.init();
  std::cout << "Food: " << food.getPos().x << " " << food.getPos().y << std::endl;

  food.init();
  std::cout << "Food: " << food.getPos().x << " " << food.getPos().y << std::endl;

  std::vector<glm::vec2> position = snake.getSnakePositions();
  for (int i = 0; i < position.size(); i++) {
    std::cout << position[i].x << ", " << position[i].y << "; " ;
  }
  std::cout << std::endl;

  return 0;
}
