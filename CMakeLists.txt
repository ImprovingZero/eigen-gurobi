cmake_minimum_required(VERSION 3.9)
project(eigen-gurobi CXX)
set(PROJECT_DESCRIPTION "Gurobi QP solver through Eigen3 library.")

### Configuration
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

################################################################################
# Eigen-Gurobi Library
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
# Compiler options
################################################################################
