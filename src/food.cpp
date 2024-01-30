#include "food.h"
#include "snake.h"

Food::Food() {
  init();
}

void Food::init() {
  position = glm::vec2(rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT);
}

glm::vec2 Food::getPos(){
  return position;
}
