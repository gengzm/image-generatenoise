# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "\n${Red}FATAL: In-source builds are not allowed.You should create a separate directory for build files.${ColorReset}")
endif()
cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5)

# Set the version information 
set(EDIC_VERSION_MAJOR 0 CACHE STRING "major version" FORCE)
set(EDIC_VERSION_MINOR 1 CACHE STRING "minor version" FORCE)
set(EDIC_VERSION_PATCH 0 CACHE STRING "patch version" FORCE)

# Use C++14 
set(DEFAULT_CXX_STANDARD ${CMAKE_CXX_STANDARD})
if (NOT DEFAULT_CXX_STANDARD)
  set(DEFAULT_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_STANDARD ${DEFAULT_CXX_STANDARD} CACHE STRING "C++ standard (minimum 14)" FORCE)

project(noise CXX C)

if (WIN32)
  set(OpenCV_DIR "D:/opencv/build/" CACHE FILEPATH "Set to find OpenCVConfig.cmake")
else()
  set(OpenCV_DIR "$ENV{HOME}/Rvbust/Install/OpenCV/share/OpenCV" CACHE FILEPATH "Set to find OpenCV")
endif()

#find_package(Threads REQUIRED)
find_package(OpenCV REQUIRED NO_DEFAULT_PATH)

add_executable(noise Src/noise.cpp)
target_include_directories(noise PRIVATE ${OpenCV_INCLUDE_DIRS} )
target_link_libraries(noise PRIVATE  ${OpenCV_LIBS})


