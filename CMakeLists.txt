cmake_minimum_required(VERSION 3.12)


project(CVRP
		VERSION 1.0.0
		DESCRIPTION "Sudoku"
		HOMEPAGE_URL "lucassguedes.github.io"
		)

set(CMAKE_C_STANDARD 17) 
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
add_compile_options(-g -Wall -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

file(GLOB SOURCES src/*.c)

add_executable(sudoku ${SOURCES})

target_link_libraries(sudoku m)



target_include_directories(sudoku PUBLIC
						   include
)


