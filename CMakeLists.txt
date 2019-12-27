cmake_minimum_required(VERSION 3.9)
project(EigenGurobi CXX)
set(PROJECT_DESCRIPTION "Gurobi QP solver through Eigen3 library.")

################################################################################

# project-options
option(EIGEN_GUROBI_WITH_TESTS "Build unit tests using Catch2" ON)

################################################################################

### Configuration
set(EIGEN_GUROBI_EXTERNAL "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${PROJECT_NAME}Dependencies)

################################################################################
# EigenGurobi Library
################################################################################

add_library(${PROJECT_NAME} "src/Gurobi.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "src/")

################################################################################
# Required Libraries
################################################################################

# Eigen
find_package(Eigen REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${Eigen_INCLUDE_DIRS})

# Gurobi
find_package(GUROBI REQUIRED)
target_include_directories(${PROJECT_NAME} PUBLIC ${GUROBI_INCLUDE_DIRS})
foreach(GUROBI_LIBRARY ${GUROBI_LIBRARIES})
  message(STATUS "Linking ${PROJECT_NAME} against ${GUROBI_LIBRARY}")
  target_link_libraries(${PROJECT_NAME} ${GUROBI_LIBRARY})
endforeach()

################################################################################

# Unit tests
if(EIGEN_GUROBI_WITH_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()

################################################################################
# Compiler options
################################################################################
