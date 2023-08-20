
# Overview

This is a simple ray tracer program, based off of *Ray Tracing in One Weekend* by **Peter Shirley**. The referenced material uses **C++** to program the ray tracer, whereas this project is written in **C**.

See the final render & references at the bottom.

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

To change the image quality or size, see `include/image.h`. For more documentation, see the header files under `include/`. TODO - add more documentation.

# Future Ideas

### Changing the image format:

`JPG` or `PNG` rather than `PPM`, maybe using **stb**.

### Parallelization:

**OpenMP** or **CUDA** could both be looked into.

### Optimization:

Many structs are passed by value, rather than by reference. This is convenient for many reasons. Most of the structs are small, so the additional `malloc` & `free` calls may not be worth it. This may be worth it for the larger structs (as done for the `hittable_list`).

### Other Changes:

*Ray Tracing in One Weekend* seems to have been updated since I wrote most of this. I cleaned up my `main.c` file similarly, to leverage the `camera` object more. It might be good to go through the files in the future & clean up the organization. 

The `random_scene` function could also be updated to create a more novel image, as well as changing the `random_double` function to be more *random* than it currently is.

# Final Render

![render](https://github.com/nathanorwick/raytracer/assets/89475097/e18f841f-2671-4965-a6a8-e746bd4a307c)

# References

- https://raytracing.github.io/books/RayTracingInOneWeekend.html
