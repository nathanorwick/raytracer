
# Overview

This is a simple ray tracer program, based off of *Ray Tracing in One Weekend* by **Peter Shirley**. The referenced material uses **C++** to program the ray tracer, whereas this project is written in **C**.

# Project Setup

    % tree .
    .
    ├── CMakeLists.txt
    ├── README.md
    ├── build.sh
    ├── include
    │   ├── camera.h
    │   ├── color.h
    │   ├── hittable.h
    │   ├── hittable_list.h
    │   ├── image.h
    │   ├── material.h
    │   ├── point3.h
    │   ├── ray.h
    │   ├── sphere.h
    │   ├── utility.h
    │   ├── vec3.h
    │   └── vector.h
    ├── run.sh
    └── src
        ├── camera.c
        ├── color.c
        ├── hittable.c
        ├── hittable_list.c
        ├── main.c
        ├── material.c
        ├── point3.c
        ├── ray.c
        ├── sphere.c
        ├── utility.c
        ├── vec3.c
        └── vector.c

To compile the program on Linux or MacOS, from the project directory, run

    % ./build.sh

Once the program is compiled, execute it with

    % ./run.sh

This will open the rendered image after, which will also be stored as `results/render.ppm`.

For more documentation, see the header files under `include/`. TODO - add more documentation.

# Future Ideas

### Changing the image format:

`JPG` or `PNG` rather than `PPM`, maybe using **stb**.

### Parallelization:

**OpenMP** or **CUDA** could both be looked into.

### Optimization:

Many structs are passed by value, rather than by reference. This is convenient for many reasons. Most of the structs are small, so the additional `malloc` & `free` calls may not be worth it. This may be worth it for the larger structs (as done for the `hittable_list`).

### Other Changes:

*Ray Tracing in One Weekend* seems to have been updated to clear up `main` & leverage the `camera` object more since I wrote this. It would be more readable to do similarly in this project, so that `main.c` is less packed.

# References

- https://raytracing.github.io/books/RayTracingInOneWeekend.html

