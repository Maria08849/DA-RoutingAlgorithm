cmake_minimum_required(VERSION 3.23)
project(ProjDA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA2ndProject main.cpp graph.cpp graph.h VertexEdge.cpp VertexEdge.h Menu.cpp Menu.h Funcs.cpp Funcs.h)


# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_SOURCE_DIR}/docs/doxyfile.txt")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/docs/doxyfile.txt")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)