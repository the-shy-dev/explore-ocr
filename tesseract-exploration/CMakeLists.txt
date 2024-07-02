cmake_minimum_required(VERSION 3.10)
project(ExploreOCR)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(BasicDemo src/BasicDemo.cpp)
add_executable(SetRectangle src/SetRectangle.cpp)
add_executable(GetComponentImages src/GetComponentImages.cpp)
add_executable(ResultIterator src/ResultIterator.cpp)

# Find Tesseract and Leptonica libraries
find_package(PkgConfig REQUIRED)
pkg_check_modules(Tesseract REQUIRED tesseract)
pkg_check_modules(Leptonica REQUIRED lept)

# Include Tesseract and Leptonica directories
include_directories(${Tesseract_INCLUDE_DIRS} ${Leptonica_INCLUDE_DIRS})

# Link Tesseract and Leptonica libraries
target_link_libraries(BasicDemo ${Tesseract_LIBRARIES} ${Leptonica_LIBRARIES})
target_link_libraries(SetRectangle ${Tesseract_LIBRARIES} ${Leptonica_LIBRARIES})
target_link_libraries(GetComponentImages ${Tesseract_LIBRARIES} ${Leptonica_LIBRARIES})
target_link_libraries(ResultIterator ${Tesseract_LIBRARIES} ${Leptonica_LIBRARIES})