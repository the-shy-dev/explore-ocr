cmake_minimum_required(VERSION 3.10)
project(PaddleOCRExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/external/opencv4
)
file(GLOB_RECURSE EXTERNAL_LIB_FILES "${CMAKE_SOURCE_DIR}/lib/external/*.so*")

# PaddleOCR and PaddlePaddle settings
set(PADDLE_DIR ${CMAKE_SOURCE_DIR}/paddle)
include_directories(${PADDLE_DIR}/paddle/include)
link_directories(${PADDLE_DIR}/paddle/lib)

# Add executable
add_executable(PaddleOCRExample main.cpp)

# Link PaddleOCR, PaddlePaddle and OpenCV libraries
target_link_libraries(PaddleOCRExample ${EXTERNAL_LIB_FILES} paddle_inference)
