cmake_minimum_required(VERSION 3.14)
project(raytracer)

add_compile_options(
    -Wall -Wextra -Wpedantic -Werror
    -fsanitize={address,undefined}
    -Wshadow -Wpointer-arith -Wcast-align
    -std=c11 -g -O3
)

set(SOURCE_PREFIX
	${PROJECT_SOURCE_DIR}/src
)

set(INCLUDE_PREFIX
	${PROJECT_SOURCE_DIR}/include
)

set(SOURCE_FILES
	${SOURCE_PREFIX}/camera.c
	${SOURCE_PREFIX}/color.c
	${SOURCE_PREFIX}/hittable.c
	${SOURCE_PREFIX}/hittable_list.c
	${SOURCE_PREFIX}/point3.c
	${SOURCE_PREFIX}/ray.c
	${SOURCE_PREFIX}/sphere.c
	${SOURCE_PREFIX}/utility.c
	${SOURCE_PREFIX}/vector.c
	${SOURCE_PREFIX}/vec3.c
)

add_library(raytracer
	${SOURCE_FILES}
)

target_include_directories(raytracer PUBLIC
	${INCLUDE_PREFIX}
)

add_executable(main
	${SOURCE_PREFIX}/main.c
)

target_include_directories(main PUBLIC
	${INCLUDE_PREFIX}
)

target_link_libraries(main PUBLIC
	raytracer
    -fsanitize=address
    -fsanitize=undefined
)
