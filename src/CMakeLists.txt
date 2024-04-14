# Set the source files for the library
set(SOURCE_FILES
    hello_openmp.cpp
    # Add more source files here
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
