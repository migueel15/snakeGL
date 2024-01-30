#include "game.h"
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
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2),
  //              vertices.data(), GL_DYNAMIC_DRAW);


  glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(glm::vec2), vertices, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2),
                        0);
  glEnableVertexAttribArray(0);

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

// void Game::updateVertices(Snake &snake) {
//   vertices.clear();
//   for (const auto &segment : snake.segments) {
//     vertices.push_back(segment.vertices[0]);
//     vertices.push_back(segment.vertices[1]);
//     vertices.push_back(segment.vertices[3]);
//
//     vertices.push_back(segment.vertices[1]);
//     vertices.push_back(segment.vertices[2]);
//     vertices.push_back(segment.vertices[3]);
//
//     std::cout << segment.vertices[0].x << " " << segment.vertices[0].y << " "
//               << segment.vertices[1].x << " " << segment.vertices[1].y << " "
//               << segment.vertices[2].x << " " << segment.vertices[2].y << " "
//               << segment.vertices[3].x << " " << segment.vertices[3].y << " "
//               << std::endl;
//   }
//   glBindBuffer(GL_ARRAY_BUFFER, VBO);
//   glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size(), &vertices[0]);
//   glBindBuffer(GL_ARRAY_BUFFER, 0);
//   
// }

void Game::updateVertices(Snake &snake) {
  int i = 0;
  for (const auto &segment : snake.segments) {
    vertices[i] = segment.vertices[0];
    i++;
    vertices[i] = segment.vertices[1];
    i++;
    vertices[i] = segment.vertices[3];
    i++;

    vertices[i] = segment.vertices[1];
    i++;
    vertices[i] = segment.vertices[2];
    i++;
    vertices[i] = segment.vertices[3];
    i++;

  }
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, 6, &vertices[0]);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
}

void Game::render() {
  glClearColor(30.0 / 255.0, 30.0 / 255.0, 46.0 / 255.0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Use the shader program, bind VAO, and draw
  glBindVertexArray(VAO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

  glUseProgram(shaderProgram);
  glDrawArrays(GL_TRIANGLES, 0, 12); // borrar despues
  // glDrawArrays(GL_TRIANGLES, 0, vertices.size());
  glBindVertexArray(0);
}

int main(int argc, char *argv[]) {
  Snake snake;
  Food food;
  initSnake(snake);
  initFood(food);
  Game game;
  // eatFood(snake, food);
  // moveSnake(snake);
  game.updateVertices(snake);

  while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
    game.render();
    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
