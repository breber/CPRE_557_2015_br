function(CreateProject name source)
    MESSAGE(STATUS "Source files: " ${source})

    project(${name})

    include(SetupLibraries)
    SetupLibraries()

    # Create an executable
    add_executable(${name} ${source})

    # Add libraries
    target_link_libraries(${name} ${ALL_LIBS} ${EXTRA_LIBS})

endfunction(CreateProject)
