#include "food.h"
#include "snake.h"

Food::Food() {
  init();
}

void Food::init() {
  float height = ((rand() % (int)BOARD_HEIGHT/SNAKE_SIZE) - (float)BOARD_HEIGHT/SNAKE_SIZE/2.0) * SNAKE_SIZE + BOARD_HEIGHT/2.0;
  float width = ((rand() % (int)BOARD_WIDTH/SNAKE_SIZE) - (float)BOARD_WIDTH/SNAKE_SIZE/2.0) * SNAKE_SIZE + BOARD_WIDTH/2.0;
  position = glm::vec2(width, height);
}

glm::vec2 Food::getPos() {
  return position;
}

glm::vec2 Food::getNormalisedFood(){
  // normalise the position between -1 and 1
  return glm::vec2((position.x / BOARD_WIDTH) * 2 - 1,
                   (position.y / BOARD_HEIGHT) * 2 - 1);
}
