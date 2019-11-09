cmake_minimum_required(VERSION 3.10)
project(Cargo)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -O3 -g -fopenmp -pthread")

find_library(LIBRT rt)
find_library(GLPK glpk)
find_library(DL dl)
find_library(METIS metis)

include_directories(. include ${PROJECT_SOURCE_DIR.}/include example example/kinetic_tree/include example/trip_vehicle_grouping/include)
add_library(CARGOLIB STATIC
    src/cargo.cc
    src/classes.cc
    src/dbsql.cc
    src/file.cc
    src/functions.cc
    src/grid.cc
    src/gtree/gtree.cc
    src/rsalgorithm.cc
    src/sqlite3/sqlite3.c
    example/bilateral+/bilateral+.cc
    example/bilateral_arrangement/bilateral_arrangement.cc
    example/grabby/grabby.cc
    example/grasp/grasp.cc
    example/greedy/greedy.cc
    example/kinetic_tree/kinetic_tree.cc
    example/kinetic_tree/src/treeTaxiPath.cpp
    example/nearest_neighbor/nearest_neighbor.cc
    example/nearest_road/nearest_road.cc
    example/simulated_annealing/simulated_annealing.cc
    example/trip_vehicle_grouping/trip_vehicle_grouping.cc)

add_executable(launcher example/launcher.cc)
target_link_libraries(launcher CARGOLIB ${LIBRT} ${METIS} ${GLPK} ${DL})

add_executable(gtreebuilder tool/gtreebuilder/src/gtreebuilder.cc)
target_link_libraries(gtreebuilder CARGOLIB ${LIBRT} ${METIS} ${GLPK} ${DL})

include_directories(tool/rspgen/include)
add_library(RSPGENLIB STATIC tool/rspgen/src/kdtree.c)
add_executable(rspgen_c tool/rspgen/src/rspgen_c.cc)
target_link_libraries(rspgen_c CARGOLIB RSPGENLIB ${LIBRT} ${METIS} ${GLPK} ${DL})

