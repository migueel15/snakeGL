project(OpenGLGame)

add_executable(game game.cpp glad.c snake.cpp)
target_link_libraries(game glfw)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)


add_executable(test test.cpp glad.c snake.cpp food.cpp)
target_link_libraries(test glfw)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
