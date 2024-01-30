#include "game.h"
#include "food.h"
#include "glad/glad.h"
#include "snake.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void check_exit(GLFWwindow *window);

Game::Game() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(BOARD_WIDTH, BOARD_HEIGHT, "Juego", NULL, NULL);

  if (window == NULL) {
    std::cout << "Error al crear la ventana" << std::endl;
    glfwTerminate();
  }

  glfwMakeContextCurrent(window);
  gladLoadGL();

  // vincula el viewport al size de la ventana
  glViewport(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
  // modifica el viewport cuando se cambia el size de la ventana
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2),
  //              vertices.data(), GL_DYNAMIC_DRAW);
  //
  // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
  // glEnableVertexAttribArray(0);

  const char *vertexShaderSource = "#version 330 core\n"
                                   "layout (location = 0) in vec2 pos;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   gl_Position = vec4(pos,0.0,1.0);\n"
                                   "}\0";

  const char *fragmentShaderSource = "#version 330 core\n"
                                     "out vec4 FragColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   FragColor = vec4(1.0,1.0,1.0, 0.0f);\n"
                                     "}\0";

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // se crea el programa del shader y se vinculan
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // una vez vinculados al programa ya podemos borrarlos
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void check_exit(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Game::render() {
  glClearColor(30.0 / 255.0, 30.0 / 255.0, 46.0 / 255.0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2),
               vertices.data(), GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
  glEnableVertexAttribArray(0);
  // Use the shader program, bind VAO, and draw
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_POINTS, 0, vertices.size()); // borrar despues
}

void Game::updateVertices(Snake &snake) {
  vertices.clear();
  std::vector<glm::vec2> positions = snake.getSnakePositions();
  for (int i = 0; i < positions.size(); i++) {
    vertices.push_back(positions[i]);
  }
}

void Game::sleep(int milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Game::checkInput(Snake &snake) {
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
    snake.changeDirection(Direction::UP);
  }
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
    snake.changeDirection(Direction::DOWN);
  }
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
    snake.changeDirection(Direction::LEFT);
  }
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
    snake.changeDirection(Direction::RIGHT);
  }
}

void check_exit() {
  if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
  }
}

int main(int argc, char *argv[]) {
  Game game;
  Snake snake;
  // Food food;
  snake.init();
  snake.appendToSnake();
  snake.appendToSnake();
  snake.appendToSnake();
  // food.init();

  while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
    check_exit();
    game.checkInput(snake);
    game.render();
    snake.move();
    game.updateVertices(snake);

    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
    game.sleep(500);
  }

  glfwTerminate();
  return 0;
}
