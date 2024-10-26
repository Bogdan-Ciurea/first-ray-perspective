# Gather all .cpp files in the apps directory
file(GLOB APP_SOURCES "*.cpp")

# Loop through each source file and create an executable
foreach(APP_SRC ${APP_SOURCES})
    # Get the name of the source file without the extension
    get_filename_component(APP_NAME ${APP_SRC} NAME_WE)

    # Create executable for the source file
    add_executable(${APP_NAME} ${APP_SRC})

    target_include_directories(${APP_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/constructions)

    # Set the C++ standard
    target_compile_features(${APP_NAME} PRIVATE cxx_std_14)

    # Link the library
    target_link_libraries(${APP_NAME} PRIVATE raytracing-lib)

    # Set output directory
    set_target_properties(${APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")
endforeach()
