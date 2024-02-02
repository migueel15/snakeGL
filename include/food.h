#pragma once
#include "glm/glm.hpp"

const int FOOD_SCORE = 1;

class Food {
public:
  Food();
  void init();
  glm::vec2 getPos();
  glm::vec2 getNormalisedFood();

private:
  glm::vec2 position;
};

