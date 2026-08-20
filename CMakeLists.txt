cmake_minimum_required(VERSION 3.20)

project("PolyScope CGAL Feature")

# ------------------------------------------------------------------------------
# Prevent in-source builds
# ------------------------------------------------------------------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR
            "Source and build directories cannot be the same. "
            "Go use the /build directory.")
endif ()

# ------------------------------------------------------------------------------
# MSVC runtime
#
# Release -> /MD
# Debug   -> /MDd
#
# IMPORTANT: Do not add /MT anywhere else in this file.
# ------------------------------------------------------------------------------
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
            "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif ()

# ------------------------------------------------------------------------------
# Output directories
# ------------------------------------------------------------------------------
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ------------------------------------------------------------------------------
# C++
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Compiler options
# ------------------------------------------------------------------------------
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang"
        OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    message("Using clang/gcc compiler flags")

    set(BASE_CXX_FLAGS
            "-std=c++20 -Wall -Wextra -g3")

    set(DISABLED_WARNINGS
            "-Wno-unused-parameter
         -Wno-unused-variable
         -Wno-unused-function
         -Wno-deprecated-declarations
         -Wno-missing-braces")

    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")

        message("Setting clang-specific options")

        set(BASE_CXX_FLAGS
                "${BASE_CXX_FLAGS} -ferror-limit=5 -fcolor-diagnostics")

        set(CMAKE_CXX_FLAGS_DEBUG
                "-fsanitize=address -fno-limit-debug-info")

    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

        message("Setting gcc-specific options")

        set(BASE_CXX_FLAGS
                "${BASE_CXX_FLAGS} -fmax-errors=5")

        set(DISABLED_WARNINGS
                "${DISABLED_WARNINGS}
             -Wno-maybe-uninitialized
             -Wno-format-zero-length
             -Wno-unused-but-set-parameter
             -Wno-unused-but-set-variable")

    endif ()

    set(CMAKE_CXX_FLAGS
            "${BASE_CXX_FLAGS} ${DISABLED_WARNINGS}")

    set(CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG} -g3")

    set(CMAKE_CXX_FLAGS_MINSIZEREL
            "-Os -DNDEBUG")

    set(CMAKE_CXX_FLAGS_RELEASE
            "-march=native -O3 -DNDEBUG")

    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO
            "-O2 -g")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message("Using Visual Studio compiler flags")

    # MSVC compilation options
    add_compile_options(
            /W4
            /bigobj
            /MP
            /wd4267
            /wd4244
            /wd4305
    )

    # Preprocessor definitions
    add_compile_definitions(
            _CRT_SECURE_NO_WARNINGS
            NOMINMAX
            _USE_MATH_DEFINES
    )

else ()

    message(FATAL_ERROR
            "Unrecognized compiler [${CMAKE_CXX_COMPILER_ID}]")

endif ()

# ------------------------------------------------------------------------------
# Eigen
# ------------------------------------------------------------------------------
set(Eigen
        "C:/Users/mladeuil/Downloads/eigen-3.4.0/eigen-3.4.0/build")

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# ------------------------------------------------------------------------------
# Boost
# ------------------------------------------------------------------------------
set(Boost_COMPILER "-vc143")
set(BOOST_ROOT "C:/local/boost_1_88_0")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

# ------------------------------------------------------------------------------
# METIS
# ------------------------------------------------------------------------------
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/Metis-5.1.0/Include
)

# ------------------------------------------------------------------------------
# Polyscope
# ------------------------------------------------------------------------------
message("\n\n == CMAKE recursively building Polyscope\n")
add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/polyscope"
)
if (TARGET polyscope)
    target_compile_options(polyscope PRIVATE
            /W0
    )
endif ()

# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------
add_executable(
        CGAL-polyscope-example
        src/main.cpp
)

# ------------------------------------------------------------------------------
# CGAL
# ------------------------------------------------------------------------------
set(CGAL_DIR
        "C:/PROJECT/CGAL/CGAL-6.2")

find_package(CGAL REQUIRED)

# ------------------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------------------
target_include_directories(
        CGAL-polyscope-example
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/deps"
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/libigl/include"
)

message(STATUS "Eigen include dirs: ${EIGEN_INCLUDE_DIRS}")
# ------------------------------------------------------------------------------
# Geometry Central
# ------------------------------------------------------------------------------
add_subdirectory(
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/geometry-central"
)

# ------------------------------------------------------------------------------
# C++ standard
# ------------------------------------------------------------------------------
target_compile_features(
        CGAL-polyscope-example
        PRIVATE
        cxx_std_20
)
add_subdirectory(deps/hlod)
# ------------------------------------------------------------------------------
# Link
# ------------------------------------------------------------------------------
target_link_libraries(
        CGAL-polyscope-example
        PRIVATE
        polyscope
        CGAL
        Eigen3::Eigen
        geometry-central
        hlod
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/Metis-5.1.0/Libs/metis_idx32.lib"
)