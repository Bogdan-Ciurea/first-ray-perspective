# Set the source files for the library
set(SOURCE_FILES
  math/vec3.cpp
  math/vec4.cpp
  math/mat4.cpp

  # Add more source files here
  objects/ObjectsList.cpp
  objects/Sphere.cpp

  hit_record.cpp
  Window.cpp
)

# Create the library
add_library(raytracing-lib ${SOURCE_FILES})

# Set the C++ standard
target_compile_features(raytracing-lib PUBLIC cxx_std_14)

# Include directories
target_include_directories(raytracing-lib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# If you need OpenMP, include it here
# Parallelization
OPTION (USE_OpenMP "Use OpenMP to enamble <omp.h>" ON)

# Find OpenMP
if (USE_OpenMP)
  find_package(OpenMP REQUIRED)
endif()

if (OPENMP_FOUND)
  # Print that we are using OpenMP
  message(STATUS "Using OpenMP for parallelization")

  target_link_libraries(raytracing-lib PUBLIC OpenMP::OpenMP_CXX)
  
  # Add the OpenMP flag
  if (USE_OpenMP)
    add_definitions(-DUSE_OPENMP="can use openmp")
  endif()
  
else()
  message(STATUS "Not using OpenMP for parallelization")
endif()

# Add raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY git@github.com:raysan5/raylib.git
  GIT_TAG 4.0.0
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

message(STATUS "Fetching raylib")

FetchContent_MakeAvailable(raylib)
target_include_directories(raytracing-lib
  PUBLIC
  ${raylib_SOURCE_DIR}/src
)

target_link_libraries(raytracing-lib PUBLIC raylib)
