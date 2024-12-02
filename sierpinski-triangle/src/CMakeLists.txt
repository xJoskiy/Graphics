set(BINARY ${CMAKE_PROJECT_NAME})

set(main "main.cpp")

add_executable(${BINARY} ${main})

target_link_libraries(${BINARY} sfml-graphics sfml-window sfml-system)