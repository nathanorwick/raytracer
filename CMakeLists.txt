cmake_minimum_required(VERSION 3.14)
project(raytracer)

add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    -fsanitize={address,undefined}
    -Wshadow -Wpointer-arith -Wcast-align
    -std=c11 -g -O2
)

add_library(raytracer
	${PROJECT_SOURCE_DIR}/src/vec3.c
	${PROJECT_SOURCE_DIR}/src/color.c
)

target_include_directories(raytracer PUBLIC
	${PROJECT_SOURCE_DIR}/include
)

add_executable(main
    ${PROJECT_SOURCE_DIR}/src/main.c
)

target_include_directories(main PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(main PUBLIC
	raytracer
    -fsanitize=address
    -fsanitize=undefined
)
