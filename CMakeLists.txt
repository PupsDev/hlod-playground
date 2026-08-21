cmake_minimum_required(VERSION 3.20)

project(HLODPlayground LANGUAGES CXX)

# ------------------------------------------------------------
# C++
# ------------------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------
# Compiler options
# ------------------------------------------------------------

if (MSVC)

    add_compile_options(
            /W4
            /bigobj
            /MP
            /wd4267
            /wd4244
            /wd4305
    )

    add_compile_definitions(
            _CRT_SECURE_NO_WARNINGS
            NOMINMAX
            _USE_MATH_DEFINES
    )

endif ()

# ------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

set(BOOST_ROOT "C:/local/boost_1_88_0")
find_package(Boost REQUIRED)

set(CGAL_DIR "C:/PROJECT/CGAL/CGAL-6.2")
find_package(CGAL REQUIRED)


# ------------------------------------------------------------
# METIS
# ------------------------------------------------------------

set(METIS_INCLUDE_DIR
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/Metis-5.1.0/Include"
)

set(METIS_LIBRARY
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/Metis-5.1.0/Libs/metis_idx32.lib"
)

add_subdirectory(deps/polyscope)
add_subdirectory(deps/hlod)
target_compile_options(polyscope PRIVATE
        /w
)
# ------------------------------------------------------------
# Application
# ------------------------------------------------------------

add_executable(
        HLODPlayground
        src/main.cpp
)

target_include_directories(
        HLODPlayground
        PRIVATE
        ${METIS_INCLUDE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        "${CMAKE_CURRENT_SOURCE_DIR}/deps"
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/libigl/include"
)

target_link_libraries(
        HLODPlayground
        PRIVATE
        polyscope
        CGAL
        Eigen3::Eigen
        hlod
        ${METIS_LIBRARY}
)