cmake_minimum_required(VERSION 3.7)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

set(SOURCE_FILES
        calculations/Intersecter.cpp
        geometry/Double.cpp
        geometry/Geometry.cpp
        objects/GeometricObject.cpp
        objects/PlaneGeometricObject.cpp
        objects/Sphere.cpp
        objects/ConvexPolygon.cpp
        objects/Parallelogram.cpp
        objects/Triangle.cpp
        main.cpp parsers/DefaultParser.cpp ImageSettings.cpp parsers/RTParser.cpp parsers/STLParser.cpp painters/PNGPainter.cpp)
add_executable(ray_tracing ${SOURCE_FILES})

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

target_link_libraries(ray_tracing pthread png)
